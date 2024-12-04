#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Bullet.h"


struct Player
{
    int hp;
    float speed;
    
    //SFML
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f direction;
    
    //Bullet params
    Bullet* bullet;
    float reloadTime;
    std::list<Bullet> bullets {};
    float shootSpeedTimer = 0;
    
    void Move(sf::Vector2f direction, sf::RenderWindow* window, float deltatime);
    void LookAt(sf::Vector2f direction);
    sf::Vector2f ClampPosition(sf::Vector2f position, sf::RenderWindow* window);
    void Shoot(float deltatime);
};

Player CreatePlayer(int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, Bullet* bullet, float reloadTime);