#pragma once

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node<T> *left;
    Node<T> *right;

    Node(const T &);
    Node(const T &, Node<T> *, Node<T> *);
};

template <typename T>
class BSTree
{
private:
    Node<T> *root;

    void printDot(Node<T> *);

    Node<T> *copy(Node<T> *);
    void cleanup(Node<T> *);

public:
    BSTree();
    BSTree(Node<T> *);
    BSTree(const BSTree<T> &);
    ~BSTree();
    BSTree<T> &operator=(const BSTree<T> &);

    void printDot();
};

template <typename T>
Node<T>::Node(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node<T> *left, Node<T> *right) : data(data), left(left), right(right) {}

template <typename T>
BSTree<T>::BSTree() : root(nullptr) {}

template <typename T>
BSTree<T>::BSTree(Node<T> *root) : root(root) {}

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
void BSTree<T>::cleanup(Node<T> *current)
{
    if (current == nullptr)
        return;

    cleanup(current->left);
    cleanup(current->right);

    delete current;
}

template <typename T>
Node<T> *BSTree<T>::copy(Node<T> *current)
{
    if (current == nullptr)
        return nullptr;

    return new Node<T>(current->data, copy(current->left), copy(current->right));
}

template <typename T>
void BSTree<T>::printDot(Node<T> *current)
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
void BSTree<T>::printDot()
{
    std::cout << "digraph G {" << std::endl;
    printDot(root);
    std::cout << "}" << std::endl;
}
