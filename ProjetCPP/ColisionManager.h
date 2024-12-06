#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"


void CheckCollision(std::list<Enemy>* enemies, std::vector<Player>* players, std::list<Bullet>* bullets);