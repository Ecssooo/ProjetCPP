#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "ColisionManager.h"


int GetNbJostick() {
    for (int i = 0; i <= 8; i++) {
        if (!sf::Joystick::isConnected(i))
        {
            return i;
        }
    }
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "GW");
    //Initialisation
    sf::Clock clock;
    int NbJoystick = GetNbJostick();

    std::list<Enemy> enemiesTypes{ 
        Enemy{100, sf::CircleShape {20, 3}, sf::Color::Green, 5.0f },
        Enemy{150, sf::CircleShape {20, 4}, sf::Color::Green, 7.5f }
    };
    std::list<Enemy> enemiesTotal{};

    Bullet bullet {400, sf::CircleShape{5}, sf::Color::Red};
    std::list<Bullet> bulletsTotal{};

    std::vector<Player> players = { CreatePlayer(3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ 300,300 }, &bullet, 0.5f) };
    for (int i = 1; i < NbJoystick; i++) {
        players.push_back(CreatePlayer(3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ 300,300 }, &bullet, 0.5f));
    }
    for (int i = 0; i < NbJoystick; i++) {
        players[i].position.x += 100 * i;
        players[i].shape.setPosition(players[i].position);
    }
    std::vector<sf::Vector2f> input{ { 0,0 } };
    for (int i = 1; i < NbJoystick; i++) {
        input.push_back({ 0,0 });
    }

    //Boucle de jeu
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds(); 

        //Jostick change
        int TestNbJoystick = GetNbJostick();
        if (TestNbJoystick != NbJoystick) {
            if (TestNbJoystick > NbJoystick && NbJoystick != 0) {
                players.push_back(CreatePlayer(3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ 300,300 }, &bullet, 0.5f));
                input.push_back({ 0,0 });
            }
            else if (TestNbJoystick < NbJoystick && NbJoystick != 1) {
                players.pop_back();
                input.pop_back();
            }
            NbJoystick = TestNbJoystick;
        }
        
        //Input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (NbJoystick >= 1)
        {
            for (int i = 0; i < NbJoystick; i++) {
                input[i] = { sf::Joystick::getAxisPosition(i, sf::Joystick::X) / 100.0f,sf::Joystick::getAxisPosition(i, sf::Joystick::Y) / 100.0f };
            }
        }
        else {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            input[0] = { mousePosition.x - players[0].position.x, mousePosition.y - players[0].position.y};
        }

        //Update
        for (int i = 0; i < players.size(); i++) {
            players[i].Move(input[i], &window, deltaTime);
            if (players[i].CanShoot(deltaTime)) {
                bulletsTotal.push_back(players[i].Shoot());
            }
        }
        MoveAllBullet(&window, &bulletsTotal, deltaTime);

        SpawnEnemies(&enemiesTotal, &enemiesTypes, &window, deltaTime);
        std::vector<sf::Vector2f> playersPos {};
        for (int i = 0; i < players.size(); i++) {
            playersPos.push_back(players[i].position);
        }
        MoveAllEnemies(&enemiesTotal, playersPos, deltaTime);
        CheckColision(&enemiesTotal, &players, &bulletsTotal);
        
        window.clear();
        //Affichage
        DrawAllEnemies(&enemiesTotal, &window);
        DrawAllBullet(&window, &bulletsTotal);
        for (int i = 0; i < players.size(); i++) {
            window.draw(players[i].shape);
        }
        
        window.display();
    }

    return 0;
}