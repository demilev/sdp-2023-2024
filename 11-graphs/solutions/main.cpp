#include "graph.h"
#include <unordered_set>

// Функция, която намира входящата степ на връх - броят на ребрата към този връх
int numberOfParents(int vertex, Graph &graph)
{
    int result = 0;

    if (!graph.containsVertex(vertex))
        return result;

    std::list<int> verticies = graph.getVertices();

    // Обхождаме всички върхове
    for (int v : verticies)
    {
        // И броим тези от тях, които имат ребро към нашия връх
        if (graph.containsEdge(v, vertex))
            result++;
    }

    return result;
}

// Функция, която проверява дали дадена поредица от върхове е път в графа
bool isPath(const std::list<int> &path, Graph &graph)
{

    if (path.size() == 0)
        return true;
    if (path.size() == 1)
        return graph.containsVertex(path.front());

    // Обхождаме елементите на списъка два по два и проверяваме дали има ребро в графа между тях
    for (auto it = path.begin(); it != --path.end();)
    {
        if (!graph.containsEdge(*it, *(++it)))
            return false;
    }

    return true;
}

// Функция, която проверява дали има път между два върха в граф
bool pathExistsHelper(int from, int to, Graph &graph, std::unordered_set<int> &visited)
{
    // Ако върховете съвпадат, път има
    if (from == to)
        return true;

    visited.insert(from);

    std::list<int> neighbours = graph.getAdjacent(from);

    // Път между текущия и крайния има, ако има път между някои от съседите на текущия връх и крайния
    for (int n : neighbours)
    {
        // Добавяме и проверка за посетеност, за да не зациклим
        if (visited.count(n) == 0 && pathExistsHelper(n, to, graph, visited))
        {
            return true;
        }
    }

    return false;
}

bool pathExists(int from, int to, Graph &graph)
{
    std::unordered_set<int> visited;
    return pathExistsHelper(from, to, graph, visited);
}

// Функция, която пуска ДФС обхождане от даден връх
void dfsVisit(int vertex, Graph &graph, std::unordered_set<int> &visited, std::list<int> &dfsOrder)
{
    // Посещаваме текущия връх
    visited.insert(vertex);
    dfsOrder.push_back(vertex);

    std::list<int> neighbours = graph.getAdjacent(vertex);

    for (int n : neighbours)
    {
        // Обхождаме рекурсивно непосетените съседи на текущия връх
        if (visited.count(n) == 0)
        {
            dfsVisit(n, graph, visited, dfsOrder);
        }
    }
}

// Имплементация на ДФС алгоритъма
std::list<int> dfs(Graph &graph)
{
    std::unordered_set<int> visited;
    std::list<int> dfsOrder;

    for (int vertex : graph.getVertices())
    {
        // Докато има непосетени върхове в графа, ги посещаваме
        if (visited.count(vertex) == 0)
            dfsVisit(vertex, graph, visited, dfsOrder);
    }

    return dfsOrder;
}

int main()
{
    Graph g;

    g.addEdge(1, 2);
    g.addEdge(1, 3);

    g.addEdge(2, 1);
    g.addEdge(2, 5);

    g.addEdge(3, 5);
    g.addEdge(3, 8);

    g.addEdge(4, 2);
    g.addEdge(4, 6);

    g.addEdge(6, 8);

    std::list<int> neighbours3 = g.getAdjacent(3);

    std::cout << "The neighbours of vertex 3: ";
    for (int v : neighbours3)
    {
        std::cout << v << " ";
    }

    std::cout << std::endl;

    // g.printDot();

    std::cout << "{1, 2, 5} is a path in the graph: " << std::boolalpha << isPath({1, 2, 5}, g) << std::endl;
    std::cout << "{1, 4, 6, 8} is a path in the graph: " << std::boolalpha << isPath({1, 4, 6, 8}, g) << std::endl;

    std::cout << "Path exists between 1 and 8: " << std::boolalpha << pathExists(1, 8, g) << std::endl;
    std::cout << "Path exists between 2 and 6: " << std::boolalpha << pathExists(2, 6, g) << std::endl;

    std::list<int> dfsOrder = dfs(g);

    std::cout << "DFS order of the graph: ";
    for (int v : dfsOrder)
    {
        std::cout << v << " ";
    }

    std::cout << std::endl;

    return 0;
}