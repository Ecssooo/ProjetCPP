#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "Base.h"
#include "ParticleSystem.h"



void CheckCollisions(std::list<Enemy>* enemies, std::list<ParticleSystem>* particleSystems, std::vector<Player>* players, std::list<Bullet>* bullets, Base* base);