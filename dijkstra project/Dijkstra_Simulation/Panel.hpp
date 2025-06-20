#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Panel {
private:
    sf::RectangleShape background;
    std::vector<sf::Text> instructions;
    sf::Font font;

public:
    Panel(float width, float height, const sf::Vector2f& position, sf::Font& sharedFont);
    void setInstructions(const std::vector<std::string>& lines);
    void draw(sf::RenderWindow& window);
};
