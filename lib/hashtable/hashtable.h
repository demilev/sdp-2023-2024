#pragma once

#include <vector>
#include <list>
#include <functional>
#include <stdexcept>

template <typename Key, typename Value>
class HashTable
{
public:
    HashTable(std::size_t);
    bool containsKey(const Key &);
    Value get(const Key &);
    void put(const Key &, const Value &);
    void remove(const Key &);
    bool empty();
    int size();
    std::vector<Key> keys();
    std::vector<Value> values();

private:
    std::vector<std::list<std::pair<Key, Value>>> table;
    std::size_t maxSize;
    std::hash<Key> hashFunction;

    int getIndex(const Key &);
    std::list<std::pair<Key, Value>> &findBucket(const Key &);
    std::pair<Key, Value> *locate(const Key &);
};

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(std::size_t maxSize) : table(maxSize), maxSize(maxSize) {}

template <typename Key, typename Value>
int HashTable<Key, Value>::getIndex(const Key &key)
{
    std::size_t hashValue = hashFunction(key);

    return hashValue % maxSize;
}

template <typename Key, typename Value>
std::list<std::pair<Key, Value>> &HashTable<Key, Value>::findBucket(const Key &key)
{
    return table[getIndex(key)];
}

template <typename Key, typename Value>
std::pair<Key, Value> *HashTable<Key, Value>::locate(const Key &key)
{
    std::list<std::pair<Key, Value>> &bucket = findBucket(key);

    for (std::pair<Key, Value> &pair : bucket)
    {
        if (pair.first == key)
            return &pair;
    }

    return nullptr;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::containsKey(const Key &key)
{
    return locate(key) != nullptr;
}

template <typename Key, typename Value>
Value HashTable<Key, Value>::get(const Key &key)
{
    std::pair<Key, Value> *pair = locate(key);
    if (pair != nullptr)
    {
        return pair->second;
    }

    throw std::out_of_range("no element found for that key");
}

template <typename Key, typename Value>
void HashTable<Key, Value>::put(const Key &key, const Value &value)
{
    std::pair<Key, Value> *pair = locate(key);

    if (pair != nullptr)
    {
        pair->second = value;
        return;
    }

    findBucket(key).push_back(std::pair<Key, Value>(key, value));
}

template <typename Key, typename Value>
void HashTable<Key, Value>::remove(const Key &key)
{
    std::list<std::pair<Key, Value>> &bucket = findBucket(key);
    for (auto it = bucket.begin(); it != bucket.end(); ++it)
    {
        if ((*it).first == key)
        {
            bucket.erase(it);
            return;
        }
    }
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::empty()
{
    return size() == 0;
}

template <typename Key, typename Value>
int HashTable<Key, Value>::size()
{
    int result = 0;
    for (const std::list<std::pair<Key, Value>> &bucket : table)
    {
        result += bucket.size();
    }

    return result;
}

template <typename Key, typename Value>
std::vector<Key> HashTable<Key, Value>::keys()
{
    std::vector<Key> result;

    for (const std::list<std::pair<Key, Value>> &bucket : table)
    {
        for (const std::pair<Key, Value> &pair : bucket)
            result.push_back(pair.first);
    }

    return result;
}

template <typename Key, typename Value>
std::vector<Value> HashTable<Key, Value>::values()
{
    std::vector<Value> result;

    for (const std::list<std::pair<Key, Value>> &bucket : table)
    {
        for (const std::pair<Key, Value> &pair : bucket)
            result.push_back(pair.second);
    }

    return result;
}
