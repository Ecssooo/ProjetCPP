#pragma once
#include <SFML/Graphics/CircleShape.hpp>

struct Player
{
    int hp;
    float speed;
    
    //SFML
    sf::CircleShape shape;
    sf::Vector2f position;
    
    void Move(sf::Vector2f direction, float deltatime);
    void LookAt(sf::Vector2f direction);
};

Player CreatePlayer(int hp, float speed, sf::CircleShape shape, sf::Vector2f pos);