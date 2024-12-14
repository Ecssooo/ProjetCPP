#include "GameManager.h"

int PlayersDead(std::vector<Player>* players)
{
    int playersAlive = 0;
    std::vector<Player>::iterator it = players->begin();
    while(it != players->end())
    {
        if((*it).playerStates == PLAYERSTATES::DEAD)
        {
            playersAlive++;
        }
        it++;
    }
    return playersAlive;
}

bool Timer(float deltatime, float* currentTimer, float maxTimer)
{
    (*currentTimer) += deltatime;
    if((*currentTimer >= maxTimer))
    {
        return true;
    }
    return false;
}
