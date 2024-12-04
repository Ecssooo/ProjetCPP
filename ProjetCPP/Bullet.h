#pragma once
#include "SFML/Graphics.hpp"
#include <list>

struct Bullet
{
    float speed;
    sf::CircleShape shape;
    sf::Color color;
    sf::Vector2f direction {};
    
    bool OutOfBound(sf::RenderWindow* window);
};

void UpdateAllBullet(sf::RenderWindow* window, std::list<Bullet>* bullets, float deltatime);

Bullet CreateBullet(Bullet* bullet, sf::Vector2f position, sf::Vector2f direction);
