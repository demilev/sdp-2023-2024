#pragma once

#include <iostream>

// Градивния елемент на дървото
template <typename T>
struct Node
{
    // Всяко дърво си има корен, в който има някакви данни
    T data;
    // Ляво поддърво
    Node<T> *left;
    // Дясно поддърво
    Node<T> *right;

    Node(const T &);
};

// Клас, представляващ двоично дърво
template <typename T>
class BTree
{
private:
    // Едно дърво еднозначно се определя от корена си
    Node<T> *root;

    // Почти всички методи за дървета ще са рекурсивни.
    // За всеки публичен метод ще имаме по един помощен private такъв,
    // който допълнително приема указател към поддървото, до което сме стигнали в рекурсивните извиквания
    bool member(Node<T> *, const T &);
    int height(Node<T> *);
    int leafs(Node<T> *);
    void print(Node<T> *);
    void printDot(Node<T> *);
    T min(Node<T> *);
    int level(Node<T> *, const T &, int);

public:
    BTree();
    BTree(Node<T> *);

    bool member(const T &);
    int height();
    int leafs();
    void print();
    void printDot();

    T leftMostLeaf();
    T min();
    int level(const T &);
};

template <typename T>
Node<T>::Node(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
BTree<T>::BTree() : root(nullptr) {}

template <typename T>
BTree<T>::BTree(Node<T> *root) : root(root) {}

template <typename T>
bool BTree<T>::member(Node<T> *current, const T &data)
{
    // Никой елемент не принадлежи на празното дърво
    if (current == nullptr)
        return false;

    // Един елемент принадлежи на дърво, ако:
    return current->data == data ||       // съвпада със стойността на корена му
           member(current->left, data) || // или се намира в лявото му поддърво
           member(current->right, data);  // // или се намира в дясното му поддърво
}

template <typename T>
int BTree<T>::height(Node<T> *current)
{

    // Височината на празното дърво е 0
    if (current == nullptr)
    {
        return 0;
    }

    int heightL = height(current->left);
    int heightR = height(current->right);

    // Височината на едно дърво е 1 + по-голямата от височините на дясното и лявото поддървета
    return 1 + std::max(heightL, heightR);
}

template <typename T>
int BTree<T>::leafs(Node<T> *current)
{

    // Празното дърво няма листа
    if (current == nullptr)
    {
        return 0;
    }

    // Дървото без поддървета е листо само по себе си
    if (current->left == nullptr && current->right == nullptr)
    {
        return 1;
    }

    int leafsL = leafs(current->left);
    int leafsR = leafs(current->right);

    // Едно дърво има толкова листа, колкото имат общо двете му поддървета
    return leafsL + leafsR;
}

template <typename T>
T BTree<T>::min(Node<T> *current)
{

    // В дървото без поддървета най-малкият елемент е коренът
    if (current->left == nullptr && current->right == nullptr)
    {
        return current->data;
    }

    // В дърво без ляво поддърво най-малкият елемент е или коренът, или най-малкият елемент на дясното поддърво
    if (current->left == nullptr)
    {
        T minR = min(current->right);
        return std::min(current->data, minR);
    }

    // В дърво без дясно поддърво най-малкият елемент е или коренът, или най-малкият елемент на лявото поддърво
    if (current->right == nullptr)
    {
        T minL = min(current->left);
        return std::min(current->data, minL);
    }

    T minL = min(current->left);
    T minR = min(current->right);
    // В едно дърво най-малкият елемент е или коренът, или най-малкият елемент на лявото поддърво, или най-малкият елемент на дясното поддърво
    return std::min(minL, std::min(current->data, minR));
}

template <typename T>
void BTree<T>::print(Node<T> *current)
{

    // За празното дърво няма какво да отпечатваме
    if (current == nullptr)
    {
        return;
    }

    // Печатаме корен
    std::cout << current->data << " ";
    // Ляво
    print(current->left);
    // Дясно
    print(current->right);
}

// Функцията за принтиране в dot формат е много подобна с изключение на това, че в допълнение
// на отпечтване на самите данни на дървото, трябва да отпечатаме и информация за самите възли в дървото.
// Всеки възел трябва да има уникален идентификатор. За целта ползваме адреса в паметта му.
template <typename T>
void BTree<T>::printDot(Node<T> *current)
{

    if (current == nullptr)
    {
        return;
    }

    // Кутийка с адрес current има стойснот current->data
    std::cout << (long)current << "[label=\"" << current->data << "\"]" << std::endl;

    if (current->left != nullptr)
    {
        // Кутийка с адрес current има връзка към кутийка с адрес current->left
        std::cout << (long)current << " -> " << (long)current->left << std::endl;
    }

    if (current->right != nullptr)
    {
        // Кутийка с адрес current има връзка към кутийка с адрес current->right
        std::cout << (long)current << " -> " << (long)current->right << std::endl;
    }

    printDot(current->left);
    printDot(current->right);
}

// Тази функция се различава от предишните с това, че пазим и допълнителен контекст при рекурсивните извкивания.
// В случая има допълнителен параметър, оказващ текущото ниво, на което се намираме.
template <typename T>
int BTree<T>::level(Node<T> *current, const T &data, int currentLevel)
{
    // Никой елемент не принадлежи на празното дърво
    if (current == nullptr)
    {
        return -1;
    }

    // Ако сме открили елемента, връщаме текущото ниво
    if (current->data == data)
        return currentLevel;

    // Търсим елемента в лявото поддърво
    int leftL = level(current->left, data, currentLevel + 1);

    // Ако сме го намерили, връщаме нивото, на коеото е в лявото поддърво
    if (leftL >= 0)
        return leftL;

    // В противен случай търсим в дясното
    return level(current->right, data, currentLevel + 1);
}

template <typename T>
bool BTree<T>::member(const T &data)
{
    return member(root, data);
}

template <typename T>
int BTree<T>::height()
{
    return height(root);
}

template <typename T>
int BTree<T>::leafs()
{
    return leafs(root);
}

template <typename T>
void BTree<T>::print()
{
    print(root);
    std::cout << std::endl;
}

template <typename T>
void BTree<T>::printDot()
{
    std::cout << "digraph G {" << std::endl;
    printDot(root);
    std::cout << "}" << std::endl;
}

// Една от малкото нерекурсивни функции за дървета.
// Възползваме се от факта, че вървим по един конкретен път, за да стигнем до най-лявото листо.
template <typename T>
T BTree<T>::leftMostLeaf()
{
    // Заповчваме от корена
    Node<T> *current = root;

    // Докато не стигнем листо
    while (current->left != nullptr && current->right != nullptr)
    {
        // Ако можем да тръгнем наляво, тръгваме наляво
        if (current->left != nullptr)
        {
            current = current->left;
        }
        else
        {
            // В противен случай тръгваме надясно
            current = current->right;
        }
    }

    return current->data;
}

template <typename T>
T BTree<T>::min()
{
    return min(root);
}

template <typename T>
int BTree<T>::level(const T &data)
{
    return level(root, data, 1);
}