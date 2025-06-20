#include "UIButton.hpp"

UIButton::UIButton(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, sf::Font& font) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color(200, 200, 200));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2.f);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(14);
    label.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    label.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f - 4);
}

bool UIButton::isClicked(const sf::Vector2f& mousePos) const {
    return shape.getGlobalBounds().contains(mousePos);
}

void UIButton::handleEvent(const sf::Event& event, const sf::Vector2f& mousePos) {
    if (shape.getGlobalBounds().contains(mousePos)) {
        isHovered = true;
        shape.setFillColor(sf::Color(180, 180, 180));
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left &&
            callback)
            callback();
    }
    else {
        isHovered = false;
        shape.setFillColor(sf::Color(200, 200, 200));
    }
}

void UIButton::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

void UIButton::setFillColor(const sf::Color& color) {
    shape.setFillColor(color);
}

sf::FloatRect UIButton::getBounds() const {
    return shape.getGlobalBounds();
}

bool UIButton::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}
