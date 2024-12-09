#pragma once
#include <SFML/Graphics.hpp>

enum class BUTTONSTATES
{
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
    
    void ChangeText(BUTTONSTATES newState);
    bool OnClick(sf::RenderWindow* window);
};


