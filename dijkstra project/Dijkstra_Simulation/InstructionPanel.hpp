#pragma once
#include <SFML/Graphics.hpp>

class InstructionPanel {
private:
    sf::Font font;

public:
    InstructionPanel();
    void draw(sf::RenderWindow& window, sf::Vector2f position);
};