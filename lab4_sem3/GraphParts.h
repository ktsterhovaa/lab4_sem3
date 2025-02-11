#ifndef GRAPHPARTS_H
#define GRAPHPARTS_H

#include <list>


template<typename T>
class Edge
{
private:
    T VertexName1;
    T VertexName2;
    int weight;
public:
    Edge(T vertex1, T vertex2, int weight) : VertexName1(vertex1), VertexName2(vertex2), weight(weight) {}

    Edge(Edge const &edge) : VertexName1(edge.VertexName1), VertexName2(edge.VertexName2), weight(edge.weight) {}

    int GetWeight() const
    {
        return weight;
    }

    T GetFirst() const
    {
        return VertexName1;
    }

    T GetLast() const
    {
        return VertexName2;
    }

    void Reverse()
    {
        T tmp = VertexName1;
        VertexName1 = VertexName2;
        VertexName2 = tmp;
    }
};

template<typename T>
class Vertex
{
private:
    T name;
    std::list<Edge<T>> edges;
public:
    Vertex() : name(), edges() {};

    Vertex(T name) : name(name) {};

    std::list<Edge<T>>& GetEdges() {
        return edges;
    }
    const std::list<Edge<T>>& GetEdges() const {
        return edges;
    }

    T GetName() const
    {
        return name;
    }

    void AddEdgeV(const Edge<T> &edge)
    {
        edges.push_back(edge);
    }

};


#endif // GRAPHPARTS_H
