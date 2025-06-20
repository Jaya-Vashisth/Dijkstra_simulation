#include "Node.hpp"

Node::Node(int id, sf::Vector2f position, const sf::Font& font)
    : id(id), position(position)
{
    shape.setRadius(22);
    shape.setOrigin(22, 22); // Center the circle
    shape.setPosition(position);
    shape.setFillColor(sf::Color(255, 255, 255));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2);

    label.setFont(font);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color::Black);

    std::string labelStr = std::to_string(id);
    label.setString(labelStr);

    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.width / 2, textBounds.height / 2 + 5);
    label.setPosition(position);
}

void Node::markAsStart() {
    shape.setFillColor(sf::Color(100, 200, 255)); // Cyan
    label.setString("S");
}

void Node::markAsDestination() {
    shape.setFillColor(sf::Color(255, 150, 200)); // Magenta
    label.setString("D");
}

void Node::resetColor() {
    shape.setFillColor(sf::Color(255, 255, 255));
    label.setString(std::to_string(id));
}

bool Node::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}

void Node::setLabel(const std::string& labelText) {
    label.setString(labelText);
}


void Node::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}
