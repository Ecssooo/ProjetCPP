#pragma once
#include <SFML/Graphics.hpp>


struct Player
{
    int hp;
    float speed;
    
    //SFML
    sf::CircleShape shape;
    sf::Vector2f position;

    sf::RenderWindow* window;
    
    void Move(sf::Vector2f direction, float deltatime);
    void LookAt(sf::Vector2f direction);
    sf::Vector2f ClampPosition(sf::Vector2f position);
};

Player CreatePlayer(int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, sf::RenderWindow* window);