#include <string>
#include <vector>
#include <stack>
#include <list>
#include <iostream>

/*
    Тази задача на практика имплементира DFS алгоритъма за намиране на топологическо сортиране.
    DFS - https://en.wikipedia.org/wiki/Depth-first_search
    Topological Sort
        - https://cp-algorithms.com/graph/topological-sort.html
        - https://en.wikipedia.org/wiki/Topological_sorting
*/

// Ще моделираме задачата със стек. За целта ще имаме две операции на стека
// 1) Рекурсивната - която симулира рекурсивното извикване и обходане
// 2) Действие след рекурсията - която симулира изпълнението на кода след рекурсивното извикване.
struct Operation
{
    int task;
    char type; // 'r' - рекурсивно извикване, 'p' - слага задачата в резултата
};

// Функция, която дава план за изпъление на дадената задача и всички, които трябва да бъдат изпълнение след нея
void visit(int task, std::vector<std::vector<int>> &dependencies, std::vector<bool> &visited, std::list<int> &order)
{

    std::stack<Operation> toVisit;
    // Започваме с операция за обхождане на текущата задача
    toVisit.push({task, 'r'});

    // Докато има задачи за обхождане
    while (!toVisit.empty())
    {
        // Вземаме текущата
        Operation current = toVisit.top();
        toVisit.pop();
        int currentTask = current.task;
        // Ако имаме рекурсиван операция за обхождане
        if (current.type == 'r')
        {
            // Тове е характерна за DFS логика, която видяхме и в задача 3
            if (!visited[currentTask])
            {
                visited[currentTask] = true;
                // Слагаме операция за обработка на текущата задача. Чак след това слагаме операция
                // за обхождане на задачите наследници. Така гарантираме, че текущата задача ще бъде
                // сложена в наредбата чак след като обходим наследниците й. С тази техника симулираме действие,
                // което се извиква след рекурсивното извикване.
                toVisit.push({currentTask, 'p'});
                std::vector<int> firends = dependencies[currentTask];
                for (int fr : firends)
                {
                    toVisit.push({fr, 'r'});
                }
            }
        }
        // Ако имаме операция за слагане в резултата, това означава, че вече сме обходили всички наследници на текущата задача
        // и можем да я сложим в резултата най-отпред.
        else if (current.type == 'p')
        {
            order.push_front(current.task);
        }
    }
}

// Главната функция
std::list<int> toposort(std::vector<int> &tasks, std::vector<std::vector<int>> &dependencies)
{
    std::vector<bool> visited(tasks.size());
    std::list<int> order;
    std::fill(visited.begin(), visited.end(), 0);

    // Обхожда непосетените задачи и намира план за изпълнение чрез помощната функция
    for (int task : tasks)
    {
        if (!visited[task])
        {
            visit(task, dependencies, visited, order);
        }
    }

    return order;
}
