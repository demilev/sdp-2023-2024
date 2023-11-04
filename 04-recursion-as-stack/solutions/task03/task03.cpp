#include <string>
#include <vector>
#include <stack>
#include <iostream>

/*
    Тази задача на практика имплементира DFS алгоритъма за намиране на свързани компоненти в граф.
    https://en.wikipedia.org/wiki/Depth-first_search
*/

// Рекурсивна функция за обхождане на групата от приятели на човек person
void visit(int person, std::vector<std::vector<int>> &friendships, std::vector<bool> &visited)
{
    // Дъно на рекурсията - вече посетен човек
    if (visited[person])
    {
        return;
    }

    // Отбелязваме текущия човек като посетен
    visited[person] = true;
    // Отепчатваме го на екрана. В случая това е действието ни при посещаване, но може и да нещо друго спрямо задачата.
    std::cout << person << std::endl;
    std::vector<int> firends = friendships[person];
    // Обхобдаме всичките му приятели
    for (int fr : firends)
    {
        // И ги посещаваме
        visit(fr, friendships, visited);
    }
}

// Итеративно решение на горната функция, използвайки стек
void visitStack(int person, std::vector<std::vector<int>> &friendships, std::vector<bool> &visited)
{
    // Пазим стек с хората, които трябва да бъдат посетени
    std::stack<int> toVisit;
    // Започваме от първия
    toVisit.push(person);

    // Докато не посетим всички
    while (!toVisit.empty())
    {
        // Вземаме текущия
        int current = toVisit.top();
        toVisit.pop();
        // Ако не е посетен(тази проверка симулира дъното на рекурсията)
        if (!visited[current])
        {
            // Посещаваме човека
            visited[current] = true;
            std::cout << current << std::endl;
            std::vector<int> firends = friendships[current];
            // И слагаме на стека всичките му приятели(това симулира рекурсивното извикване)
            for (int fr : firends)
            {
                toVisit.push(fr);
            }
        }
    }
}

// Тази функция обхожда всички хора и отпечатва техните групи
void friendGroups(std::vector<int> &people, std::vector<std::vector<int>> &friendships)
{
    std::vector<bool> visited(people.size());
    std::fill(visited.begin(), visited.end(), 0);
    int i = 1;
    for (int person : people)
    {
        // Ако има непосетен човек, значи има нова група от приятели
        if (!visited[person])
        {
            std::cout << "Group " << i++ << std::endl;
            // Обхождаме я с помощната функция
            visitStack(person, friendships, visited); // visit(person, friendships, visited)
        }
    }
}

int main()
{
    std::vector<int> people = {0, 1, 2, 3, 4};
    std::vector<std::vector<int>> friendships = {{3, 4}, {2}, {1}, {0, 4}, {0, 3}};

    friendGroups(people, friendships);

    return 0;
}