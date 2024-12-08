#include "GameManager.h"

int PlayerAlive(std::vector<Player>* players)
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