#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "Edge.hpp"

class Graph {
private:
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;
    sf::Font font;

public:
    Graph();
    ~Graph();

    void addNode(const sf::Vector2f& position);
    void addEdge(Node* from, Node* to, float weight);
    Node* getNodeAt(const sf::Vector2f& point);
    Node* getNodeById(int id);
    void resetColors();
    const std::vector<Node*>& getNodes() const;
    const std::vector<Edge*>& getEdges() const;
    void draw(sf::RenderWindow& window);
    void resetNodeLabels();
    void clear();
};
