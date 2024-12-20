#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "player.h"

sf::Color PlayerColor(int id);

int GetNbJostick(std::list<int> JosticksID);

void InitPlayers(std::list<int> JosticksID, std::vector<Player>* players, Bullet* bullet);
void CheckJoystick(std::list<int> JosticksID, std::vector<sf::Vector2f>* inputs, std::vector<Player>* players, Bullet* bullet);
bool CheckPlayerExist(int id, std::vector<Player>* players);
void GetMovementInputs(std::list<int> JosticksID, std::vector<sf::Vector2f>* inputs);
void GetReadyInputs(std::list<int> JosticksID, std::vector<Player>* players);
bool GetPauseInput(std::list<int> JosticksID);