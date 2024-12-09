#pragma once
#include "SFML/Graphics.hpp"


struct Base {
	int maxHp;
	int hp;
	float roundTimer;
	float revivePlayerTimer;
	sf::Text timerText;
	sf::Font font;

	sf::CircleShape shape;
	sf::Color color;
	sf::Vector2f position;


	
};

void DrawBase(Base* base, sf::RenderWindow* window);
void DrawBaseLife(Base* base, sf::RenderWindow* window);
void BaseTakeDamage(Base* base);
Base CreateBase(sf::RenderWindow* window, int hp, float reviveTimer, float roundTimer);