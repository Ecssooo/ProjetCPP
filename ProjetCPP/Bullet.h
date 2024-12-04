#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "MathUtils.h"

struct Bullet
{
    float speed;
    sf::CircleShape shape;
    sf::Color color;
    sf::Vector2f position;
    sf::Vector2f direction {};
    
    bool OutOfBound(sf::RenderWindow* window);
};

void MoveAllBullet(sf::RenderWindow* window, std::list<Bullet>* bullets, float deltatime);
void DrawAllBullet(sf::RenderWindow* window, std::list<Bullet>* bullets);

Bullet CreateBullet(Bullet* bullet, sf::Vector2f position, sf::Vector2f direction);
