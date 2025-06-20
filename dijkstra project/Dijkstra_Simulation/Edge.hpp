#pragma once
#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Edge {
public:
    Node* from;
    Node* to;
    float weight;
    sf::Text label;
    sf::VertexArray line;

    Edge(Node* from, Node* to, float weight, const sf::Font& font);

    void updateLabel();
    bool connects(Node* a, Node* b) const;
    void draw(sf::RenderWindow& window);
};
