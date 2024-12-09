#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "ColisionManager.h"
#include "Multiplayer.h"
#include "ParticleSystem.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "GW", sf::Style::Fullscreen);
    //Initialisation
    sf::Clock clock;

    GAMESTATES gameStates = GAMESTATES::START;

    std::list<Enemy> enemiesTypes{ 
        Enemy{100, sf::CircleShape {20, 3}, sf::Color::Red, 1.0f },
        Enemy{150, sf::CircleShape {20, 4}, sf::Color::Red, 1.2f }
    };
    std::list<Enemy> enemiesTotal{};

    std::list<ParticleSystem> particleSystems {};

    Bullet bullet {400, sf::CircleShape{5}, sf::Color::Red};
    std::list<Bullet> bulletsTotal{};

    std::list<int> JosticksID{0,1,2,3,4,5,6,7};

    std::vector<Player> players = { CreatePlayer(0, 3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ 300,300 }, &bullet, 0.5f, PlayerColor(0))};
    if (GetNbJostick(JosticksID) > 0) InitPlayers(JosticksID, &players, &bullet);
    std::vector<sf::Vector2f> inputs{8, { 0,0 } };
    std::vector<sf::Vector2f> playersPos {};
    
    float currentTimer = 0;
    
    int playersReady = 0;
    bool GamePause = true;

    //Boucle de jeu
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        
        switch (gameStates)
        {
            default:
                gameStates = GAMESTATES::START;
                break;
            case(GAMESTATES::START):
                GamePause = true;

                //Input
                if (GetNbJostick(JosticksID) > 0)
                {
                    playersReady = GetReadyInputs(JosticksID, &players);
                }
                if (!sf::Joystick::isConnected(0)) {
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)) {
                            players[0].playerStates = PLAYERSTATES::READY;
                        }
                    }
                }

                //Update
                for (int i = 0; i < players.size(); i++) {
                    if (players[i].playerStates == PLAYERSTATES::READY) {
                        playersReady++;
                    }
                }

                if (playersReady == players.size())
                {
                    for (int i = 0; i < players.size(); i++) {
                        players[i].playerStates = PLAYERSTATES::ALIVE;
                    }
                    gameStates = GAMESTATES::ROUNDINPROGRESS;
                }
                break;
            case(GAMESTATES::PAUSE):
                GamePause = true;
                window.close();
                break;
            case(GAMESTATES::END):
                GamePause = true;
                window.close();
                break;
            case(GAMESTATES::ROUNDINPROGRESS):
                GamePause = false;

                if(Timer(deltaTime, &currentTimer, 10))
                {
                    gameStates = GAMESTATES::REVIVE;
                    currentTimer = 0;
                }
                //Update
                for (int i = 0; i < players.size(); i++) {
                    if(players[i].playerStates == PLAYERSTATES::ALIVE)
                    {
                        if (players[i].CanShoot(deltaTime)) {
                            bulletsTotal.push_back(players[i].Shoot());
                        }
                    }
                }
            
                MoveAllBullets(&window, &bulletsTotal, deltaTime);

                SpawnEnemies(&enemiesTotal, &enemiesTypes, &window, deltaTime);
                for (int i = 0; i < players.size(); i++) {
                    playersPos.push_back(players[i].position);
                }
                MoveAllEnemies(&enemiesTotal, playersPos, deltaTime);
                CheckCollision(&enemiesTotal, &particleSystems, &players, &bulletsTotal);
            
                break;
            case(GAMESTATES::REVIVE):
                GamePause = false;
                enemiesTotal.clear();

                if(Timer(deltaTime, &currentTimer, 10))
                {
                    gameStates = GAMESTATES::ROUNDINPROGRESS;
                    currentTimer = 0;
                }
            
                for (int i = 0; i < players.size(); i++) {
                    if (players[i].playerStates == PLAYERSTATES::DEAD)
                    {
                        players[i].playerStates = PLAYERSTATES::ALIVE;
                        players[i].hp = 3;
                    }
                }

                break;
        }
        if (GamePause == false) {
            //Input
            playersPos = {};
            sf::Event event;
            while (window.pollEvent(event))
            {
                if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                    gameStates = GAMESTATES::PAUSE;
                }
            }
            if (GetNbJostick(JosticksID) > 0)
            {
                CheckJoystick(JosticksID, &inputs, &players, &bullet);
                GetInputs(JosticksID, &inputs);
            }
            if (!sf::Joystick::isConnected(0)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                inputs[0] = { mousePosition.x - players[0].position.x, mousePosition.y - players[0].position.y };
            }

            //Update
            MoveAllPlayers(&players, inputs, & window, deltaTime);
            MoveAllBullets(&window, &bulletsTotal, deltaTime);

            for (int i = 0; i < players.size(); i++) {
                playersPos.push_back(players[i].position);
            }
            UpdateAllParticleSystem(&particleSystems, &window, deltaTime);

            //Affichage
            window.clear();
            DrawAllEnemies(&enemiesTotal, &window);
            DrawAllBullets(&window, &bulletsTotal);
            DrawAllParticleSystem(&window, &particleSystems);
            DrawAllPlayers(&players, &window);
        }
        else {
            //Affichage
            window.clear();
        }
        window.display();
    }

    return 0;
}
