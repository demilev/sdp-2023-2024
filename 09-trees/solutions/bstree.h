#pragma once

#include <iostream>
#include <vector>

template <typename T>
struct BSNode
{
    T data;
    BSNode<T> *left;
    BSNode<T> *right;

    BSNode(const T &);
    BSNode(const T &, BSNode<T> *, BSNode<T> *);
};

template <typename T>
class BSTree
{
private:
    BSNode<T> *root;

    BSNode<T> *copy(BSNode<T> *);
    void cleanup(BSNode<T> *);

    bool member(BSNode<T> *, const T &);
    void add(BSNode<T> *&, const T &);

    void printDot(BSNode<T> *);

    int balancedHeight(BSNode<T> *);
    static void balancedAdd(BSTree<T> &, const std::vector<T> &, int, int);

public:
    BSTree();
    BSTree(BSNode<T> *);
    BSTree(const BSTree<T> &);
    ~BSTree();
    BSTree<T> &operator=(const BSTree<T> &);

    T min();
    T max();

    bool member(const T &);
    void add(const T &);
    void remove(const T &);

    void printDot();

    bool isBalanced();
    static BSTree<T> balanced(const std::vector<T> &);
};

template <typename T>
BSNode<T>::BSNode(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
BSNode<T>::BSNode(const T &data, BSNode<T> *left, BSNode<T> *right) : data(data), left(left), right(right) {}

template <typename T>
BSTree<T>::BSTree() : root(nullptr) {}

template <typename T>
BSTree<T>::BSTree(BSNode<T> *root) : root(root) {}

template <typename T>
BSTree<T>::~BSTree()
{
    cleanup(root);
}

template <typename T>
BSTree<T>::BSTree(const BSTree<T> &other) : root(nullptr)
{
    root = copy(other.root);
}

template <typename T>
BSTree<T> &BSTree<T>::operator=(const BSTree<T> &other)
{
    if (this != &other)
    {
        cleanup(root);
        root = copy(other.root);
    }

    return *this;
}

template <typename T>
void BSTree<T>::cleanup(BSNode<T> *current)
{
    if (current == nullptr)
        return;

    cleanup(current->left);
    cleanup(current->right);

    delete current;
}

template <typename T>
BSNode<T> *BSTree<T>::copy(BSNode<T> *current)
{
    if (current == nullptr)
        return nullptr;

    return new BSNode<T>(current->data, copy(current->left), copy(current->right));
}

// За да е балансирано дървото грубо казано трябва в лявото поддърво да има толкова елементи, колкото и в дясното
// Т.е. коренът на дърво трябва да е средния елемент на вектора
template <typename T>
void BSTree<T>::balancedAdd(BSTree<T> &tree, const std::vector<T> &elements, int left, int right)
{
    if (left > right)
        return;

    int middle = (left + right) / 2;
    // Добаявме средния елемент на вектора
    tree.add(elements[middle]);
    // Добавяме всички по-малки от него. Те ще са му наследници в лявото поддърво
    balancedAdd(tree, elements, left, middle - 1);
    // Добавяме всички по-големи от него. Те ще са му наследници в дясното поддърво
    balancedAdd(tree, elements, middle + 1, right);

    // Накрая сме си гарантирали, че средният елемент е корен на дърво, в което лявото и дясното поддървета има еднакъв брой елементи
}

template <typename T>
BSTree<T> BSTree<T>::balanced(const std::vector<T> &elements)
{
    BSTree<T> result;
    balancedAdd(result, elements, 0, elements.size());
    return result;
}

template <typename T>
bool BSTree<T>::member(BSNode<T> *current, const T &data)
{
    if (current == nullptr)
        return false;

    if (current->data == data)
        return true;

    if (current->data > data)
        return member(current->left, data);

    if (current->data < data)
        return member(current->right, data);

    return false;
}

template <typename T>
void BSTree<T>::add(BSNode<T> *&current, const T &data)
{
    if (current == nullptr)
    {
        current = new BSNode<T>(data);
    }

    if (current->data > data)
    {
        add(current->left, data);
        return;
    }

    if (current->data < data)
    {
        add(current->right, data);
        return;
    }

    return;
}

template <typename T>
void BSTree<T>::printDot(BSNode<T> *current)
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
int BSTree<T>::balancedHeight(BSNode<T> *current)
{

    if (current == nullptr)
    {
        return 0;
    }

    int heightL = balancedHeight(current->left);
    if (heightL == -1)
        return -1;

    int heightR = balancedHeight(current->right);
    if (heightR == -1)
        return -1;

    if (abs(heightL - heightR) > 1)
        return -1;

    return 1 + std::max(heightL, heightR);
}

template <typename T>
bool BSTree<T>::isBalanced()
{
    return balancedHeight(root) != -1;
}

template <typename T>
bool BSTree<T>::member(const T &data)
{
    return member(root, data);
}

template <typename T>
void BSTree<T>::add(const T &data)
{
    add(root, data);
}

template <typename T>
void BSTree<T>::remove(const T &data)
{
    remove(root, data);
}

template <typename T>
void BSTree<T>::printDot()
{
    std::cout << "digraph G {" << std::endl;
    printDot(root);
    std::cout << "}" << std::endl;
}