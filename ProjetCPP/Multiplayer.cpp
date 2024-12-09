#include "Multiplayer.h"

sf::Color PlayerColor(int id) {
    std::vector<sf::Color> ColorList = {
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color(226, 133, 110, 255),
        sf::Color(236, 240, 241, 255),
        sf::Color(97, 155, 138, 255)
    };
    return ColorList[id];
}

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
    int i = 0;
    while (it != JosticksID.end()) {
        if (sf::Joystick::isConnected(*it)) {
            float pos = 100.f * (*it) + 300.f;
            (*players).push_back(CreatePlayer((*it), 3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ pos ,300 }, bullet, 0.5f, PlayerColor(i)));
        }
        i++;
        it++;
    }
}

void CheckJoystick(std::list<int> JosticksID, std::vector<sf::Vector2f>* inputs, std::vector<Player>* players, Bullet* bullet) {
    std::list<int>::iterator it = JosticksID.begin();
    int  i = 0;
    while (it != JosticksID.end()) {
        if (sf::Joystick::isConnected(*it) && !CheckPlayerExist((*it), players) && (*it) != 0) {
            float pos = 100.f * (*it) + 300.f;
            (*players).push_back(CreatePlayer((*it), 3, 200, sf::CircleShape{ 20, 3 }, sf::Vector2f{ pos,300 }, bullet, 0.5f, PlayerColor(i)));
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
        i++;
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

void GetReadyInputs(std::list<int> JosticksID, std::vector<Player>* players)
{
    std::list<int>::iterator joystickIterator = JosticksID.begin();
    while(joystickIterator != JosticksID.end())
    {
        if(sf::Joystick::isButtonPressed((*joystickIterator),0))
        {
            (*players)[(*joystickIterator)].playerStates = PLAYERSTATES::READY;
        }
        joystickIterator++;
    }
}