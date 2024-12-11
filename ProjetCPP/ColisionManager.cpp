#include "ColisionManager.h"

void CheckCollisionsPlayers(std::list<Enemy>* enemies, std::list<ParticleSystem>* particleSystems, std::vector<Player>* players)
{
    std::list<Enemy>::iterator it = enemies->begin();
    while (it != enemies->end())
    {
        for (int i = 0; i < players->size(); i++)
        {
            if ((*it).Touch((*players)[i].position, (*players)[i].shape.getRadius()) && (*players)[i].playerStates == PLAYERSTATES::ALIVE) {
                it = enemies->erase(it);
                (*players)[i].TakeDamage();
                if ((*players)[i].hp <= 0) {
                    particleSystems->push_back(CreatePrefabSystem((*players)[i].color, (*players)[i].position));
                    (*players)[i].playerStates = PLAYERSTATES::DEAD;
                }
                break;
            }
        }
        if(it != enemies->end()) it++;
    }
}

void CheckCollisionsBase(std::list<Enemy>* enemies, Base* base)
{
    std::list<Enemy>::iterator it = enemies->begin();
    while (it != enemies->end())
    {
        if ((*it).Touch((*base).position, (*base).shape.getRadius())) {
            it = enemies->erase(it);
            BaseTakeDamage(base);
            continue;
        }
        it++;
    }
}

void CheckCollisionsBullets(std::list<Enemy>* enemies, std::list<ParticleSystem>* particleSystems, std::list<Bullet>* bullets)
{
    std::list<Enemy>::iterator it = enemies->begin();
    while (it != enemies->end())
    {
        std::list<Bullet>::iterator with = bullets->begin();
        while (with != bullets->end())
        {
            if ((*it).Touch(with->position, with->shape.getRadius())) {
                particleSystems->push_back(CreatePrefabSystem((*it).color, (*it).position));
                it = enemies->erase(it);
                bullets->erase(with);
                break;
            }
            with++;
        }
        if(it != enemies->end()) it++;
    }
}