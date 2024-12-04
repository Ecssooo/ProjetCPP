#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"


void CheckColision(std::list<Enemy>* enemies, std::vector<Player>* players, std::list<Bullet>* bullets);