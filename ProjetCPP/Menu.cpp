#include "Menu.h"
#include "MathUtils.h"
#include "Font.h"
#include <iostream>


void Button::Change(BUTTONSTATES newState)
{
    switch(newState)
    {
        default:
            text = "Button";
            break;
        case(BUTTONSTATES::QUIT):
            text = "Quit";
            ButtonText.setString(text);
            buttonState = newState;
            break;
        case(BUTTONSTATES::RESUME):
            text = "Resume";
            ButtonText.setString(text);
            buttonState = newState;
            break;
        case(BUTTONSTATES::RETRY):
            text = "Retry";
            ButtonText.setString(text);
            buttonState = newState;
            break;
    }
}

bool Button::OnClick(sf::RenderWindow* window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    if(IIM::IsOverlappingBoxOnBox(this->position, this->shape.getSize(), (sf::Vector2f)mousePosition, {0.1f,0.1f}))
    {
        this->shape.setFillColor(sf::Color {200, 200, 200});
        return sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
    this->shape.setFillColor(sf::Color::White);
    return false;
}

void DrawAllButton(sf::RenderWindow* window, std::vector<Button>* buttons)
{
    for(int i = 0; i < buttons->size(); i++)
    {
        if ((*buttons)[i].buttonState != BUTTONSTATES::NONE)
        {
            (*buttons)[i].ButtonText.setPosition((*buttons)[i].position);
            (*buttons)[i].ButtonText.setFont((*buttons)[i].font);
            (*buttons)[i].ButtonText.setFillColor(sf::Color::Black);
            (*buttons)[i].ButtonText.setCharacterSize(40);
            (*buttons)[i].ButtonText.setOrigin({ (*buttons)[i].ButtonText.getLocalBounds().getSize().x / 2, (*buttons)[i].ButtonText.getLocalBounds().getSize().y / 2 });
            (*buttons)[i].shape.setPosition((*buttons)[i].position);
            (*buttons)[i].shape.setOrigin({ (*buttons)[i].shape.getSize().x / 2, (*buttons)[i].shape.getSize().y / 2 });
            window->draw((*buttons)[i].shape);
            window->draw((*buttons)[i].ButtonText);
        }
    }
}

Button CreateButton(std::string text, sf::Vector2f position, sf::RectangleShape shape, BUTTONSTATES state) {
    Button tempButton;
    tempButton.text = text;
    tempButton.position = position;
    tempButton.shape = shape;
    tempButton.buttonState = state;
    tempButton.font.loadFromFile(GetFont() + "\\ARIAL.TTF");
    //tempButton.ButtonText.setString("AAAAAAA");
    return tempButton;

}
