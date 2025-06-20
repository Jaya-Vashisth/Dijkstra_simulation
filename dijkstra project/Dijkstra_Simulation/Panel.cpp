#include "Panel.hpp"


// Constructor to initialize the panel with a specific width, height, position, and shared font
Panel::Panel(float width, float height, const sf::Vector2f& position, sf::Font& sharedFont) {
    background.setSize(sf::Vector2f(width, height));
    background.setPosition(position);
    background.setFillColor(sf::Color(245, 245, 245));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2);
    font = sharedFont; // copy the reference
}



//set the instructions for the panel
void Panel::setInstructions(const std::vector<std::string>& lines) {
    instructions.clear();
    float y = background.getPosition().y + 20;


	//loop through each line(instruction) and create a text object
    for (const auto& line : lines) {
        sf::Text text;
        text.setFont(font);
        text.setString(line);
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::Black);
        text.setPosition(background.getPosition().x + 10, y);
        instructions.push_back(text);
		y += 26; // add some space between lines
    }
}

//draw the panel and its instructions
void Panel::draw(sf::RenderWindow& window) {
    window.draw(background);
    for (const auto& text : instructions)
        window.draw(text);
}
