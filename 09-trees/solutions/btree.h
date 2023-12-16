#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <functional>
#include <list>
#include "bstree.h"

template <typename T>
struct Node
{
    T data;
    Node<T> *left;
    Node<T> *right;

    Node(const T &);
    Node(const T &, Node<T> *, Node<T> *);
};

// Помощен клас, който ще ни позволява да обхождаме дървото и извън рамките на самия клас
template <typename T>
class BTreeVisitor
{
public:
    BTreeVisitor(Node<T> *);
    T get();
    BTreeVisitor goLeft();
    BTreeVisitor goRight();
    bool empty();

private:
    Node<T> *current;
};

template <typename T>
class BTree
{
private:
    Node<T> *root;

    void printDot(Node<T> *);

    Node<T> *copy(Node<T> *);
    void cleanup(Node<T> *);

    int balancedHeight(Node<T> *);
    void allPaths(Node<T> *, std::list<T>, std::list<std::list<T>> &);
    void forest(Node<T> *&, BSTree<T> &, std::list<BTree<T>> &);

public:
    BTree();
    BTree(Node<T> *);
    BTree(const BTree<T> &);
    ~BTree();
    BTree<T> &operator=(const BTree<T> &);

    void printDot();
    bool isBalanced();
    std::list<std::list<T>> allPaths();
    std::list<std::list<T>> allLevels();
    BTreeVisitor<T> visitor();
    std::list<BTree<T>> forest(BSTree<T> &);
};

template <typename T>
Node<T>::Node(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node<T> *left, Node<T> *right) : data(data), left(left), right(right) {}

template <typename T>
BTreeVisitor<T>::BTreeVisitor(Node<T> *current) : current(current) {}

template <typename T>
T BTreeVisitor<T>::get()
{
    return current->data;
}

template <typename T>
BTreeVisitor<T> BTreeVisitor<T>::goLeft()
{
    return BTreeVisitor<T>(current->left);
}

template <typename T>
BTreeVisitor<T> BTreeVisitor<T>::goRight()
{
    return BTreeVisitor<T>(current->right);
}

template <typename T>
bool BTreeVisitor<T>::empty()
{
    return current == nullptr;
}

template <typename T>
BTree<T>::BTree() : root(nullptr) {}

template <typename T>
BTree<T>::BTree(Node<T> *root) : root(root) {}

template <typename T>
BTree<T>::~BTree()
{
    cleanup(root);
}

template <typename T>
BTree<T>::BTree(const BTree<T> &other) : root(nullptr)
{
    root = copy(other.root);
}

template <typename T>
BTree<T> &BTree<T>::operator=(const BTree<T> &other)
{
    if (this != &other)
    {
        cleanup(root);
        root = copy(other.root);
    }

    return *this;
}

template <typename T>
void BTree<T>::cleanup(Node<T> *current)
{
    if (current == nullptr)
        return;

    cleanup(current->left);
    cleanup(current->right);

    delete current;
}

template <typename T>
Node<T> *BTree<T>::copy(Node<T> *current)
{
    if (current == nullptr)
        return nullptr;

    return new Node<T>(current->data, copy(current->left), copy(current->right));
}

template <typename T>
void BTree<T>::printDot(Node<T> *current)
{

    if (current == nullptr)
    {
        return;
    }

    std::cout << (long)current << "[label=\"" << current->data << "\"]" << std::endl;

    if (current->left != nullptr)
    {
        std::cout << (long)current << " -> " << (long)current->left << std::endl;
    }

    if (current->right != nullptr)
    {
        std::cout << (long)current << " -> " << (long)current->right << std::endl;
    }

    printDot(current->left);
    printDot(current->right);
}

template <typename T>
void BTree<T>::printDot()
{
    std::cout << "digraph G {" << std::endl;
    printDot(root);
    std::cout << "}" << std::endl;
}

// Функция, която намира височината на дървото, но която връща -1, ако дървото не е балансирано
template <typename T>
int BTree<T>::balancedHeight(Node<T> *current)
{

    if (current == nullptr)
    {
        return 0;
    }

    // лявото балансирано ли е?
    int heightL = balancedHeight(current->left);
    if (heightL == -1)
        return -1;

    // дясното балансирано ли е?
    int heightR = balancedHeight(current->right);
    if (heightR == -1)
        return -1;

    // текущото дърво балансирано ли е?
    if (abs(heightL - heightR) > 1)
        return -1;

    // само ако предните три условия са изпълнени връщаме височината на текущото дърво
    return 1 + std::max(heightL, heightR);
}

template <typename T>
bool BTree<T>::isBalanced()
{
    return balancedHeight(root) != -1;
}

// Функция, която връща всички пътища в дървото.
// Подаваме два допълнителни аргумента - текущо изградения път и всички пътища до момента
template <typename T>
void BTree<T>::allPaths(Node<T> *current, std::list<T> currentPath, std::list<std::list<T>> &result)
{
    // Добавяме корена към текущо изградения път
    currentPath.push_back(current->data);

    if (current->left == nullptr && current->right == nullptr)
    {
        // Ако сме стигнали листо, добавяме текущия път в резултата
        result.push_back(currentPath);
        return;
    }

    // Ако можем да тръгнем наляво, добавяме всички пътища, които могат да се получат в лявото поддърво
    if (current->left)
        allPaths(current->left, currentPath, result);
    // Ако можем да тръгнем надясно, добавяме всички пътища, които могат да се получат в дясно поддърво
    if (current->right)
        allPaths(current->right, currentPath, result);
}

template <typename T>
void BTree<T>::forest(Node<T> *&current, BSTree<T> &bstree, std::list<BTree<T>> &result)
{
    if (current == nullptr)
        return;

    forest(current->left, bstree, result);
    forest(current->right, bstree, result);

    // Ако трябва да махнем текущия елемент
    if (bstree.member(current->data))
    {
        // Добавяме лявото поддърво към резултата
        if (current->left)
            result.push_back(BTree<T>(copy(current->left)));
        // Добавяме дясното поддърво към резултата
        if (current->right)
            result.push_back(BTree<T>(copy(current->right)));

        // Трием корена
        delete current;
        current = nullptr;
    }
}

template <typename T>
std::list<std::list<T>> BTree<T>::allPaths()
{
    std::list<T> currentPath;
    std::list<std::list<T>> result;
    allPaths(root, currentPath, result);

    return result;
}

template <typename T>
std::list<std::list<T>> BTree<T>::allLevels()
{
    // Списък, в който ще трупаме резултата
    std::list<std::list<T>> result;
    // Списък, в който ще трупаме текущо необходените елементи, заедно с височината в дървото, на която се намират
    std::list<std::pair<int, Node<T> *>> nodes;
    // Започваме от корена, който е на първо ниво
    nodes.push_back({1, root});

    // Докато не обходим всички възли в дървото
    while (!nodes.empty())
    {
        // Вземаме първия
        std::pair<int, Node<T> *> current = nodes.front();
        nodes.pop_front();
        // Ако не съществува списък за нивото на текущия елемента, добавяме такъв
        if (current.first > result.size())
        {
            result.push_back(std::list<T>({current.second->data}));
        }
        else
        {
            // В противен случай го добавяме към елементите за това ниво
            result.back().push_back(current.second->data);
        }

        // Ако има ляв наследник, го добавяме в края на необходените елементи
        if (current.second->left != nullptr)
        {
            nodes.push_back({current.first + 1, current.second->left});
        }

        // Ако има десен наследник, го добавяме в края на необходените елементи
        if (current.second->right != nullptr)
        {
            nodes.push_back({current.first + 1, current.second->right});
        }
    }

    return result;
}

template <typename T>
BTreeVisitor<T> BTree<T>::visitor()
{
    return BTreeVisitor<T>(root);
}

template <typename T>
std::list<BTree<T>> BTree<T>::forest(BSTree<T> &bstree)
{
    std::list<BTree<T>> result;
    // Работим с копие на дървото
    Node<T> *rootCopy = copy(root);
    forest(rootCopy, bstree, result);
    // Накрая добавяме финалното дърво в случай, че коренът му не е бил изтрит
    if (rootCopy != nullptr)
        result.push_back(rootCopy);
    return result;
}