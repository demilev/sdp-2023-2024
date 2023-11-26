#pragma once

#include <iostream>
#include <vector>

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
    Node(const T &, Node<T> *, Node<T> *);
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
    bool areSiblings(Node<T> *, const T &, const T &);
    std::vector<T> levelItems(Node<T> *, int);
    Node<T> *lca(Node<T> *, Node<T> *, Node<T> *);
    bool equal(Node<T> *, Node<T> *);
    bool isSubtree(Node<T> *, Node<T> *);
    int diameter(Node<T> *);
    bool isMirror(Node<T> *, Node<T> *);

    // Забележете, че подаваме указател по референция, защото функцията ще го модифицира и искаме промените да
    // се отразят на обекта, с който сме извикали функцията.
    void add(Node<T> *&, const T &, std::string);

    // Стандартните функции, които ползваме при копиране и унищожаване на обекта.
    // Този път сигнатурата им е малко по-различна, за да ги направим по-лесни за изпозлване.
    Node<T> *copy(Node<T> *);
    void cleanup(Node<T> *);

public:
    BTree();
    BTree(Node<T> *);
    BTree(const BTree<T> &);
    ~BTree();
    BTree<T> &operator=(const BTree<T> &);

    void add(const T &, std::string);
    bool member(const T &);

    void print();
    void printDot();

    int height();
    int leafs();
    T leftMostLeaf();
    T min();
    int level(const T &);
    bool areCousines(const T &, const T &);
    std::vector<T> levelItems(int);
    Node<T> *lca(Node<T> *, Node<T> *);
    bool isSubtree(BTree<T> &);
    int diameter();
    bool isSymetric();
};

template <typename T>
Node<T>::Node(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node<T> *left, Node<T> *right) : data(data), left(left), right(right) {}

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
    // От празното дърво няма какво да трием
    if (current == nullptr)
        return;

    // Изтриваме лявото и дясно поддървета
    cleanup(current->left);
    cleanup(current->right);
    // Трием корена
    delete current;
}

template <typename T>
Node<T> *BTree<T>::copy(Node<T> *current)
{
    // Копието на празно дърво е празно дърво
    if (current == nullptr)
        return nullptr;

    // Копието на текущото дърво е дърво, чиито:
    // * корен има същата стойност на корена на другото дърво
    // * ляво поддърво е копие на лявото поддърво на другото дърво
    // * дясно поддърво е копие на дясното поддърво на другото дърво
    return new Node<T>(current->data, copy(current->left), copy(current->right));
}

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

// Функция, която проверява дали два елемента имат общ родител
template <typename T>
bool BTree<T>::areSiblings(Node<T> *current, const T &first, const T &second)
{
    // В празното поддърво нямат общ родител
    if (current == nullptr)
        return false;

    // Ако текущият корен е баща на двата елемента, връщаме истина
    if (
        current->left != nullptr &&
        current->right != nullptr &&
        ((current->left->data == first && current->right->data == second) ||
         (current->left->data == second && current->right->data == first)))
    {
        return true;
    }

    // В противен случай проверяваме дали двата елемента имат общ наследник в някое от поддърветата
    return areSiblings(current->left, first, second) || areSiblings(current->right, first, second);
}

template <typename T>
std::vector<T> BTree<T>::levelItems(Node<T> *current, int level)
{
    // В празното поддърво нямa елементи на това ниво
    if (current == nullptr)
        return std::vector<T>();

    // На първо ниво е само коренът
    if (level == 1)
        return std::vector<T>({current->data});

    // Вземаме елементите от съответното ниво в ляовото и дясното поддървета
    std::vector<T> lefts = levelItems(current->left, level - 1);
    std::vector<T> rights = levelItems(current->right, level - 1);

    // Функция от стандартната библиотека, която ни позволява да конкатенираме двата вектора
    lefts.insert(lefts.end(), rights.begin(), rights.end());

    return lefts;
}

template <typename T>
Node<T> *BTree<T>::lca(Node<T> *current, Node<T> *first, Node<T> *second)
{
    // В празното поддърво нямат най-близък общ наследник
    if (current == nullptr)
        return nullptr;

    // Ако един от двата елемента е корен на текущото дърво, то той е и най-близкият общ наследник
    if (current == first)
        return current;
    if (current == second)
        return current;

    // Намираме най-малкия общ наследник в лявото и дясното поддърво
    Node<T> *leftLca = lca(current->left, first, second);
    Node<T> *rightLca = lca(current->right, first, second);

    // Ако и двата съществуват, това означава, че единият елемент сме го намерили в едното поддърво, а другият в другото.
    // Това означава, че текущият корен е най-близък общ наследник
    if (leftLca != nullptr && rightLca != nullptr)
        return current;

    // В противен случай връщаме един от двата
    return leftLca != nullptr ? leftLca : rightLca;
}

// Фунцкия, която проверява дали две дървета са напълно еднакви
template <typename T>
bool BTree<T>::equal(Node<T> *first, Node<T> *second)
{
    if (first == nullptr && second == nullptr)
        return true;
    if (first == nullptr)
        return false;
    if (second == nullptr)
        return false;

    return (first->data == second->data && equal(first->left, second->left) && equal(first->right, second->right));
}

template <typename T>
bool BTree<T>::isSubtree(Node<T> *first, Node<T> *second)
{
    if (second == nullptr)
        return true;
    if (first == nullptr)
        return false;

    if (equal(first, second))
        return true;

    return isSubtree(first->left, second) || isSubtree(first->right, second);
}

template <typename T>
int BTree<T>::diameter(Node<T> *current)
{
    if (current == nullptr)
        return 0;

    int leftDiameter = diameter(current->left);
    int rightDiameter = diameter(current->right);

    int leftHeight = height(current->left);
    int rightHeight = height(current->right);

    // Диаметър на едно дърво е по-голямото от следните три неща:
    // * височината на лявото + височината на дясното
    // * диаметъра на лявото дърво
    // * диаметъра на дясното дърво
    //
    // Реално търсим поддървото с най-голяма сума на височините на ляво и дясно
    return std::max(leftHeight + rightHeight, std::max(leftDiameter, rightDiameter));
}

template <typename T>
bool BTree<T>::isMirror(Node<T> *first, Node<T> *second)
{
    if (first == nullptr && second == nullptr)
        return true;
    if (first == nullptr || second == nullptr)
        return false;
    return first->data == second->data && isMirror(first->left, second->right) && isMirror(first->right, second->left);
}

template <typename T>
void BTree<T>::add(Node<T> *&current, const T &data, std::string path)
{
    if (current == nullptr)
    {
        // Ако дървото е празно, го създаваме
        if (path.empty())
            current = new Node<T>(data);

        return;
    }

    // Ако сме изчерпали пътя, значи трябва да променим текущия корен
    if (path.empty())
        current->data = data;

    // Ако трябва да добавим в лявото поддърво
    if (path[0] == 'L')
    {
        // тръгваме наляво
        add(current->left, data, path.substr(1, path.size() - 1));
        return;
    }
    if (path[0] == 'R')
    {
        // в противен случай тръгваме надясно
        add(current->right, data, path.substr(1, path.size() - 1));
        return;
    }
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

template <typename T>
bool BTree<T>::areCousines(const T &first, const T &second)
{
    // Братовчеди са, ако са не едно ниво, но нямат общ родител
    return level(root, first, 1) == level(root, second, 1) && !areSiblings(root, first, second);
}

template <typename T>
std::vector<T> BTree<T>::levelItems(int level)
{
    return levelItems(root, level);
}

template <typename T>
Node<T> *BTree<T>::lca(Node<T> *first, Node<T> *second)
{
    return lca(root, first, second);
}

template <typename T>
bool BTree<T>::isSubtree(BTree<T> &other)
{
    return isSubtree(root, other.root);
}

template <typename T>
int BTree<T>::diameter()
{
    return diameter(root);
}

template <typename T>
bool BTree<T>::isSymetric()
{
    // Едно дърво е симетрично, ако е огледален образ на себе си
    return isMirror(root, root);
}

template <typename T>
void BTree<T>::add(const T &data, std::string path)
{
    add(root, data, path);
    return;
}