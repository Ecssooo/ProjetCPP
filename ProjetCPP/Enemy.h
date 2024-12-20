#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <cmath>
#include "MathUtils.h"

struct Enemy
{
    float startSpeed;
    int attack;
    bool targetPlayers = false;

    //SFML
    sf::CircleShape shape;
    sf::Color color;

    float startSpawnTimer;

    sf::Vector2f position;
    sf::Vector2f direction;

    float speed = 0;
    float spawnTimer = 0;
    float spawnTime{ 0 };

    void Move(sf::Vector2f direction, float deltatime);
    void LookAt(sf::Vector2f direction);
    bool Touch(sf::Vector2f position, float radius);
};

void SpawnEnemies(std::list<Enemy>* enemiesTotal, std::list<Enemy>* enemies, sf::Vector2f basePos, sf::RenderWindow* window, float deltatime);
Enemy CreateEnemy(Enemy* enemy, sf::Vector2f position);
void MoveAllEnemies(std::list<Enemy>* enemies, sf::Vector2f basePos, std::vector<sf::Vector2f> playersPos, float deltatime);
void DrawAllEnemies(std::list<Enemy>* enemies, sf::RenderWindow* window);
void UpdateEnemiesDifficulty(std::list<Enemy>* enemies, int difficulty);