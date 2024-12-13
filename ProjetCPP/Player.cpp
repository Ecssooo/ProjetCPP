#include "Player.h"

Player CreatePlayer(int id, int hp, float speed, sf::CircleShape shape, sf::Vector2f pos, Bullet* bullet, float reloadTime, sf::Color color)
{
    shape.setPosition(pos);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setFillColor(color);
    return Player{id, hp, speed,shape, color ,pos, sf::Vector2f{0,0}, bullet, reloadTime};
}

void MoveAllPlayers(std::vector<Player>* players, std::vector<sf::Vector2f> directions, sf::RenderWindow* window, float deltatime)
{
    for (int i = 0; i < (*players).size(); i++) {
        (*players)[i].Move(directions[(*players)[i].id], window, deltatime);
    }
}
void DrawAllPlayers(std::vector<Player>* players, sf::RenderWindow* window)
{
    for (int i = 0; i < (*players).size(); i++) {
        if ((*players)[i].playerStates == PLAYERSTATES::ALIVE)
        {
            window->draw((*players)[i].shape);
            (*players)[i].DrawHealth(window, i);
        }
    }
}

void Player::Move(sf::Vector2f direction, sf::RenderWindow* window, float deltatime)
{
    if(IIM::GetMagnitude(direction) < 0.3f || playerStates != PLAYERSTATES::ALIVE)
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
    if (IIM::GetMagnitude(this->direction) < 0.3f || playerStates != PLAYERSTATES::ALIVE)
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

void Player::TakeDamage(int damage) {
    this->hp -= damage;
}

void Player::DrawHealth(sf::RenderWindow* window, int offset) {
    for (int i = 0; i < hp; i++) {
        sf::CircleShape hexa;
        hexa.setPointCount(6);
        hexa.setRadius(15);
        hexa.setFillColor(color);
        hexa.setOrigin(sf::Vector2f{ hexa.getRadius(), hexa.getRadius() });
        sf::Vector2f pos;
        pos.x = (float)window->getSize().x - (hexa.getRadius()) * (1 + (2 * i));
        pos.y = (float)hexa.getRadius() * (1 +(2.5f * offset));
        hexa.setPosition(pos);
        window->draw(hexa);
    }
}

void UpdateAllPlayersStats(std::vector<Player>* players, int ennemiesKills)
{
    std::vector<Player>::iterator it = players->begin();
    while(it != players->end())
    {
        (*it).reloadTime *= pow(.9f, ennemiesKills);
        it++;
    }
}
