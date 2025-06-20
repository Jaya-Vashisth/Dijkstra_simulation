#include "Edge.hpp"
#include <sstream>
#include <iomanip>

Edge::Edge(Node* from, Node* to, float weight, const sf::Font& font)
    : from(from), to(to), weight(weight)
{
    line = sf::VertexArray(sf::Lines, 2);
    line[0].position = from->position;
    line[0].color = sf::Color::Black;
    line[1].position = to->position;
    line[1].color = sf::Color::Black;

    label.setFont(font);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color(80, 80, 80));

    updateLabel();
}

bool Edge::connects(Node* a, Node* b) const {
    return (from == a && to == b) || (from == b && to == a);
}

void Edge::updateLabel() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << weight;
    label.setString(ss.str());

    sf::Vector2f mid(
        (from->position.x + to->position.x) / 2.0f,
        (from->position.y + to->position.y) / 2.0f - 10.0f // Shift above the line
    );
    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin(bounds.width / 2, bounds.height / 2 + 4);
    label.setPosition(mid);
}

void Edge::draw(sf::RenderWindow& window) {
    window.draw(line);
    window.draw(label);
}
