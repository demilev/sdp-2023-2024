#include "graph.h"
#include <unordered_set>

void printList(const std::list<int> &l)
{
    for (int el : l)
    {
        std::cout << el << " ";
    }

    std::cout << std::endl;
}

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

// Функция, която пуска БФС обхождане от даден връх
void bfsVisit(int vertex, Graph &graph, std::unordered_set<int> &visited, std::list<int> &bfsOrder)
{
    // Списък, в който ще трупаме елементите за обхождане.
    // Най-отпред ще стои текущия връх за обхождане, а новите ще добавяме най-отзад.
    // Т.е. ще ползваме списъка като опашка
    std::list<int> toVisit;
    toVisit.push_back(vertex);
    visited.insert(vertex);

    // Докато има върхове за обхождаме
    while (!toVisit.empty())
    {
        // Вземаме текущия
        int current = toVisit.front();
        toVisit.pop_front();

        // Обхождаме съседите му
        std::list<int> neighbours = graph.getAdjacent(current);
        for (int n : neighbours)
        {
            // Тези които са непосетени,
            if (visited.count(n) == 0)
            {
                // ги посещаваме
                visited.insert(n);
                toVisit.push_back(n);
            }
        }

        // Слагаме текущия в резултата
        bfsOrder.push_back(current);
    }
}

// Имплементация на БФС алгоритъма
std::list<int> bfs(Graph &graph)
{
    std::unordered_set<int> visited;
    std::list<int> bfsOrder;

    for (int vertex : graph.getVertices())
    {
        // Докато има непосетени върхове в графа, ги посещаваме
        if (visited.count(vertex) == 0)
            bfsVisit(vertex, graph, visited, bfsOrder);
    }

    return bfsOrder;
}

bool listContains(const std::list<int> &l, int n)
{
    for (int element : l)
    {
        if (element == n)
            return true;
    }

    return false;
}

// Намиране на всички пътища м/у два върха в граф, използвайки BFS обхождане
std::list<std::list<int>> allPaths(int from, int to, Graph &graph)
{
    // Вместо опашка от върхове, ще пазим опашка от пътища, които ще градим
    std::list<std::list<int>> pathsToVisit;
    // Променлива, в която ще пазим всички намерене пътища
    std::list<std::list<int>> allPaths;

    // Започваме с един път, който се състои само от началния елемент
    pathsToVisit.push_back({from});

    while (!pathsToVisit.empty())
    {
        // На всяка стъпка вземаме текущия път
        std::list<int> currentPath = pathsToVisit.front();
        pathsToVisit.pop_front();

        // И неговия последен връх
        int lastVertex = currentPath.back();

        // Ако сме стигнали целта, добавяме текущия път в резултата
        if (lastVertex == to)
        {
            allPaths.push_back(currentPath);
        }
        else
        {
            // В противен случай създаваме нови пътища от текущия път, като добавяме наследниците на последния връх
            for (int neighbor : graph.getAdjacent(lastVertex))
            {
                // Проверяваме дали вече сме минали през новия връх в текущия път
                if (!listContains(currentPath, neighbor))
                {
                    std::list<int> newPath = currentPath;
                    newPath.push_back(neighbor);

                    pathsToVisit.push_back(newPath);
                }
            }
        }
    }

    return allPaths;
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

    g.printDot();

    std::cout << "{1, 2, 5} is a path in the graph: " << std::boolalpha << isPath({1, 2, 5}, g) << std::endl;
    std::cout << "{1, 4, 6, 8} is a path in the graph: " << std::boolalpha << isPath({1, 4, 6, 8}, g) << std::endl;

    std::cout << "Path exists between 1 and 8: " << std::boolalpha << pathExists(1, 8, g) << std::endl;
    std::cout << "Path exists between 2 and 6: " << std::boolalpha << pathExists(2, 6, g) << std::endl;

    std::list<int> dfsOrder = dfs(g);

    std::cout << "DFS order of the graph: ";
    printList(dfsOrder);

    std::list<int> bfsOrder;
    std::unordered_set<int> visited;
    bfsVisit(1, g, visited, bfsOrder);

    std::cout << "BFS order of the graph: ";
    printList(bfsOrder);

    std::list<std::list<int>> allPathsFrom4to5 = allPaths(4, 5, g);

    std::cout << "All paths from 4 to 5: " << std::endl;
    for (std::list<int> &path : allPathsFrom4to5)
    {
        printList(path);
    }

    return 0;
}