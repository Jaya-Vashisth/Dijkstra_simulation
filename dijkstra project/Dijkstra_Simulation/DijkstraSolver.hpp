#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "PriorityQueuePanel.hpp"

class DijkstraSolver {
private:
    Graph* graph;
    std::map<int, float> distances;
    std::map<int, int> previous;
    std::map<int, bool> visited;
    PriorityQueuePanel& queuePanel;
    sf::RenderWindow& window;
    std::vector<int> visitOrder;
    size_t currentStep;
    bool complete;

public:
    DijkstraSolver(Graph* graph, PriorityQueuePanel& queuePanel, sf::RenderWindow& window);

    std::vector<int> run(int startId, int endId); // full execution once
    void stepForward();
    void stepBackward();
    bool isComplete() const;
    void reset();

    void prepareSteps(int startId, int endId);
    void visualizeStep(int current);
    void colorPath(const std::vector<int>& path);

    const std::map<int, float>& getDistances() const { return distances; }
    const std::map<int, int>& getPrevious() const { return previous; }
    const std::map<int, bool>& getVisited() const { return visited; }
};
