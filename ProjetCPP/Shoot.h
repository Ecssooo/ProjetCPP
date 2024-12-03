#pragma once
#include "Player.h"


struct Bullet
{
    float speed;
    sf::CircleShape shape;
    sf::Vector2f direction;

    bool OutOfBound(sf::RenderWindow* window);
};

void Shoot(Player* player);
void UpdateAllBullet(sf::RenderWindow* window, Player* player, float deltatime);

Bullet CreateBullet(Player* player);
