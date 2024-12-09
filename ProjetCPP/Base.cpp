#include "Base.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Windows.h"

std::string getAppPath() {
	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256);
	std::string exeFilePath = cExeFilePath;
	int exeNamePos = exeFilePath.find_last_of("\\/");
	std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
	return appPath;
}

std::string getAssetsPath() {
	std::string basePath = getAppPath();
	basePath += "\Assets";
	return basePath;
}

Base CreateBase(sf::RenderWindow* window, int hp, float reviveTimer, float roundTimer) {
	Base base;
	base.maxHp = hp;
	base.hp = hp;
	base.revivePlayerTimer = reviveTimer;
	base.roundTimer = roundTimer;
	base.font.loadFromFile(getAssetsPath() + "\\ARIAL.TTF");
	base.timerText.setFont(base.font);
	base.timerText.setString(std::to_string((int)base.roundTimer));
	base.timerText.setCharacterSize(60);
	base.timerText.setFillColor(sf::Color::Magenta);
	base.shape.setPointCount(8);
	base.shape.setRadius(100);
	base.shape.setOrigin(sf::Vector2f{ base.shape.getRadius(), base.shape.getRadius() });
	base.position = { (float)(rand() % (int)((window->getSize().x - base.shape.getRadius()) + base.shape.getRadius())) , (float)(rand() % (int)((window->getSize().y - base.shape.getRadius()) + base.shape.getRadius()))};
	sf::Vector2f offset = { (float)(base.timerText.getCharacterSize() / 2), (float)((base.timerText.getCharacterSize() / 2) + 5) };
	base.timerText.setPosition(base.position - offset);
	base.shape.setPosition(base.position);
	base.color = sf::Color::White;
	base.shape.setFillColor(base.color);

	return base;
}

void DrawBase(Base* base, sf::RenderWindow* window) {
	window->draw(base->shape);
	window->draw(base->timerText);
}

sf::RectangleShape SetLifeBars(sf::Color color, float length, sf::RenderWindow* window) {
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f{ length, (float)(window->getSize().y / 20) });
	shape.setFillColor(color);
	shape.setPosition(sf::Vector2f{ 0, 0 });
	return shape;
}

void DrawBaseLife(Base* base, sf::RenderWindow* window) {
	sf::RectangleShape allHp;
	sf::RectangleShape remainingHp;
	allHp = SetLifeBars(sf::Color::Red, 1980, window);
	float percentageLife = (float)window->getSize().x / (float)base->maxHp;
	float length = percentageLife * base->hp;
	std::cout << base->hp << std::endl;
	remainingHp = SetLifeBars(sf::Color::Green, length, window);
	window->draw(allHp);
	window->draw(remainingHp);
}

void BaseTakeDamage(Base* base) {
	base->hp -= 1;
}