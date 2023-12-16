#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <functional>

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
struct Operation
{
    Node<T> *node;
    char type; // 'r' - recursive, 'p' - process
};

template <typename T>
class BTreeIterator
{
public:
    BTreeIterator(Node<T> *);
    BTreeIterator<T> &operator++();
    T &operator*();
    bool operator!=(const BTreeIterator<T> &);

private:
    // Ще пазим стек с операции, на върху на който винаги ще искаме да има операция за обработка/извличане на елемент.
    // Операторът * ще връща този елемент на върха на стека, а операторът ++ ще маха елемента от върха на стека и ще го развива, докато друг такъв не е на върха на стека.
    std::stack<Operation<T>> ops;
    void traverse();
};

template <typename T>
class BTree
{
private:
    Node<T> *root;

    void printDot(Node<T> *);

    Node<T> *copy(Node<T> *);
    void cleanup(Node<T> *);

    void inorder(Node<T> *, std::vector<T> &);
    void preoder(Node<T> *, std::vector<T> &);

public:
    BTree();
    BTree(Node<T> *);
    BTree(const BTree<T> &);
    ~BTree();
    BTree<T> &operator=(const BTree<T> &);

    void printDot();

    std::vector<T> inorder();
    std::vector<T> preoder();

    void printInorderStack();
    BTreeIterator<T> begin();
    BTreeIterator<T> end();
    void map(std::function<T(T)>);
};

template <typename T>
Node<T>::Node(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node<T> *left, Node<T> *right) : data(data), left(left), right(right) {}

template <typename T>
void BTreeIterator<T>::traverse()
{
    // Развиваме стека, докато на върха му няма елемент за извличане на елемент
    while (!ops.empty() && ops.top().type != 'p')
    {
        Operation<T> current = ops.top();
        ops.pop();

        if (current.node != nullptr)
        {
            ops.push({current.node->right, 'r'});
            ops.push({current.node, 'p'});
            ops.push({current.node->left, 'r'});
        }
    }
}

template <typename T>
BTreeIterator<T>::BTreeIterator(Node<T> *root)
{
    ops.push({root, 'r'});
    traverse();
}

template <typename T>
T &BTreeIterator<T>::operator*()
{
    return ops.top().node->data;
}

template <typename T>
BTreeIterator<T> &BTreeIterator<T>::operator++()
{
    ops.pop();
    traverse();
    return *this;
}

template <typename T>
bool BTreeIterator<T>::operator!=(const BTreeIterator<T> &other)
{
    if (ops.empty())
    {
        return !other.ops.empty();
    }

    if (other.ops.empty())
    {
        return !ops.empty();
    }

    return ops.top().node != other.ops.top().node;
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
void BTree<T>::inorder(Node<T> *current, std::vector<T> &result)
{
    if (current == nullptr)
    {
        return;
    }

    // ляво
    inorder(current->left, result);

    // корен
    result.push_back(current->data);

    // дясно
    inorder(current->right, result);
}

template <typename T>
void BTree<T>::preoder(Node<T> *current, std::vector<T> &result)
{
    if (current == nullptr)
    {
        return;
    }
    // корен
    result.push_back(current->data);

    // ляво
    preoder(current->left, result);

    // дясно
    preoder(current->right, result);
}

template <typename T>
void BTree<T>::printDot()
{
    std::cout << "digraph G {" << std::endl;
    printDot(root);
    std::cout << "}" << std::endl;
}

template <typename T>
std::vector<T> BTree<T>::inorder()
{
    std::vector<T> result;
    inorder(root, result);
    return result;
}

template <typename T>
std::vector<T> BTree<T>::preoder()
{
    std::vector<T> result;
    preoder(root, result);
    return result;
}

template <typename T>
void BTree<T>::printInorderStack()
{
    std::stack<Operation<T>> ops;
    ops.push({root, 'r'});

    while (!ops.empty())
    {
        Operation<T> current = ops.top();
        ops.pop();

        if (current.node != nullptr)
        {
            if (current.type == 'p')
            {
                std::cout << current.node->data << " ";
            }
            if (current.type == 'r')
            {
                ops.push({current.node->right, 'r'});
                ops.push({current.node, 'p'});
                ops.push({current.node->left, 'r'});
            }
        }
    }
}

template <typename T>
BTreeIterator<T> BTree<T>::begin()
{
    return BTreeIterator<T>(root);
}

template <typename T>
BTreeIterator<T> BTree<T>::end()
{
    return BTreeIterator<T>(nullptr);
}

template <typename T>
void BTree<T>::map(std::function<T(T)> f)
{
    for (T &element : *this)
    {
        element = f(element);
    }
}