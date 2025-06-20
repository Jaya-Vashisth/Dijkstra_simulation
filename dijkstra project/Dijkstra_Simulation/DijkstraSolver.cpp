#include "DijkstraSolver.hpp"
#include <queue>
#include <thread>
#include <chrono>
#include <limits>
#include <algorithm>

DijkstraSolver::DijkstraSolver(Graph* graph, PriorityQueuePanel& queuePanel, sf::RenderWindow& window)
    : graph(graph), queuePanel(queuePanel), window(window), currentStep(0), complete(false) {
}

std::vector<int> DijkstraSolver::run(int startId, int endId) {
    prepareSteps(startId, endId);

    while (!complete && currentStep < visitOrder.size()) {
        stepForward();
    }

    std::vector<int> path;
    if (distances[endId] == std::numeric_limits<float>::infinity())
        return path;

    for (int at = endId; at != startId; at = previous[at]) {
        path.push_back(at);
    }
    path.push_back(startId);
    std::reverse(path.begin(), path.end());
    return path;
}

void DijkstraSolver::prepareSteps(int startId, int endId) {
    distances.clear();
    previous.clear();
    visited.clear();
    visitOrder.clear();
    queuePanel.clear();
    currentStep = 0;
    complete = false;

    for (auto& node : graph->getNodes()) {
        distances[node->id] = std::numeric_limits<float>::infinity();
        visited[node->id] = false;
    }

    distances[startId] = 0;
    std::set<int> pq;
    pq.insert(startId);
    queuePanel.push(startId, 0);

    while (!pq.empty()) {
        int current = *pq.begin();
        pq.erase(pq.begin());

        if (visited[current]) continue;
        visited[current] = true;
        visitOrder.push_back(current);

        if (current == endId) break;

        for (Edge* edge : graph->getEdges()) {
            if (edge->from->id == current) {
                int neighbor = edge->to->id;
                float alt = distances[current] + edge->weight;
                if (alt < distances[neighbor]) {
                    distances[neighbor] = alt;
                    previous[neighbor] = current;
                    pq.insert(neighbor);
                    queuePanel.push(neighbor, alt);
                }
            }
        }
    }

    complete = true;
}

void DijkstraSolver::stepForward() {
    if (currentStep >= visitOrder.size()) return;
    int nodeId = visitOrder[currentStep];
    visualizeStep(nodeId);
    currentStep++;
}

void DijkstraSolver::stepBackward() {
    if (currentStep == 0) return;
    currentStep--;
    int nodeId = visitOrder[currentStep];
    Node* node = graph->getNodeById(nodeId);
    if (node) node->shape.setFillColor(sf::Color::White);

    window.clear(sf::Color::White);
    graph->draw(window);
    queuePanel.draw(window, { window.getSize().x - 210.f, 10.f });
    window.display();
}

bool DijkstraSolver::isComplete() const {
    return complete;
}

void DijkstraSolver::reset() {
    currentStep = 0;
    complete = false;
    visitOrder.clear();
    distances.clear();
    previous.clear();
    visited.clear();
    queuePanel.clear();
}

void DijkstraSolver::visualizeStep(int current) {
    Node* node = graph->getNodeById(current);
    if (node) node->shape.setFillColor(sf::Color::Yellow);

    window.clear(sf::Color::White);
    graph->draw(window);
    queuePanel.draw(window, { window.getSize().x - 210.f, 10.f });
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
}

void DijkstraSolver::colorPath(const std::vector<int>& path) {
    for (int id : path) {
        Node* node = graph->getNodeById(id);
        if (node) node->shape.setFillColor(sf::Color::Green);

        window.clear(sf::Color::White);
        graph->draw(window);
        queuePanel.draw(window, { window.getSize().x - 210.f, 10.f });
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
    }
}
