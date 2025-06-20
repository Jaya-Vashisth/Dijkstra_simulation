#include "PriorityQueuePanel.hpp"
#include <sstream>
#include <iomanip>

PriorityQueuePanel::PriorityQueuePanel() {
    font.loadFromFile("arial.ttf");
}

void PriorityQueuePanel::push(int nodeId, float dist) {
    elements.emplace_back(nodeId, dist);
}

void PriorityQueuePanel::pop() {
    if (!elements.empty())
        elements.erase(elements.begin());
}

void PriorityQueuePanel::clear() {
    elements.clear();
}

void PriorityQueuePanel::draw(sf::RenderWindow& window, sf::Vector2f position) {
    float panelWidth = 200;
    float panelHeight = 320;

    sf::RectangleShape panel(sf::Vector2f(panelWidth, panelHeight));
    panel.setPosition(position);
    panel.setFillColor(sf::Color(240, 240, 240));
    panel.setOutlineColor(sf::Color::Black);
    panel.setOutlineThickness(2);
    window.draw(panel);

    sf::Text title;
    title.setFont(font);
    title.setString("Priority Queue");
    title.setCharacterSize(18);
    title.setFillColor(sf::Color::Black);
    title.setPosition(position.x + 10, position.y + 10);
    window.draw(title);

    float offsetY = 40;
    bool alternate = false;

    for (const auto& item : elements) {
        // Background row
        sf::RectangleShape rowBg(sf::Vector2f(panelWidth - 20, 24));
        rowBg.setPosition(position.x + 10, position.y + offsetY);
        rowBg.setFillColor(alternate ? sf::Color(225, 225, 225) : sf::Color(250, 250, 250));
        window.draw(rowBg);

        std::stringstream ss;
        ss << "Node " << item.first << " (w=" << std::fixed << std::setprecision(1) << item.second << ")";

        sf::Text entry;
        entry.setFont(font);
        entry.setCharacterSize(14);
        entry.setFillColor(sf::Color(30, 90, 160));
        entry.setString(ss.str());
        entry.setPosition(position.x + 14, position.y + offsetY + 2);
        window.draw(entry);

        offsetY += 26;
        alternate = !alternate;
    }
}
