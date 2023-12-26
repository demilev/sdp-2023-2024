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
    double efficiency();

private:
    // Пазим вектор от наредени двойки. На индекс i, стои свързан списък от всички наредени двойки, чиито ключ има хеш стойност равна на i
    std::vector<std::list<std::pair<Key, Value>>> table;
    // Максималният размер на вектора
    std::size_t maxSize;
    // Хеширащата функция
    std::hash<Key> hashFunction;

    // Помощни методи:
    int getIndex(const Key &);                                 // Намира индекса във вектора, на който трябва да отиде съответния ключ
    std::list<std::pair<Key, Value>> &findBucket(const Key &); // Връща референция към кутията/бъкета, към който принадлежи съответния ключ
    std::pair<Key, Value> *locate(const Key &);                // Връща указател към наредената двойка(ако такава съществува) съответстваща на този ключ
};

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(std::size_t maxSize) : table(maxSize), maxSize(maxSize) {}

template <typename Key, typename Value>
int HashTable<Key, Value>::getIndex(const Key &key)
{
    // Смятаме хеш стойността
    std::size_t hashValue = hashFunction(key);

    // Намираме индекса, на който съответства тази хеш стойност
    return hashValue % maxSize; // [0, maxSize - 1]
}

template <typename Key, typename Value>
std::list<std::pair<Key, Value>> &HashTable<Key, Value>::findBucket(const Key &key)
{
    // Вземаме кутийката съотвестваща на индекса на ключа
    return table[getIndex(key)];
}

// Моделираме функцията да връща указател към наредената двойка, съответсваща на съответния ключ,
// за да използваме nullptr в случай, че този ключ не е намерен
template <typename Key, typename Value>
std::pair<Key, Value> *HashTable<Key, Value>::locate(const Key &key)
{
    // // Вземаме кутийката съотвестваща на ключа
    std::list<std::pair<Key, Value>> &bucket = findBucket(key);

    // Търсим наредената двойка за този ключ
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
    // Ако наредената двойка е намерена, връщаме втория й елемент
    if (pair != nullptr)
    {
        return pair->second;
    }

    // В противен случай хвърляме грешка
    throw std::out_of_range("no element found for that key");
}

template <typename Key, typename Value>
void HashTable<Key, Value>::put(const Key &key, const Value &value)
{
    std::pair<Key, Value> *pair = locate(key);

    // Ако съществува наредена двойка с този ключ, update-ваме стойността й
    if (pair != nullptr)
    {
        pair->second = value;
        return;
    }

    // В противен случай добавяме нова наредена двойка
    findBucket(key).push_back(std::pair<Key, Value>(key, value));
}

template <typename Key, typename Value>
void HashTable<Key, Value>::remove(const Key &key)
{
    std::list<std::pair<Key, Value>> &bucket = findBucket(key);
    // Трием от свързания списък през итератор
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
    // обхождаме всички кутийки
    for (const std::list<std::pair<Key, Value>> &bucket : table)
    {
        // и броим колко реални елементи съдържат
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

template <typename Key, typename Value>
double HashTable<Key, Value>::efficiency()
{
    int all = 0;
    int coliding = 0;

    for (const std::list<std::pair<Key, Value>> &bucket : table)
    {
        if (bucket.size() > 1)
            coliding += bucket.size();

        all += bucket.size();
    }

    return coliding / all;
}