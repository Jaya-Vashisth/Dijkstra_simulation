#include "InputBox.hpp"

InputBox::InputBox() {
    font.loadFromFile("arial.ttf");

    box.setSize(sf::Vector2f(300, 50));
    box.setFillColor(sf::Color(255, 255, 255));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(box.getPosition().x + 10, box.getPosition().y + 10);

    active = false;
    input = "";
}

void InputBox::setPosition(const sf::Vector2f& pos) {
    box.setPosition(pos);
    text.setPosition(pos.x + 10, pos.y + 10);
}

void InputBox::activate() {
    input.clear();
    text.setString("");
    active = true;
}

void InputBox::deactivate() {
    active = false;
}

bool InputBox::isActive() const {
    return active;
}

std::string InputBox::getInput() const {
    return input;
}

void InputBox::handleEvent(const sf::Event& event) {
    if (!active) return;

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') {
            if (!input.empty()) {
                input.pop_back();
                text.setString(input);
            }
        }
        else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
            deactivate(); // Enter key pressed
        }
        else if (event.text.unicode < 128) {
            input += static_cast<char>(event.text.unicode);
            text.setString(input);
        }
    }
}

void InputBox::draw(sf::RenderWindow& window) {
    if (!active) return;
    window.draw(box);
    window.draw(text);
}