#include "Multiplayer.h"


int GetNbJostick(std::list<int> JosticksID) {
    std::list<int>::iterator it = JosticksID.begin();
    int nbJosticks = 0;
    while (it != JosticksID.end()) {
        if (sf::Joystick::isConnected((*it)))
        {
            nbJosticks++;
        }
        it++;
    }
    return nbJosticks;
}

void InitPlayers(std::list<int> JosticksID, std::vector<Player>* players, Bullet* bullet) {
    players->clear();
    std::list<int>::iterator it = JosticksID.begin();
    while (it != JosticksID.end()) {
        if (sf::Joystick::isConnected(*it)) {
            float pos = 100.f * (*it) + 300.f;
            (*players).push_back(CreatePlayer((*it), 3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ pos ,300 }, bullet, 0.5f));
        }
        it++;
    }
}

void CheckJoystick(std::list<int> JosticksID, std::vector<sf::Vector2f>* inputs, std::vector<Player>* players, Bullet* bullet) {
    std::list<int>::iterator it = JosticksID.begin();
    while (it != JosticksID.end()) {
        if (sf::Joystick::isConnected(*it) && !CheckPlayerExist((*it), players) && (*it) != 0) {
            float pos = 100.f * (*it) + 300.f;
            (*players).push_back(CreatePlayer((*it), 3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ pos,300 }, bullet, 0.5f));
        }
        else if (!sf::Joystick::isConnected(*it) && CheckPlayerExist((*it), players) && (*it) != 0) {
            std::vector<Player>::iterator that = (*players).begin();
            for (int i = 0; i < 8; i++) {

                if ((*it) == (*players)[i].id) {
                    (*players).erase(that);
                    return;
                }
                that++;
            }
        }
        it++;
    }
}

bool CheckPlayerExist(int id, std::vector<Player>* players) {
    for (int i = 0; i < players->size(); i++)
    {
        if ((*players)[i].id == id) return true;
    }
    return false;
}

void GetInputs(std::list<int> JosticksID, std::vector<sf::Vector2f>* inputs) {
    std::list<int>::iterator it = JosticksID.begin();
    while (it != JosticksID.end()) {
        if (sf::Joystick::isConnected(*it))
        {
            (*inputs)[(*it)] = { sf::Joystick::getAxisPosition(*it, sf::Joystick::X) / 100.0f,sf::Joystick::getAxisPosition(*it, sf::Joystick::Y) / 100.0f };
        }
        it++;
    }
}