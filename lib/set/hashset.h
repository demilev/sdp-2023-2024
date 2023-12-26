#pragma once

#include "../hashtable/hashtable.h"

template <typename T>
class HashSet
{
private:
    HashTable<T, bool> ht;

public:
    HashSet();
    bool contains(const T &data);
    void add(const T &data);
    void remove(const T &data);
    int size();
    bool empty();
};

template <typename T>
HashSet<T>::HashSet() : ht(1000) {}

template <typename T>
bool HashSet<T>::contains(const T &data)
{
    return ht.containsKey(data);
}

template <typename T>
void HashSet<T>::add(const T &data)
{
    ht.put(data, true);
}

template <typename T>
void HashSet<T>::remove(const T &data)
{
    ht.remove(data);
}

template <typename T>
int HashSet<T>::size()
{
    return ht.size();
}

template <typename T>
bool HashSet<T>::empty()
{
    return ht.empty();
}
