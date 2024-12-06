#include "Player.h"

Player CreatePlayer(int id, int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, Bullet* bullet, float reloadTime)
{
    shape.setPosition(pos);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    return Player{id, hp, speed,shape, pos, sf::Vector2f{0,0}, bullet, reloadTime};
}

void Player::Move(sf::Vector2f direction, sf::RenderWindow* window, float deltatime)
{
    if(IIM::GetMagnitude(direction) < 0.3f)
    {
        return;
    }
    
    sf::Vector2f newPos = position;
    newPos += IIM::Normalize(direction) * speed * deltatime;
    position = ClampPosition(newPos, window);
    shape.setPosition(position);
    this->direction = direction;
    LookAt(direction);
}

void Player::LookAt(sf::Vector2f direction)
{
    shape.setRotation(IIM::ConvertVectorToDegree(direction,false, false) - 30);
}

sf::Vector2f Player::ClampPosition(sf::Vector2f position, sf::RenderWindow* window)
{
    if(position.x < (0 + shape.getRadius()))
    {
        position.x = (0 + shape.getRadius());
    }else if(position.x > (window->getSize().x - shape.getRadius()))
    {
        position.x = (window->getSize().x - shape.getRadius());
    }
    if(position.y < (0 + shape.getRadius()))
    {
        position.y = (0 + shape.getRadius());
    }else if(position.y > (window->getSize().y - shape.getRadius()))
    {
        position.y = (window->getSize().y - shape.getRadius());
    }

    return position;
}

bool Player::CanShoot(float deltatime)
{
    shootSpeedTimer += deltatime;
    if (IIM::GetMagnitude(this->direction) < 0.3f)
    {
        return false;
    }
    return this->shootSpeedTimer >= this->reloadTime;
}

Bullet Player::Shoot()
{
    this->shootSpeedTimer = 0;
    return CreateBullet(this->bullet, this->position, this->direction);
}