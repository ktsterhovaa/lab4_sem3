
#ifndef LABR4_MENUFUNC_H
#define LABR4_MENUFUNC_H
#include <iostream>
#include "Graph.h"
void displayGraph(Graph<int>& graph) {
    for (int i = 0; i < graph.GetSize(); ++i) {
        int vertexName = i + 1;

        if (graph.SearchVertex(vertexName)) {
            const Vertex<int>& vertex = graph.Get(vertexName);
            std::cout << "Vertex: " << vertex.GetName() << " -> ";

            const auto& edges = vertex.GetEdges();
            if (edges.empty()) {
                std::cout << "No outgoing edges." << std::endl;
            } else {
                for (const auto& edge : edges) {
                    std::cout << edge.GetLast() << " (weight: " << edge.GetWeight() << "), ";
                }
                std::cout << std::endl;
            }
        } else {
            std::cout << "Vertex " << vertexName << " not found." << std::endl;
        }
    }
}

void runMenu() {
    Graph<int> graph;
    int choice;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add vertex\n";
        std::cout << "2. Add arc\n";
        std::cout << "3. Remove arc\n";
        std::cout << "4. Remove vertex\n";
        std::cout << "5. Topological sort\n";
        std::cout << "6. Dijkstra's algorithm\n";
        std::cout << "7. Generate random graph\n";
        std::cout << "8. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int vertex;
                std::cout << "Enter the name of the vertex: ";
                std::cin >> vertex;
                graph.AddVertex(vertex);
                displayGraph(graph);
                break;
            }
            case 2: {
                int vertex1, vertex2, weight;
                std::cout << "Enter the name of the first vertex: ";
                std::cin >> vertex1;
                std::cout << "Enter the name of the second vertex: ";
                std::cin >> vertex2;
                std::cout << "Enter the weight: ";
                std::cin >> weight;
                graph.AddArc(vertex1, vertex2, weight);
                displayGraph(graph);
                break;
            }
            case 3: {
                int vertex1, vertex2;
                std::cout << "Enter the name of the first vertex: ";
                std::cin >> vertex1;
                std::cout << "Enter the name of the second vertex: ";
                std::cin >> vertex2;
                graph.RemoveEdge(vertex1, vertex2);
                displayGraph(graph);
                break;
            }
            case 4: {
                int vertex;
                std::cout << "Enter the name of the vertex to remove: ";
                std::cin >> vertex;
                graph.RemoveVertex(vertex);
                displayGraph(graph);
                break;
            }
            case 5: {
                DynamicArray<int> topologicalOrder;
                graph.topologicalSort(topologicalOrder);
                std::cout << "Topological sort: ";
                for (const auto& vertex : topologicalOrder) {
                    std::cout << vertex << " ";
                }
                std::cout << std::endl;
                break;
            }
            case 6: {
                int startVertex, endVertex;
                std::cout << "Enter the number of the start vertex: ";
                std::cin >> startVertex;
                std::cout << "Enter the number of the end vertex: ";
                std::cin >> endVertex;
                Path<int> path = graph.Dijkstra(startVertex, endVertex);
                std::cout << "Shortest path: ";
                for (const auto& vertex : path.GetPath()) {
                    std::cout << vertex << " ";
                }
                std::cout << std::endl;
                break;
            }
            case 7: {
                int numVertices, numEdges;
                std::cout << "Enter the number of vertices: ";
                std::cin >> numVertices;
                std::cout << "Enter the number of edges: ";
                std::cin >> numEdges;
                graph.GenerateRandomGraph(numVertices, numEdges);
                displayGraph(graph);
                break;
            }
            case 8: // Exit
                std::cout << "Exiting." << std::endl;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
                break;
        }
    } while (choice != 8);
}

#endif //LABR4_MENUFUNC_H
