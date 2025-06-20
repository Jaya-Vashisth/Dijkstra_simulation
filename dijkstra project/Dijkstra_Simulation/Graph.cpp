#include "Graph.hpp"

Graph::Graph() {
    font.loadFromFile("arial.ttf");
}

Graph::~Graph() {
    clear();
}

void Graph::addNode(const sf::Vector2f& position) {
    size_t id = nodes.size();
    Node* node = new Node(id, position, font);
    nodes.push_back(node);
}

void Graph::addEdge(Node* from, Node* to, float weight) {
    if (!from || !to || from == to)
        return;

    for (Edge* edge : edges) {
        if (edge->connects(from, to))
            return; // avoid duplicate
    }

    Edge* edge = new Edge(from, to, weight, font);
    edges.push_back(edge);
}

Node* Graph::getNodeAt(const sf::Vector2f& point) {
    for (Node* node : nodes) {
        if (node->contains(point))
            return node;
    }
    return nullptr;
}

Node* Graph::getNodeById(int id) {
    if (id >= 0 && id < static_cast<int>(nodes.size()))
        return nodes[id];
    return nullptr;
}

const std::vector<Node*>& Graph::getNodes() const {
    return nodes;
}

const std::vector<Edge*>& Graph::getEdges() const {
    return edges;
}

void Graph::draw(sf::RenderWindow& window) {
    for (Edge* edge : edges)
        edge->draw(window);
    for (Node* node : nodes)
        node->draw(window);
}

void Graph::resetNodeLabels() {
    for (auto& node : nodes) {
        node->resetColor();
    }
}

void Graph::resetColors() {
    for (Node* node : nodes) {
        node->shape.setFillColor(sf::Color::White);
    }

    for (Edge* edge : edges) {
        edge->line[0].color = sf::Color::Black;
        edge->line[1].color = sf::Color::Black;
    }
}



void Graph::clear() {
    for (Node* node : nodes)
        delete node;
    for (Edge* edge : edges)
        delete edge;
    nodes.clear();
    edges.clear();
}
