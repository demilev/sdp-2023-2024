#include "graph.h"

bool Graph::containsVertex(int vertex)
{
    return adjList.count(vertex) > 0;
}

bool Graph::containsEdge(int from, int to)
{
    if (!containsVertex(from) || !containsVertex(to))
        return false;

    for (int v : adjList[from])
    {
        if (v == to)
            return true;
    }

    return false;
}

void Graph::addVertex(int vertex)
{
    if (!containsVertex(vertex))
        adjList[vertex] = std::list<int>();
}

void Graph::addEdge(int from, int to)
{
    addVertex(from);
    addVertex(to);

    if (!containsEdge(from, to))
        adjList[from].push_back(to);
}

std::list<int> Graph::getAdjacent(int vertex)
{
    if (!containsVertex(vertex))
        return std::list<int>();

    return adjList[vertex];
}

void Graph::printDot()
{
    std::cout << "digraph G {" << std::endl;
    for (std::pair<int, std::list<int>> p : adjList)
    {
        for (int v : p.second)
        {
            std::cout << p.first << "->" << v << std::endl;
        }
    }

    std::cout << "}" << std::endl;
}

std::list<int> Graph::getVertices()
{
    std::list<int> result;

    for (std::pair<int, std::list<int>> p : adjList)
    {
        result.push_back(p.first);
    }

    return result;
}