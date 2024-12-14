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

void MoveAllBullets(sf::RenderWindow* window, std::list<Bullet>* bullets, float deltatime);
void DrawAllBullets(sf::RenderWindow* window, std::list<Bullet>* bullets);

Bullet CreateBullet(Bullet* bullet, sf::Vector2f position, sf::Vector2f direction);
