#pragma once

#include <stdexcept>
#include <stack>

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
    char type;
};

template <typename T>
class BTreeIterator
{
public:
    BTreeIterator(Node<T> *);
    BTreeIterator<T> &operator++();
    T operator*();
    bool operator!=(const BTreeIterator<T> &);

private:
    std::stack<Operation<T>> ops;
    void traverse();
};

template <typename T>
class BSTree
{
private:
    Node<T> *root;
    int numberOfElements;

    Node<T> *copy(Node<T> *);
    void cleanup(Node<T> *);

    T min(Node<T> *);
    T max(Node<T> *);

    bool member(Node<T> *, const T &);
    void add(Node<T> *&, const T &);
    void remove(Node<T> *&, const T &);

    void range(Node<T> *, const T &, const T &, std::vector<T> &);

public:
    BSTree();
    BSTree(Node<T> *);
    BSTree(const BSTree<T> &);
    ~BSTree();
    BSTree<T> &operator=(const BSTree<T> &);

    T min();
    T max();

    bool member(const T &);
    void add(const T &);
    void remove(const T &);

    int size();

    BTreeIterator<T> begin();
    BTreeIterator<T> end();

    std::vector<T> range(const T &, const T &);
};

template <typename T>
Node<T>::Node(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node<T> *left, Node<T> *right) : data(data), left(left), right(right) {}

template <typename T>
void BTreeIterator<T>::traverse()
{
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
T BTreeIterator<T>::operator*()
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
BSTree<T>::BSTree() : root(nullptr), numberOfElements(0) {}

template <typename T>
BSTree<T>::BSTree(Node<T> *root) : root(root), numberOfElements(0) {}

template <typename T>
BSTree<T>::~BSTree()
{
    cleanup(root);
}

template <typename T>
BSTree<T>::BSTree(const BSTree<T> &other) : root(nullptr)
{
    root = copy(other.root);
    numberOfElements = other.numberOfElements;
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
T BSTree<T>::min(Node<T> *current)
{
    if (current == nullptr)
        throw std::out_of_range("the tree is empty");

    while (current->left != nullptr)
    {
        current = current->left;
    }

    return current->data;
}

template <typename T>
T BSTree<T>::max(Node<T> *current)
{
    if (current == nullptr)
        throw std::out_of_range("the tree is empty");

    while (current->right != nullptr)
    {
        current = current->right;
    }

    return current->data;
}

template <typename T>
bool BSTree<T>::member(Node<T> *current, const T &data)
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
void BSTree<T>::add(Node<T> *&current, const T &data)
{
    if (current == nullptr)
    {
        numberOfElements++;
        current = new Node<T>(data);
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
void BSTree<T>::remove(Node<T> *&current, const T &data)
{
    if (current == nullptr)
    {
        return;
    }

    if (current->data > data)

    {
        remove(current->left, data);
        return;
    }

    if (current->data < data)
    {
        remove(current->right, data);
        return;
    }

    if (current->left == nullptr && current->right == nullptr)
    {
        delete current;
        numberOfElements--;
        current = nullptr;
        return;
    }

    if (current->left == nullptr && current->right != nullptr)
    {

        Node<T> *tmp = current;
        current = current->right;
        delete tmp;
        numberOfElements--;
    }
    else if (current->left != nullptr && current->right == nullptr)
    {

        Node<T> *tmp = current;
        current = current->left;
        delete tmp;
        numberOfElements--;
    }
    else
    {
        T minRight = min(current->right);
        current->data = minRight;
        remove(current->right, minRight);
    }

    return;
}

template <typename T>
void BSTree<T>::range(Node<T> *current, const T &from, const T &to, std::vector<T> &result)
{
    if (current == nullptr)
        return;

    if (current->data > from)
        range(current->left, from, to, result);

    if (current->data > from && current->data < to)
        result.push_back(current->data);

    if (current->data < to)
        range(current->right, from, to, result);
}

template <typename T>
bool BSTree<T>::member(const T &data)
{
    return member(root, data);
}

template <typename T>
T BSTree<T>::min()
{
    return min(root);
}

template <typename T>
T BSTree<T>::max()
{
    return max(root);
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
int BSTree<T>::size()
{
    return numberOfElements;
}

template <typename T>
std::vector<T> BSTree<T>::range(const T &from, const T &to)
{
    std::vector<T> result;
    range(root, from, to, result);
    return result;
}

template <typename T>
BTreeIterator<T> BSTree<T>::begin()
{
    return BTreeIterator<T>(root);
}

template <typename T>
BTreeIterator<T> BSTree<T>::end()
{
    return BTreeIterator<T>(nullptr);
}
