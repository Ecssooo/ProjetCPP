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

    std::vector<Player> players = { CreatePlayer(0, 3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ 300,300 }, &bullet, 0.5f, sf::Color::Green) };
    if (GetNbJostick(JosticksID) > 0) InitPlayers(JosticksID, &players, &bullet);
    std::vector<sf::Vector2f> inputs{8, { 0,0 } };
    std::vector<sf::Vector2f> playersPos {};
    

    int playersReady = 0;

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

                    //Input
                    playersReady = GetReadyInputs(JosticksID, &players);
            
                    //Update
                    for (int i = 0; i < players.size(); i++) {
                        if(players[i].playerStates == PLAYERSTATES::READY){
                            playersReady++;
                        }
                    }
                
                    if(playersReady == players.size())
                    {
                        for (int i = 0; i < players.size(); i++){
                            players[i].playerStates = PLAYERSTATES::ALIVE;
                        }
                        gameStates = GAMESTATES::ROUNDINPROGRESS;
                    }

                    //Draw
                break;
            case(GAMESTATES::PAUSE):
                break;
            case(GAMESTATES::END):
                window.close();
                break;
            case(GAMESTATES::ROUNDINPROGRESS):
                
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
                for (int i = 0; i < players.size(); i++) {
                    if(players[i].playerStates == PLAYERSTATES::ALIVE)
                    {
                        players[i].Move(inputs[players[i].id], &window, deltaTime);
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
                UpdateAllParticleSystem(&particleSystems, &window, deltaTime);

                if(PlayerAlive(&players) == players.size())
                {
                    gameStates = GAMESTATES::END;
                }
                
                break;
            case(GAMESTATES::REVIVE):
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
                for (int i = 0; i < players.size(); i++) {
                    players[i].Move(inputs[players[i].id], &window, deltaTime);
                }
            
                for (int i = 0; i < players.size(); i++) {
                    playersPos.push_back(players[i].position);
                }
                UpdateAllParticleSystem(&particleSystems, &window, deltaTime);
            
                break;
        }
        
        
        //Input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        playersPos = {};
        
        window.clear();
        //Affichage
        DrawAllEnemies(&enemiesTotal, &window);
        DrawAllBullets(&window, &bulletsTotal);
        DrawAllParticleSystem(&window, &particleSystems);
        for (int i = 0; i < players.size(); i++) {
            if(players[i].playerStates != PLAYERSTATES::DEAD)
            {
                window.draw(players[i].shape);
                players[i].DrawHealth(&window, i);
            }
        }
        
        window.display();
    }

    return 0;
}
