
#pragma once

#include "set.h"
#include "bstree.h"

template <typename T>
class TreeSet : public Set<T>
{
private:
    BSTree<T> tree;

public:
    bool contains(const T &data);
    void add(const T &data);
    void remove(const T &data);
    int size();
    bool empty();
};

template <typename T>
bool TreeSet<T>::contains(const T &data)
{
    return tree.member(data);
}

template <typename T>
void TreeSet<T>::add(const T &data)
{
    tree.add(data);
}

template <typename T>
void TreeSet<T>::remove(const T &data)
{
    tree.remove(data);
}

template <typename T>
int TreeSet<T>::size()
{
    return tree.size();
}

template <typename T>
bool TreeSet<T>::empty()
{
    return tree.size() == 0;
}

int countUniques(const std::vector<int> &data)
{
    // Пазим си множество с посетени елементи
    TreeSet<int> visited;

    int uniques = 0;
    // Сложност по време - О(n)
    for (const int element : data)
    {
        // Ако текущият елемент не е бил срещан досега
        // Сложност по време - О(lgn)
        if (!visited.contains(element))
        {
            // Увеличаваме брояча за брой уникални елементи
            uniques++;
            // Добавяме го в множеството с посетени елементи, за да не го броим като уникален повече
            // Сложност по време - О(lgn)
            visited.add(element);
        }
    }

    // Обща сложност по време - О(n*lgn)
    // Обща сложност по памет - О(n)

    return uniques;
}

bool twoSum(const std::vector<int> &data, int target)
{
    // Пазим си множество с вече посетени елементи
    TreeSet<int> visited;

    // Сложност по време - О(n)
    for (const int element : data)
    {
        // Ако вече сме посетили елемент, който е равен на target - <текущия елемент>, значи има два елемента във вектор със сума target
        // Сложност по време - О(lgn)
        if (visited.contains(target - element))
        {
            return true;
        }

        // Добавяме текущия елемент в множеството с посетени елементи
        visited.add(element);
    }

    // Обща сложност по време - О(n*lgn)
    // Обща сложност по памет - О(n)

    return false;
}