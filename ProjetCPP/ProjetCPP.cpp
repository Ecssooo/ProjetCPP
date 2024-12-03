#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"


int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "GW");
    //Initialisation
    sf::Clock clock;
    
    Player player = CreatePlayer(3, 1, sf::CircleShape {20, 3}, sf::Vector2f{300,300}, &window);

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

            if(sf::Joystick::isConnected(0))
            {

                input = {sf::Joystick::getAxisPosition(0, sf::Joystick::X),sf::Joystick::getAxisPosition(0, sf::Joystick::Y)};
            }
        }
        
        window.clear();
        //Affichage
        player.Move(input, deltaTime);
        
        window.display();
    }

    return 0;
}
