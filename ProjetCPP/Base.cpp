#include "Base.h"


Base CreateBase(sf::RenderWindow* window, int hp, float reviveTimer, float roundTimer) {
	Base base {hp, hp,roundTimer,reviveTimer};

	//Text timer
	base.font.loadFromFile(GetFont());
	base.timerText.setFont(base.font);
	base.timerText.setString(std::to_string((int)base.roundTimer));
	base.timerText.setCharacterSize(40);
	base.timerText.setFillColor(sf::Color::Magenta);

	//Shape
	base.shape.setPointCount(8);
	base.shape.setRadius(75);
	base.shape.setOrigin(sf::Vector2f{ base.shape.getRadius(), base.shape.getRadius() });
	base.color = sf::Color::White;
	base.shape.setFillColor(base.color);

	//Position
	float x = rand() % (int)(window->getSize().x - base.shape.getRadius() * 2) + base.shape.getRadius();
	float y = rand() % (int)(window->getSize().y - (base.shape.getRadius() * 2 + window->getSize().y / 20)) + base.shape.getRadius();
	base.position = {  x, y};
	sf::Vector2f offset = { (float)(base.timerText.getCharacterSize() / 2), (float)((base.timerText.getCharacterSize() / 2) + 5) };
	base.timerText.setPosition(base.position - offset);
	base.shape.setPosition(base.position);

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
	shape.setPosition(sf::Vector2f{ 0, (float)window->getSize().y - shape.getSize().y});
	return shape;
}

void DrawBaseLife(Base* base, sf::RenderWindow* window) {
	sf::RectangleShape allHp;
	sf::RectangleShape remainingHp;
	allHp = SetLifeBars(sf::Color::Red, (float)window->getSize().x, window);
	float percentageLife = (float)window->getSize().x / (float)base->maxHp;
	float length = percentageLife * base->hp;
	remainingHp = SetLifeBars(sf::Color::Green, length, window);
	window->draw(allHp);
	window->draw(remainingHp);
}

void Base::BaseTakeDamage(int damage) {
	this->hp -= damage;
}

void Base::BaseRevive(sf::RenderWindow* window) {
	this->hp = this->maxHp;
	float x = rand() % (int)(window->getSize().x - this->shape.getRadius() * 2) + this->shape.getRadius();
	float y = rand() % (int)(window->getSize().y - (this->shape.getRadius() * 2 + window->getSize().y / 20)) + this->shape.getRadius();
	this->position = {x, y};
	this->shape.setPosition(this->position);
	sf::Vector2f offset = { (float)(this->timerText.getCharacterSize() / 2), (float)((this->timerText.getCharacterSize() / 2) + 5) };
	this->timerText.setPosition(this->position - offset);
}

bool Base::IsBaseAlive() {
	return this->hp > 0;
}