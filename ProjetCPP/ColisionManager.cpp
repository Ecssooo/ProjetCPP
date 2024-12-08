#include "ColisionManager.h"

void CheckCollision(std::list<Enemy>* enemies, std::list<ParticleSystem>* particleSystems, std::vector<Player>* players, std::list<Bullet>* bullets)
{
    std::list<Enemy>::iterator it = enemies->begin();
    while (it != enemies->end())
    {
        for (int i = 0; i < players->size(); i++)
        {
            if ((*it).Touch((*players)[i].position, (*players)[i].shape.getRadius())) {
                it = enemies->erase(it);
                (*players)[i].TakeDamage();
                if ((*players)[i].hp <= 0) {
                    std::vector<Player>::iterator that = (*players).begin();
                    for (int i = 0; i < 8; i++) {

                        if (that->id == (*players)[i].id) {
                            (*players).erase(that);
                            return;
                        }
                        that++;
                    }
                }
                return;
            }
        }
        std::list<Bullet>::iterator with = bullets->begin();
        while (with != bullets->end())
        {
            if ((*it).Touch(with->position, with->shape.getRadius())) {
                particleSystems->push_back(CreatePrefabSystem((*it).color, (*it).position));
                it = enemies->erase(it);
                bullets->erase(with);
                return;
            }
            with++;
        }
        it++;
    }
}