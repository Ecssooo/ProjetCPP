#pragma once
#include <list>
#include <SFML/Graphics.hpp>

struct Bullet;

struct Player
{
    int hp;
    float speed;
    
    //SFML
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f direction;
    
    sf::RenderWindow* window;
    
    //Bullet params
    std::list<Bullet> bullets;

    sf::CircleShape bulletShape;
    float bulletSpeed;
    float bulletRadius;
    
    float shootSpeedTimer = 0;
    
    void Move(sf::Vector2f direction, float deltatime);
    void LookAt(sf::Vector2f direction);
    sf::Vector2f ClampPosition(sf::Vector2f position);
};

Player CreatePlayer(int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, sf::RenderWindow* window, sf::CircleShape bulletShape, float bulletSpeed, float bulletRadius);