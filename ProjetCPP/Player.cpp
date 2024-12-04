#include "Player.h"
#include "Bullet.h"
#include "MathUtils.h"

const double pi = 3.14159265358979323846;

Player CreatePlayer(int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, Bullet* bullet, float reloadTime)
{
    shape.setPosition(pos);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    return Player{hp, speed,shape, pos, sf::Vector2f{0,0}, bullet, reloadTime};
}

void Player::Move(sf::Vector2f direction, sf::RenderWindow* window, float deltatime)
{
    if(IIM::GetMagnitude(direction) < 0.3f)
    {
        window->draw(shape);
        return;
    }
    
    sf::Vector2f newPos = position;
    newPos += IIM::Normalize(direction) * speed * deltatime;
    position = ClampPosition(newPos, window);
    shape.setPosition(position);
    this->direction = direction;
    LookAt(direction);
    
    window->draw(shape);
}

void Player::LookAt(sf::Vector2f direction)
{
    shape.setRotation(atan2(direction.y, direction.x)*180 / pi - 30);
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

void Player::Shoot(float deltatime)
{
    shootSpeedTimer += deltatime;
    if(this->shootSpeedTimer >= this->reloadTime)
    {
        bullets.push_back(CreateBullet(this->bullet, this->position, this->direction));
        this->shootSpeedTimer = 0;
    }
}