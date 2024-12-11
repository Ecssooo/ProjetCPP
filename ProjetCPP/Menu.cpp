#include "Menu.h"
#include "Windows.h"
#include "MathUtils.h"


std::string getAssetsPath() {
    char cExeFilePath[256];
    GetModuleFileNameA(NULL, cExeFilePath, 256);
    std::string exeFilePath = cExeFilePath;
    int exeNamePos = exeFilePath.find_last_of("\\/");
    std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
    return appPath + "\\Assets";
}

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

void Button::SetFont(sf::Font* font) {
    ButtonText.setFont(*font);
}

void DrawAllButton(sf::RenderWindow* window, std::vector<Button>* buttons)
{
    for(int i = 0; i < buttons->size(); i++)
    {
        if((*buttons)[i].buttonState != BUTTONSTATES::NONE)
        {
            (*buttons)[i].shape.setPosition((*buttons)[i].position);
            (*buttons)[i].shape.setOrigin({(*buttons)[i].shape.getSize().x / 2, (*buttons)[i].shape.getSize().y / 2});
            window->draw((*buttons)[i].shape);
        }
    }
}

