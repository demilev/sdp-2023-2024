
#pragma once

#include "set.h"
#include "bstree/bstree.h"

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
