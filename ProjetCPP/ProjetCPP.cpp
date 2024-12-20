#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Base.h"
#include "ColisionManager.h"
#include "Multiplayer.h"
#include "ParticleSystem.h"
#include "GameManager.h"
#include "Menu.h"
#include "Windows.h"




int main(int argc, char* argv[])
{
    //Initialisation
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "GW", sf::Style::Fullscreen);
    sf::Clock clock;

    int waveCount = 0;
    
    //Setup States
    GAMESTATES gameStates = GAMESTATES::START;
    GAMESTATES pastGameStates = GAMESTATES::START;
    bool GamePause = true;

    //Setup Base
    Base base = CreateBase(&window, 100, 5, 30);
    float currentTimer = 0;
    
    //Setup Enemies
    std::list<Enemy> enemiesTypes{
        Enemy{100, 1, false, sf::CircleShape {15, 3}, sf::Color{227,41,20}, 3.75f  },
        Enemy{ 100, 1, true, sf::CircleShape {15, 3}, sf::Color{251,1,1}, 5.1f },
        Enemy{ 150, 2, false, sf::CircleShape {15, 4}, sf::Color{199,56,19}, 7.2f  } ,
        Enemy{300, 0, true, sf::CircleShape {5}, sf::Color{249,70,9}, 1.3f},
        Enemy{ 75, 40, false, sf::CircleShape {175, 12}, sf::Color{165,21,13}, 15.0f }
    };
    std::list<Enemy> enemiesTotal{};

    int enemiesKills = 1;

    //Setup Particles
    std::list<ParticleSystem> particleSystems {};

    //Setup Bullet
    Bullet bullet {400, sf::CircleShape{5}, sf::Color {236, 240, 241, 255}};
    std::list<Bullet> bulletsTotal{};


    //Setup Player
    std::list<int> JosticksID{0,1,2,3,4,5,6,7};

    std::vector<Player> players = { CreatePlayer(0, 3, 200, sf::CircleShape{ 15, 3 }, sf::Vector2f{ 300,300 }, &bullet, 0.5f, PlayerColor(0))};
    if (GetNbJostick(JosticksID) > 0) InitPlayers(JosticksID, &players, &bullet);
    std::vector<sf::Vector2f> inputs{8, { 0,0 } };
    std::vector<sf::Vector2f> playersPos {};
    int playersReady = 0;


    //Setup UI
    std::vector<Button> buttons{
        CreateButton("None", sf::Vector2f {(float)window.getSize().x / 2,400}, sf::RectangleShape{{500,200}}, BUTTONSTATES::NONE),
        CreateButton("Quit", sf::Vector2f {(float)window.getSize().x / 2,700}, sf::RectangleShape{{500,200}}, BUTTONSTATES::QUIT),
    };
    std::vector<Button>::iterator buttonsIt = buttons.begin();
    while (buttonsIt != buttons.end()) {
        buttonsIt->Change(buttonsIt->buttonState);
        buttonsIt++;
    }
    
    std::vector<Text> texts{
        CreateText("Appuyer sur espace ou la touche A pour vous mettre pret", sf::Vector2f {(float)window.getSize().x / 2,0}),
        CreateText("Wave ", sf::Vector2f {(float)window.getSize().x / 2,0}),
        CreateText("GEOMERTY GUYS FOR REAL WAR", sf::Vector2f {(float)window.getSize().x / 2,(float)window.getSize().y / 3}),
        CreateText("Enemies killed : ", sf::Vector2f {(float)window.getSize().x / 2, 50}),
    };
    
    //Game Loop
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        window.clear();

        //Manage function for specific state;
        switch (gameStates)
        {
            default:
                gameStates = GAMESTATES::START;
                break;
            case(GAMESTATES::START):
                
                //Check player ready
                sf::Event event;
                if (GetNbJostick(JosticksID) > 0)
                {
                    GetReadyInputs(JosticksID, &players);
                }
                while (window.pollEvent(event)) {
                    //Use keyboard if no controller 0
                    if (!sf::Joystick::isConnected(0)) {
                        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)) {
                            players[0].playerStates = PLAYERSTATES::READY;
                        }
                    }
                }

                //Check number player ready
                playersReady = 0;
                for (int i = 0; i < players.size(); i++) {
                    if (players[i].playerStates == PLAYERSTATES::READY) {
                        playersReady++;
                    }
                }
                    
                //Change State : switch game state when all player ready;
                if (playersReady == players.size())
                {
                    base.BaseRevive(&window);
                    currentTimer = 0;
                    gameStates = GAMESTATES::REVIVE;
                    GamePause = false;
                }
                break;
            case(GAMESTATES::ROUNDINPROGRESS):
                if(GamePause) break;
                //Update timer : switch game state when ending; 
                base.timerText.setString(std::to_string((int)(base.roundTimer - currentTimer)));
                if(Timer(deltaTime, &currentTimer, base.roundTimer))
                {
                    gameStates = GAMESTATES::REVIVE;
                    currentTimer = 0;
                }

                //Make player shoot
            
                for (int i = 0; i < players.size(); i++) {
                    if(players[i].playerStates == PLAYERSTATES::ALIVE)
                    {
                        if (players[i].CanShoot(deltaTime)) {
                            bulletsTotal.push_back(players[i].Shoot());
                        }
                    }
                }
                MoveAllBullets(&window, &bulletsTotal, deltaTime);

                //Update enemies
                SpawnEnemies(&enemiesTotal, &enemiesTypes, base.position, &window, deltaTime);
                for (int i = 0; i < players.size(); i++) {
                    if (players[i].playerStates == PLAYERSTATES::ALIVE) {
                        playersPos.push_back(players[i].position);
                    }
                }
                MoveAllEnemies(&enemiesTotal, base.position, playersPos, deltaTime);
                CheckCollisionsPlayers(&enemiesTotal, &particleSystems, &players);
                CheckCollisionsBase(&enemiesTotal, &base);
                CheckCollisionsBullets(&enemiesTotal, &particleSystems, &bulletsTotal, &enemiesKills);
            

                //Change State : switch game state when base destroyed;
                if (!base.IsBaseAlive()) {
                    gameStates = GAMESTATES::START;
                    waveCount = 0;
                    buttons[0].Change(BUTTONSTATES::NONE);
                    GamePause = true;
                }
            
                break;
            case(GAMESTATES::REVIVE):
                if(GamePause) break;
                enemiesTotal.clear();

                //Update timer : switch game state when ending;
                base.timerText.setString(std::to_string((int)(base.revivePlayerTimer - currentTimer)));
                if(Timer(deltaTime, &currentTimer, base.revivePlayerTimer))
                {
                    gameStates = GAMESTATES::ROUNDINPROGRESS;
                    currentTimer = 0;
                    waveCount++;
                    UpdateEnemiesDifficulty(&enemiesTypes, waveCount + players.size());
                    UpdateAllPlayersStats(&players, enemiesKills);

                }

                //Revive dead players
                for (int i = 0; i < players.size(); i++) {
                    players[i].hp = 3;
                    if (players[i].playerStates != PLAYERSTATES::ALIVE)
                    {
                        players[i].playerStates = PLAYERSTATES::ALIVE;
                        players[i].position = base.position;
                        players[i].shape.setPosition(base.position);
                    }
                }

                break;
        }

        //Manage global function in game
        if (GamePause == false) {
            //Get all input 
            playersPos = {};
            sf::Event event;
            while (window.pollEvent(event))
            {
                if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || GetPauseInput(JosticksID)) {
                    pastGameStates = gameStates;
                    buttons[0].Change(BUTTONSTATES::RESUME);
                    GamePause = true;
                }
            }
            if (GetNbJostick(JosticksID) > 0)
            {
                CheckJoystick(JosticksID, &inputs, &players, &bullet);
                GetMovementInputs(JosticksID, &inputs);
            }
            //Use mouse if no controller 0
            if (!sf::Joystick::isConnected(0)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                inputs[0] = { mousePosition.x - players[0].position.x, mousePosition.y - players[0].position.y };
            }

            //Update entity positions
            MoveAllPlayers(&players, inputs, & window, deltaTime);
            MoveAllBullets(&window, &bulletsTotal, deltaTime);
            UpdateAllParticleSystem(&particleSystems, &window, deltaTime);

            //Draw game
            DrawAllEnemies(&enemiesTotal, &window);
            DrawBase(&base, &window);
            DrawBaseLife(&base, &window);
            DrawAllBullets(&window, &bulletsTotal);
            DrawAllParticleSystem(&window, &particleSystems);
            DrawAllPlayers(&players, &window);
            DrawWaveText(&window, texts[1], waveCount);
            DrawWaveText(&window, texts[3], enemiesKills - 1);
        }
        //Manage function in menu
        else {
            //Manage button
            sf::Event event;
            while (window.pollEvent(event));
            for(int i = 0; i < buttons.size(); i++)
            {
                if(buttons[i].OnClick(&window))
                {
                    switch(buttons[i].buttonState)
                    {
                        default:
                            break;
                        case(BUTTONSTATES::QUIT):
                            window.close();
                            break;
                        case(BUTTONSTATES::RESUME):
                            gameStates = pastGameStates;
                            GamePause = false;
                            break;
                    }
                }
            }

            //Draw menu
            DrawAllButton(&window, &buttons);
            if(gameStates == GAMESTATES::START)
            {
                DrawStartText(&window,texts[0]);
                DrawStartText(&window,texts[2]);
            }
        }
        window.display();
    }

    return 0;
}
