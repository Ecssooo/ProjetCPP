#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "MathUtils.h"
#include "Font.h"
#include <iostream>

enum class BUTTONSTATES
{
    NONE,
    RESUME,
    RETRY,
    QUIT,
};

struct Button
{
    std::string text;
    sf::Vector2f position;
    sf::RectangleShape shape;
    BUTTONSTATES buttonState;
    sf::Font font;
    sf::Text ButtonText;
    

    void Change(BUTTONSTATES newState);
    bool OnClick(sf::RenderWindow* window);
};

struct Text
{
    std::string text;
    sf::Vector2f position;
    sf::Font font;
    sf::Text ShowText;
};

void DrawAllButton(sf::RenderWindow* window, std::vector<Button>* buttons);
Button CreateButton(std::string text, sf::Vector2f position, sf::RectangleShape shape, BUTTONSTATES state);

Text CreateText(std::string text, sf::Vector2f position);
void DrawStartText(sf::RenderWindow* window, Text text);
void DrawWaveText(sf::RenderWindow* window, Text text, int wave);