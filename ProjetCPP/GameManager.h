#pragma once
#include "Player.h"


enum class GAMESTATES
{
    START,
    PAUSE,
    END,
    ROUNDINPROGRESS,
    REVIVE
};

int PlayersDead(std::vector<Player>* players);
bool Timer(float deltatime, float* currentTimer, float maxTimer);