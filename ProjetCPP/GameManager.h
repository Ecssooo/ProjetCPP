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

int PlayerAlive(std::vector<Player>* players);
