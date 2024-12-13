#pragma once
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "MathUtils.h"

enum class PLAYERSTATES
{
    NOTREADY,
    READY,
    ALIVE,
    DEAD
};

struct Player
{
    int id;
    int hp;
    float speed;
    
    //SFML
    sf::CircleShape shape;
    sf::Color color = sf::Color::White;
    sf::Vector2f position;
    sf::Vector2f direction;
    
    //Bullet params
    Bullet* bullet;
    float reloadTime;
    float shootSpeedTimer = 0;
    PLAYERSTATES playerStates = PLAYERSTATES::NOTREADY;
    
    void Move(sf::Vector2f direction, sf::RenderWindow* window, float deltatime);
    sf::Vector2f ClampPosition(sf::Vector2f position, sf::RenderWindow* window);
    void LookAt(sf::Vector2f direction);
    bool CanShoot(float deltatime);
    Bullet Shoot();
    void TakeDamage(int damage);
    void DrawHealth(sf::RenderWindow* window, int offset);
};

void MoveAllPlayers(std::vector<Player>* players, std::vector<sf::Vector2f> directions, sf::RenderWindow* window, float deltatime);
void DrawAllPlayers(std::vector<Player>* players, sf::RenderWindow* window);
Player CreatePlayer(int id, int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, Bullet* bullet, float reloadTime, sf::Color color = sf::Color::White);
void UpdateAllPlayersStats(std::vector<Player>* players, int ennemiesKills);