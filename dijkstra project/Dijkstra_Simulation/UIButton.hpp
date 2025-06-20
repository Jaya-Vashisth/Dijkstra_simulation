#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class UIButton {
private:
    sf::RectangleShape shape;
    sf::Text label;
    std::function<void()> callback;
    bool isHovered = false;

public:
    UIButton(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, sf::Font& font);

    void setCallback(std::function<void()> func);
    void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos);
    void draw(sf::RenderWindow& window);
    void setFillColor(const sf::Color& color);
    bool isClicked(const sf::Vector2f& mousePos) const;
    sf::FloatRect getBounds() const; // <-- Used in main.cpp
    bool contains(const sf::Vector2f& point) const; // <-- Used in main.cpp
};
