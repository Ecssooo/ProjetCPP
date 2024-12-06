#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "MathUtils.h"


struct Player
{
    int id;
    int hp;
    float speed;
    
    //SFML
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f direction;
    
    //Bullet params
    Bullet* bullet;
    float reloadTime;
    float shootSpeedTimer = 0;
    
    void Move(sf::Vector2f direction, sf::RenderWindow* window, float deltatime);
    sf::Vector2f ClampPosition(sf::Vector2f position, sf::RenderWindow* window);
    void LookAt(sf::Vector2f direction);
    bool CanShoot(float deltatime);
    Bullet Shoot();
};

Player CreatePlayer(int id, int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, Bullet* bullet, float reloadTime);