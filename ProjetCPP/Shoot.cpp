#include "Shoot.h"
#include "Math.h"

Bullet CreateBullet(Player* player)
{
    Bullet newBullet {player->speed, player->bulletShape, player->direction};
    
    newBullet.shape.setFillColor(sf::Color::Red);
    newBullet.shape.setPosition(player->position);
    newBullet.shape.setOrigin(player->bulletRadius, player->bulletRadius);
    newBullet.shape.setRadius(player->bulletRadius);

    return newBullet;
}

void Shoot(Player* player)
{
    player->bullets.push_back(CreateBullet(player));
}

void UpdateAllBullet(sf::RenderWindow* window, Player* player, float deltatime)
{
    std::list<Bullet>::iterator it = player->bullets.begin();
    while(it != player->bullets.end())
    {
        if((*it).OutOfBound(window))
        {
            it = player->bullets.erase(it);
            return;
        }
        sf::Vector2f newPos = (*it).shape.getPosition();
        newPos += Normalize((*it).direction) * player->bulletSpeed * deltatime;
        (*it).shape.setPosition(newPos);

        
        window->draw((*it).shape);
        it++;
    }
    player->shootSpeedTimer += deltatime;
    if(player->shootSpeedTimer >= 0.2f)
    {
        Shoot(player);
        player->shootSpeedTimer = 0;
    }
    
    
}

bool Bullet::OutOfBound(sf::RenderWindow* window)
{
    return this->shape.getPosition().x < 0 || this->shape.getPosition().y < 0 || this->shape.getPosition().x > window->getSize().x || this->shape.getPosition().y > window->getSize().y; 
}
