#pragma once
#include <SFML/Graphics.hpp>

class Node {
public:
    int id;
    sf::Vector2f position;
    sf::CircleShape shape;
    sf::Text label;

    Node(int id, sf::Vector2f position, const sf::Font& font);

    void markAsStart();
    void markAsDestination();
    void resetColor();
    void draw(sf::RenderWindow& window);
    bool contains(sf::Vector2f point) const;
    void setLabel(const std::string& labelText);

};
