#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
#include <iostream>

inline std::string InputBoxA(const std::string& prompt) {
    char buffer[256] = "";
    if (MessageBoxA(NULL, prompt.c_str(), "Input", MB_OKCANCEL | MB_ICONQUESTION) == IDOK) {
        std::cout << prompt << ": ";
        std::cin.getline(buffer, 256);
        return std::string(buffer);
    }
    return "";
}

class InputBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;
    std::string input;
    bool active;

public:
    InputBox();
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& pos);
    void activate();
    void deactivate();
    bool isActive() const;
    std::string getInput() const;
};
