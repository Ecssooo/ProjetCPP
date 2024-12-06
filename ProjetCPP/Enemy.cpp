#include "Enemy.h"

void SpawnEnemies(std::list<Enemy>* enemies, std::list<Enemy>* enemiesType, sf::RenderWindow* window, float deltatime) {

    std::list<Enemy>::iterator it = enemiesType->begin();
    while (it != enemiesType->end())
    {
        (*it).spawnTime += deltatime;
        if ((*it).spawnTime >= (*it).spawnTimer)
        {
            float x = rand() % window->getSize().x;
            float y = rand() % window->getSize().y;
            (*enemies).push_back(CreateEnemy(&(*it), sf::Vector2f{x, y}));
            (*it).spawnTime = 0;
        }
        it++;
    }
}

Enemy CreateEnemy(Enemy* enemy, sf::Vector2f position)
{
    Enemy newEnemy = (*enemy);

    newEnemy.position = position;
    newEnemy.shape.setFillColor(enemy->color);
    newEnemy.shape.setPosition(position);
    newEnemy.shape.setOrigin(enemy->shape.getRadius(), enemy->shape.getRadius());

    return newEnemy;
}

void MoveAllEnemies(std::list<Enemy>* enemies, std::vector<sf::Vector2f> playersPos, float deltatime)
{
    std::list<Enemy>::iterator it = enemies->begin();
    while (it != enemies->end())
    {
        sf::Vector2f destination = playersPos[0];
        float distance = IIM::GetDistance(destination, (*it).position);
        for (int i = 0; i < playersPos.size(); i++)
        {
            if (IIM::GetDistance(playersPos[i], (*it).position) < distance) {
                distance = IIM::GetDistance(playersPos[i], (*it).position);
                destination = playersPos[i];
            }
        }
        (*it).Move(destination - (*it).position, deltatime);
        it++;
    }
}
void DrawAllEnemies(std::list<Enemy>* enemies, sf::RenderWindow* window)
{
    std::list<Enemy>::iterator it = enemies->begin();
    while (it != enemies->end())
    {
        window->draw((*it).shape);
        it++;
    }
}

bool Enemy::Touch(sf::Vector2f position, float radius)
{
    return IIM::IsOverlappingCircleOnCircle(this->position, this->shape.getRadius(), position, radius);
}

void Enemy::Move(sf::Vector2f direction, float deltatime)
{
    this->position += IIM::Normalize(direction) * this->speed * deltatime;
    shape.setPosition(position);
    this->direction = direction;
    LookAt(direction);
}

void Enemy::LookAt(sf::Vector2f direction)
{
    shape.setRotation(IIM::ConvertVectorToDegree(direction, false, false) - 30);
}