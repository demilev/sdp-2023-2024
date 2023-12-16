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
    int numberOfElements;

    void printDot(Node<T> *);

    void printLeft(Node<T> *);
    void printRight(Node<T> *);

    Node<T> *copy(Node<T> *);
    void cleanup(Node<T> *);
    T min(Node<T> *);
    T max(Node<T> *);
    T minSorted(Node<T> *);
    T maxSorted(Node<T> *);
    bool isBST(Node<T> *);
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

    void printDot();
    bool isBST();
    T min();
    T max();
    bool member(const T &);
    void add(const T &);
    void remove(const T &);

    int size();
    std::vector<T> range(const T &, const T &);
};

template <typename T>
Node<T>::Node(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node<T> *left, Node<T> *right) : data(data), left(left), right(right) {}

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

// Версия на функцията за намиране на най-малък елемент, в която не се въпзолзваме от факта, че
// дървото е наредено, а просто го обхождаме цялото.
template <typename T>
T BSTree<T>::min(Node<T> *current)
{

    if (current->left == nullptr && current->right == nullptr)
    {
        return current->data;
    }

    if (current->left == nullptr)
    {
        T minR = min(current->right);
        return std::min(current->data, minR);
    }

    if (current->right == nullptr)
    {
        T minL = min(current->left);
        return std::min(current->data, minL);
    }

    T minL = min(current->left);
    T minR = min(current->right);

    return std::min(minL, std::min(current->data, minR));
}

// Версия на функцията за намиране на най-голям елемент, в която не се въпзолзваме от факта, че
// дървото е наредено, а просто го обхождаме цялото.
template <typename T>
T BSTree<T>::max(Node<T> *current)
{

    if (current->left == nullptr && current->right == nullptr)
    {
        return current->data;
    }

    if (current->left == nullptr)
    {
        T minR = max(current->right);
        return std::max(current->data, minR);
    }

    if (current->right == nullptr)
    {
        T minL = max(current->left);
        return std::max(current->data, minL);
    }

    T minL = max(current->left);
    T minR = max(current->right);

    return std::max(minL, std::max(current->data, minR));
}

// Версия на функцията за намиране на най-малък елемент, в която се въпзолзваме от факта, че
// дървото е наредено.
template <typename T>
T BSTree<T>::minSorted(Node<T> *current)
{
    if (current == nullptr)
        throw "the tree is empty";

    // Най-малкият елемент е този който е най-вляво в дървото(този който няма ляв наследник)
    while (current->left != nullptr)
    {
        current = current->left;
    }

    return current->data;
}

// Версия на функцията за намиране на най-голям елемент, в която се въпзолзваме от факта, че
// дървото е наредено.
template <typename T>
T BSTree<T>::maxSorted(Node<T> *current)
{
    if (current == nullptr)
        throw "the tree is empty";

    // Най-големият елемент е този който е най-вдясно в дървото(този който няма десен наследник)
    while (current->right != nullptr)
    {
        current = current->right;
    }

    return current->data;
}

template <typename T>
bool BSTree<T>::isBST(Node<T> *current)
{

    // Празното дърво е наредено
    if (current == nullptr)
        return true;

    T maxLeft = current->left != nullptr ? max(current->left) : current->data;
    T minRight = current->right != nullptr ? min(current->right) : current->data;

    // Едно дърво е наредено, ако:
    return current->data >= maxLeft &&  // коренът е по-голям от всички елементи в лявото поддърво
           current->data <= minRight && // коренът е по-малък от всички елементи в дясното поддърво
           isBST(current->left) &&      // лявото поддърво е наредено
           isBST(current->right);       // дясното поддърво е наредено
}

// Версия на функцията за търсене на елемент в дърво, в която се въпзолзваме от факта, че
// дървото е наредено.
template <typename T>
bool BSTree<T>::member(Node<T> *current, const T &data)
{
    if (current == nullptr)
        return false;

    if (current->data == data)
        return true;

    // Ако търсеният елемент е по-малък от корена, го търсим в лявото поддърво.
    // Няма смисъл да го търсим в дясното поддърво, защото там всички елементи са по-големи от корена.
    if (current->data > data)
        return member(current->left, data);

    // Ако търсеният елемент е по-голям от корена, го търсим в дясното поддърво.
    // Няма смисъл да го търсим в лявото поддърво, защото там всички елементи са по-малки от корена.
    if (current->data < data)
        return member(current->right, data);

    return false;
}

template <typename T>
void BSTree<T>::add(Node<T> *&current, const T &data)
{
    // Добавяне в празното дърво
    if (current == nullptr)
    {
        numberOfElements++;
        // Създаваме нов възел
        current = new Node<T>(data);
    }

    // Трябва да добавим новия елемент, така че  да запазим наредбата. Т.е. ако е по-малък от текущия, трябва да го добавим в лявото поддърво.
    if (current->data > data)
    {
        add(current->left, data);
        return;
    }

    // Ако е по-голям от текущия, трябва да го добавим в дясното поддърво.
    if (current->data < data)
    {
        add(current->right, data);
        return;
    }

    return;
}

// За повече информация - https://github.com/demilev/sdp-2023-2024/blob/main/extra/bst-remove.md
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

    // Трием листо
    if (current->left == nullptr && current->right == nullptr)
    {
        delete current;
        numberOfElements--;
        current = nullptr;
        return;
    }

    // Трием елемент с един наследник
    if (current->left == nullptr && current->right != nullptr)
    {

        Node<T> *tmp = current;
        current = current->right;
        delete tmp;
        numberOfElements--;
    }
    // Трием елемент с един наследник
    else if (current->left != nullptr && current->right == nullptr)
    {

        Node<T> *tmp = current;
        current = current->left;
        delete tmp;
        numberOfElements--;
    }
    else
    {
        // Вариант 1
        T minRight = minSorted(current->right);
        current->data = minRight;
        remove(current->right, minRight);

        // Вариант 2
        // Т maxLeft = maxSorted(current->left);
        // current->data = maxLeft;
        // remove(current->left, maxLeft);
    }

    return;
}

template <typename T>
void BSTree<T>::range(Node<T> *current, const T &from, const T &to, std::vector<T> &result)
{
    if (current == nullptr)
        return;

    // Ако текущият елемент е по-голям от долната граница, обхождаме и лявото поддърво
    if (current->data > from)
        range(current->left, from, to, result);

    if (current->data > from && current->data < to)
        result.push_back(current->data);

    // Ако текущият елемент е по-малък от горната граница, обхождаме и дясното поддърво
    if (current->data < to)
        range(current->right, from, to, result);
}

template <typename T>
void BSTree<T>::printDot()
{
    std::cout << "digraph G {" << std::endl;
    printDot(root);
    std::cout << "}" << std::endl;
}

template <typename T>
bool BSTree<T>::isBST()
{
    return isBST(root);
}

template <typename T>
bool BSTree<T>::member(const T &data)
{
    return member(root, data);
}

template <typename T>
T BSTree<T>::min()
{
    return minSorted(root);
}

template <typename T>
T BSTree<T>::max()
{
    return maxSorted(root);
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
