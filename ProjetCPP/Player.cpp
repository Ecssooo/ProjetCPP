#include "Player.h"

const float pi = 3.14159265358979323846;

Player CreatePlayer(int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, sf::RenderWindow* window)
{
    shape.setPosition(pos);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    return Player{hp, speed, shape, pos, window};
}

void Player::Move(sf::Vector2f direction, float deltatime)
{
    
    if(abs(direction.x) < 0.1f && abs(direction.y) < 0.1f)
    {
        shape.setFillColor(sf::Color::Red);
        window->draw(shape);
        return;
    }
    sf::Vector2f newPos = position;
    newPos += direction * speed * deltatime;
    shape.setFillColor(sf::Color::White);
    position = ClampPosition(newPos);
    shape.setPosition(position);
    LookAt(direction);
    window->draw(shape);

}

void Player::LookAt(sf::Vector2f direction)
{
    shape.setRotation(atan2(direction.y, direction.x)*180 / pi - 30);
}

sf::Vector2f Player::ClampPosition(sf::Vector2f position)
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
