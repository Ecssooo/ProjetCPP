#pragma once
#include <list>
#include <SFML/Graphics.hpp>

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
    
    void Change(BUTTONSTATES newState);
    bool OnClick(sf::RenderWindow* window);
};

void DrawAllButton(sf::RenderWindow* window, std::vector<Button>* buttons);