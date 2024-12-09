#include "Menu.h"

#include "MathUtils.h"

void Button::ChangeText(BUTTONSTATES newState)
{
    switch(newState)
    {
        default:
            text = "Button";
            break;
        case(BUTTONSTATES::QUIT):
            text = "Quit";
            buttonState = newState;
            break;
        case(BUTTONSTATES::RESUME):
            text = "Resume";
            buttonState = newState;
            break;
        case(BUTTONSTATES::RETRY):
            text = "Retry";
            buttonState = newState;
            break;
    }
}

bool Button::OnClick(sf::RenderWindow* window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    return IIM::IsOverlappingBoxOnBox(this->position, this->shape.getSize(), (sf::Vector2f)mousePosition, {0.1f,0.1f});
}
