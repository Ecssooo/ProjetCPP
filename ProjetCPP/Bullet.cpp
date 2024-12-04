#include "Bullet.h"

Bullet CreateBullet(Bullet* bullet, sf::Vector2f position, sf::Vector2f direction)
{
    Bullet newBullet = (*bullet);
    
    newBullet.shape.setFillColor(bullet->color);
    newBullet.shape.setPosition(position);
    newBullet.shape.setOrigin(bullet->shape.getRadius(), bullet->shape.getRadius());
    newBullet.position = position;
    newBullet.direction = direction;

    return newBullet;
}

void MoveAllBullet(sf::RenderWindow* window, std::list<Bullet>* bullets, float deltatime)
{
    std::list<Bullet>::iterator it = bullets->begin();
    while (it != bullets->end())
    {
        sf::Vector2f newPos = (*it).shape.getPosition();
        newPos += IIM::Normalize((*it).direction) * (*it).speed * deltatime;
        (*it).shape.setPosition(newPos);
        (*it).position = newPos;
        if ((*it).OutOfBound(window))
        {
            it = bullets->erase(it);
        }
        else {
            it++;
        }
    }
}
void DrawAllBullet(sf::RenderWindow* window, std::list<Bullet>* bullets)
{
    std::list<Bullet>::iterator it = bullets->begin();
    while (it != bullets->end())
    {
        window->draw((*it).shape);
        it++;
    }
}

bool Bullet::OutOfBound(sf::RenderWindow* window)
{
    return this->shape.getPosition().x < 0 || this->shape.getPosition().y < 0 || this->shape.getPosition().x > window->getSize().x || this->shape.getPosition().y > window->getSize().y; 
}
