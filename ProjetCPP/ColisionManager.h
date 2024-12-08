#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "ParticleSystem.h"



void CheckCollision(std::list<Enemy>* enemies, std::list<ParticleSystem>* particleSystems, std::vector<Player>* players, std::list<Bullet>* bullets);