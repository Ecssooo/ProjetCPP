#include "Player.h"

const float pi = 3.14159265358979323846;

Player CreatePlayer(int hp, float speed, sf::CircleShape shape, sf::Vector2f pos)
{
    return Player{hp, speed, shape, pos};
}

void Player::Move(sf::Vector2f direction, float deltatime)
{
    if(abs(direction.x) < 0.1 && abs(direction.y) < 0.1)
    {
        shape.setFillColor(sf::Color::Red);
        return;
    }
    shape.setFillColor(sf::Color::White);
    position += direction * speed * deltatime;
    shape.setPosition(position);
    LookAt(direction);
}

void Player::LookAt(sf::Vector2f direction)
{
    shape.setRotation(atan2(direction.y, direction.x)*180 / pi - 30);
}
