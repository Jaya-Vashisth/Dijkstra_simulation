#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class PriorityQueuePanel {
private:
    std::vector<std::pair<int, float>> elements;
    sf::Font font;

public:
    PriorityQueuePanel();
    void push(int nodeId, float dist);
    void pop();
    void clear();
    void draw(sf::RenderWindow& window, sf::Vector2f position);
};
