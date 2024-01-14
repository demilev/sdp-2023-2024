#include <unordered_map>
#include <list>
#include <iostream>

class Graph
{
private:
    // Представяме графа със списъци на съседство моделирани чрез хеш таблица.
    // Ключовете на таблицата са върховете, а стойностите са списък от върхове, към които текущия има ребро:
    //
    // 1 -> [2, 3] - връх едно е свързан с върхове 2 и 3
    // 2 -> [4]
    // 3 -> [5, 1]
    // 4 -> [5]
    // 5 -> [2, 3, 4]
    std::unordered_map<int, std::list<int>> adjList;

public:
    void addVertex(int);
    void addEdge(int, int);
    std::list<int> getAdjacent(int);
    void printDot();
    std::list<int> getVertices();
    bool containsVertex(int);
    bool containsEdge(int from, int to);
};