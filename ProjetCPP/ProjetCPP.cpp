#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");


    while (window.isOpen()) {
       
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.display();
    }

    return 0;
}
