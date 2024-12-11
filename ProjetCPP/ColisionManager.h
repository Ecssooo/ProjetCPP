#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "Base.h"
#include "ParticleSystem.h"



void CheckCollisionsPlayers(std::list<Enemy>* enemies, std::list<ParticleSystem>* particleSystems, std::vector<Player>* players);
void CheckCollisionsBase(std::list<Enemy>* enemies, Base* base);
void CheckCollisionsBullets(std::list<Enemy>* enemies, std::list<ParticleSystem>* particleSystems, std::list<Bullet>* bullets);