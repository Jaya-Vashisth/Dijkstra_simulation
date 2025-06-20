#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include <iostream>
#include "Graph.hpp"
#include "DijkstraSolver.hpp"
#include "PriorityQueuePanel.hpp"
#include "Panel.hpp"
#include "UIButton.hpp"
#include "InputBox.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Dijkstra Visualizer");
    sf::Font font;
    font.loadFromFile("arial.ttf");

    Graph graph;
    PriorityQueuePanel queuePanel;
    DijkstraSolver solver(&graph, queuePanel, window);


	// Set up the instruction panel
    Panel instructionPanel(270, 170, { 10, 10 }, font);
    instructionPanel.setInstructions({
        "1. Left click: Add node",
        "2. Click two nodes: Create edge",
        "3. Press 'S': Set start node",
        "4. Press 'E': Set end node",
        "5. Press 'R': Reset",
        "6. Press SPACE: Start/Repeat"
        });
   
	//set up the buttons for next and previous steps
    UIButton nextButton({ window.getSize().x - 200.f, 650.f }, { 100.f, 40.f }, "Next", font);
    UIButton prevButton({ window.getSize().x - 100.f, 650.f }, { 100.f, 40.f }, "Prev", font);


    
    int startId = -1, endId = -1;
    Node* selected1 = nullptr;
    Node* selected2 = nullptr;
    std::vector<int> finalPath;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (nextButton.isClicked(mousePos)) {
                    if (!solver.isComplete())
                        solver.stepForward();
                    continue;
                }

                if (prevButton.isClicked(mousePos)) {
                    solver.stepBackward();
                    continue;
                }

                // Prevent drawing behind side panels
                if (mousePos.x <= 240 || mousePos.x >= window.getSize().x - 240)
                    continue;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    Node* clicked = graph.getNodeAt(mousePos);
                    if (clicked) {
                        if (!selected1) {
                            selected1 = clicked;
                        }
                        else if (!selected2 && clicked != selected1) {
                            selected2 = clicked;

                            std::string input = InputBoxA("Enter weight between node " + std::to_string(selected1->id) + " and " + std::to_string(selected2->id));
                            try {
                                float weight = std::stof(input);
                                graph.addEdge(selected1, selected2, weight);
                            }
                            catch (...) {
                                MessageBoxA(NULL, "Invalid weight!", "Error", MB_OK);
                            }

                            selected1 = selected2 = nullptr;
                        }
                    }
                    else {
                        graph.addNode(mousePos);
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                Node* clicked = graph.getNodeAt(mousePos);

                if (event.key.code == sf::Keyboard::S && clicked) {
                    startId = clicked->id;
                    clicked->shape.setFillColor(sf::Color::Cyan);
                    clicked->setLabel("S");
                }

                if (event.key.code == sf::Keyboard::E && clicked) {
                    endId = clicked->id;
                    clicked->shape.setFillColor(sf::Color::Magenta);
                    clicked->setLabel("D");
                }

                if (event.key.code == sf::Keyboard::Space) {
                    if (solver.isComplete()) {
                        solver.reset();
                        graph.resetNodeLabels();
                        graph.resetColors();
                        finalPath.clear();
                        continue;
                    }

                    if (startId != -1 && endId != -1) {
                        finalPath = solver.run(startId, endId);
                        solver.colorPath(finalPath);
                    }
                    else {
                        MessageBoxA(NULL, "Select both Start and End nodes!", "Warning", MB_OK);
                    }
                }

                if (event.key.code == sf::Keyboard::R) {
                    graph.clear();
                    solver.reset();
                    startId = endId = -1;
                    selected1 = selected2 = nullptr;
                    finalPath.clear();
                }
            }
        }

        window.clear(sf::Color::White);
        graph.draw(window);
        instructionPanel.draw(window);
        queuePanel.draw(window, { window.getSize().x - 210.f, 10.f });

        nextButton.draw(window);
        prevButton.draw(window);
        window.display();
    }

    return 0;
}
