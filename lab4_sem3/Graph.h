#ifndef GRAPH_H
#define GRAPH_H

#include "DynamicArray.h"
#include <list>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include "GraphParts.h"
#include <vector>
#include "Path.h"
#include <set>
#include <random>
template<typename T>
class Graph
{
private:
    DynamicArray<Vertex<T>> graph;
public:

    Graph() = default;

    void AddVertex(T vertexName) {
        if (SearchVertex(vertexName)) {
            std::cout << "Vertex " << vertexName << " already exists." << std::endl;
            return;
        }
        Vertex<T> vertex(vertexName);
        graph.push_back(vertex);
        //std::cout << "Vertex " << vertexName << " is added." << std::endl;
    }

    bool SearchVertex(T vertexName) {
        for (const auto &i : graph) {
            if (i.GetName() == vertexName) {
                return true;
            }
        }
        return false;
    }


    void AddEdge(T vertexName1, T vertexName2, int weight) {
        if (!SearchVertex(vertexName1) || !SearchVertex(vertexName2)) {
            std::cout << "One or both vertices do not exist." << std::endl;
            return;
        }

        if (SearchEdgeArc(vertexName1, vertexName2)) {
            return;
        }

        Edge newEdge(vertexName1, vertexName2, weight);
        for (auto &i: graph) {
            if (i.GetName() == vertexName1) {
                i.AddEdgeV(newEdge);
            }
        }

        Edge reverseEdge(vertexName2, vertexName1, weight);
        for (auto &i: graph) {
            if (i.GetName() == vertexName2) {
                i.AddEdgeV(reverseEdge);
            }
        }
    }
    const DynamicArray<Vertex<T>>& getGraph() const {
        return graph;
    }

    void AddArc(T vertexName1, T vertexName2, int weight) {
        if (!SearchVertex(vertexName1) || !SearchVertex(vertexName2)) {
            std::cout << "One or both vertices do not exist." << std::endl;
            return;
        }
        if (SearchEdgeArc(vertexName1, vertexName2)) {
            std::cout << "Arc from " << vertexName1 << " to " << vertexName2 << " already exists." << std::endl;
            return;
        }
        Edge newEdge(vertexName1, vertexName2, weight);
        for (auto &i: graph) {
            if (i.GetName() == vertexName1) {
                i.AddEdgeV(newEdge);
                //std::cout << "Added arc from " << vertexName1 << " to " << vertexName2 << " with weight " << weight << std::endl;
                return;
            }
        }
    }

    bool SearchEdgeArc(T vertexName1, T vertexName2)
    {
        for (auto &i: graph)
        {
            for (auto &it: i.GetEdges())
            {
                if (it.GetFirst() == vertexName1 && it.GetLast() == vertexName2)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void RemoveEdge(T vertexName1, T vertexName2) {
        for (auto &j: graph) {
            auto &edges = j.GetEdges();
            for (auto i = edges.begin(); i != edges.end();) {
                if (((*i).GetFirst() == vertexName1 && (*i).GetLast() == vertexName2) ||
                    ((*i).GetFirst() == vertexName2 && (*i).GetLast() == vertexName1)) {
                    i = edges.erase(i);
                } else {
                    ++i;
                }
            }
        }
    }

    void RemoveVertex(T vertexName) {
        for (auto& vertex : graph) {
            auto& edges = vertex.GetEdges();
            for (auto it = edges.begin(); it != edges.end();) {
                if ((*it).GetFirst() == vertexName || (*it).GetLast() == vertexName) {
                    it = edges.erase(it);
                } else {
                    ++it;
                }
            }
        }
        for (auto it = graph.begin(); it != graph.end();) {
            if ((*it).GetName() == vertexName) {
                it = graph.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }

    int GetSize() const
    {
        return static_cast<int>(graph.get_size());
    }



    Path<T> Dijkstra(T startVertexName, T endVertexName) {
        int numVertices = GetSize();
        if (numVertices == 0) {
            std::cout << "Graph is empty." << std::endl;
            return Path<T>();
        }
        if (!SearchVertex(startVertexName) || !SearchVertex(endVertexName)) {
            std::cout << "Start or end vertex not found." << std::endl;
            return Path<T>();
        }

        DynamicArray<int> dist(numVertices, INT_MAX);
        DynamicArray<int> prev(numVertices, -1);
        DynamicArray<bool> visited(numVertices, false);
        int startVertexIndex = -1;

        for (int i = 0; i < numVertices; ++i) {
            if (graph[i].GetName() == startVertexName) {
                startVertexIndex = i;
                break;
            }
        }

        dist[startVertexIndex] = 0;

        for (int i = 0; i < numVertices - 1; ++i) {
            int u = -1;
            for (int j = 0; j < numVertices; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }
            if (u == -1 || dist[u] == INT_MAX) {
                break;
            }
            visited[u] = true;

            for (const auto &edge : graph[u].GetEdges()) {
                int vertEnd = -1;
                for (int k = 0; k < numVertices; ++k) {
                    if (graph[k].GetName() == edge.GetLast()) {
                        vertEnd = k;
                        break;
                    }
                }
                int weight = edge.GetWeight();
                if (vertEnd != -1 && dist[vertEnd] > dist[u] + weight) {
                    dist[vertEnd] = dist[u] + weight;
                    prev[vertEnd] = u;
                }
            }
        }

        int endVertexIndex = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (graph[i].GetName() == endVertexName) {
                endVertexIndex = i;
                break;
            }
        }

        if (endVertexIndex == -1 || dist[endVertexIndex] == INT_MAX) {
            std::cout << "Path from " << startVertexName << " to " << endVertexName << " does not exist." << std::endl;
            return Path<T>();
        }


        std::cout << "Shortest distance from " << startVertexName << " to " << endVertexName << " is: " << dist[endVertexIndex] << std::endl;

        DynamicArray<T> path;
        for (int at = endVertexIndex; at != -1; at = prev[at]) {
            path.push_back(graph[at].GetName());
        }
        std::reverse(path.begin(), path.end());
        Path<T> item(dist, path);
        return item;
    }

    void topologicalSort(DynamicArray<T>& result) {
        if (hasCycle()) {
            std::cout << "Error: The graph contains a cycle. Topological sort is not possible." << std::endl;
            return;
        }

        int numVertices = GetSize();
        DynamicArray<bool> visited(numVertices, false);
        std::stack<T> stack;

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                topologicalSortUtil(graph[i].GetName(), visited, stack);
            }
        }

        while (!stack.empty()) {
            result.push_back(stack.top());
            stack.pop();
        }
    }


    bool hasCycle()
    {
        int numVertices = (int) graph.get_size();
        bool *visited = new bool[numVertices];
        bool *recStack = new bool[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false;
            recStack[i] = false;
        }

        for (int i = 0; i < numVertices; i++)
        {
            if (hasCycleUtil(i, visited, recStack))
            {
                delete[] visited;
                delete[] recStack;
                return true;
            }
        }

        delete[] visited;
        delete[] recStack;

        return false;
    }


    Vertex<T>& Get(T name_) {
        for (int i = 0; i < graph.get_size(); i++) {
            if (graph[i].GetName() == name_) {
                return graph[i];
            }
        }
        throw std::runtime_error("Vertex not found");
    }


    const Vertex<T>& Get(T name_) const
    {
        if (graph.get_size() == 0)
        {
            throw std::runtime_error("Graph is empty");
        }
        for (int i = 0; i < graph.get_size(); i++)
        {
            if (graph[i].GetName() == name_)
            {
                return graph[i];
            }
        }
        throw std::runtime_error("Vertex not found");
    }
    void GenerateRandomGraph(int numVertices, int numEdges) {
        if (numVertices <= 0 || numEdges < 0) {
            std::cout << "Invalid number of vertices or edges." << std::endl;
            return;
        }
        for (int i = 0; i < numVertices; ++i) {
            AddVertex(i + 1);
        }
        std::set<std::pair<int, int>> edgesSet;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> vertexDistribution(1, numVertices);

        while (edgesSet.size() < numEdges) {
            int vertex1 = vertexDistribution(generator);
            int vertex2 = vertexDistribution(generator);
            if (vertex1 != vertex2) {
                edgesSet.insert(std::make_pair(vertex1, vertex2));
            }
        }

        for (const auto& edge : edgesSet) {
            int vertex1 = edge.first;
            int vertex2 = edge.second;
            int weight = 1 + (std::rand() % 10); // Random weight from 1 to 10
            AddArc(vertex1, vertex2, weight);
        }

        std::cout << "Random graph generated with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
    }

private:

    void topologicalSortUtil(T vertexName, DynamicArray<bool>& visited, std::stack<T>& stack) {
        int vertexIndex = -1;
        for (int i = 0; i < graph.get_size(); i++) {
            if (graph[i].GetName() == vertexName) {
                vertexIndex = i;
                break;
            }
        }

        if (vertexIndex == -1) {
            return;
        }

        visited[vertexIndex] = true;

        for (const auto& edge : graph[vertexIndex].GetEdges()) {
            T neighbor = edge.GetLast();
            int neighborIndex = -1;

            for (int i = 0; i < graph.get_size(); i++) {
                if (graph[i].GetName() == neighbor) {
                    neighborIndex = i;
                    break;
                }
            }


            if (neighborIndex != -1 && !visited[neighborIndex]) {
                topologicalSortUtil(neighbor, visited, stack);
            }
        }

        stack.push(vertexName);
    }

    bool hasCycleUtil(int v, bool visited[], bool *recStack) {
        if (v < 0 || v >= graph.get_size()) {
            return false;
        }

        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            for (auto &edge: graph[v].GetEdges()) {

                T neighborName = edge.GetLast();
                int neighborIndex = -1;


                for (int i = 0; i < graph.get_size(); i++) {
                    if (graph[i].GetName() == neighborName) {
                        neighborIndex = i;
                        break;
                    }
                }

                if (neighborIndex != -1) {
                    if (!visited[neighborIndex] && hasCycleUtil(neighborIndex, visited, recStack)) {
                        return true;
                    } else if (recStack[neighborIndex]) {
                        return true;
                    }
                }
            }
        }
        recStack[v] = false;
        return false;
    }
};


#endif // GRAPH_H