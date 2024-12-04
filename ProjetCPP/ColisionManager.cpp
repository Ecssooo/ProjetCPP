#include "ColisionManager.h"

void CheckColision(std::list<Enemy>* enemies, std::vector<Player>* players, std::list<Bullet>* bullets)
{
    std::list<Enemy>::iterator it = enemies->begin();
    while (it != enemies->end())
    {
        for (int i = 0; i < players->size(); i++)
        {
            if ((*it).Touch((*players)[i].position, (*players)[i].shape.getRadius())) {
                it = enemies->erase(it);
                return;
            }
        }
        std::list<Bullet>::iterator with = bullets->begin();
        while (with != bullets->end())
        {
            if ((*it).Touch(with->position, with->shape.getRadius())) {
                it = enemies->erase(it);
                bullets->erase(with);
                return;
            }
            with++;
        }
        it++;
    }
}