#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Shoot.h"


int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "GW");
    //Initialisation
    sf::Clock clock;
    
    Player player = CreatePlayer(3, 50, sf::CircleShape {20, 3}, sf::Vector2f{300,300}, &window, sf::CircleShape {5}, 200, 5);

    sf::Vector2f input {0,0};

    //Boucle de jeu
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (sf::Joystick::isConnected(0))
        {
            input = { sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.0f,sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100.0f };
        }
        else {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            input = { mousePosition.x - player.position.x, mousePosition.y - player.position.y };
        }
        
        window.clear();
        //Affichage
        
        player.Move(input, deltaTime);
        UpdateAllBullet(&window, &player, deltaTime);
        
        window.display();
    }

    return 0;
}