#pragma once

#include <cassert>
#include <list>
#include <istream>
#include <string>

template <typename T>
struct TNode
{
    T data;
    std::list<TNode<T> *> children;

    TNode(const T &);
    void addChild(TNode<T> *);
};

template <typename T>
class Tree
{
private:
    TNode<T> *root;

    void serialise(TNode<T> *current);
    static TNode<T> *parseNode(std::istream &);

public:
    Tree(TNode<T> *);

    void serialise();
    static Tree<T> deserialize(std::istream &);

    std::list<std::list<T>> allLevels();
};

template <typename T>
TNode<T>::TNode(const T &data) : data(data) {}

template <typename T>
void TNode<T>::addChild(TNode<T> *child)
{
    children.push_back(child);
}

template <typename T>
Tree<T>::Tree(TNode<T> *root) : root(root) {}

template <typename T>
void Tree<T>::serialise(TNode<T> *current)
{
    if (current == nullptr)
    {
        std::cout << "()";
        return;
    }

    std::cout << "(" << current->data << " (";

    int i = 0;
    for (TNode<T> *child : current->children)
    {
        serialise(child);

        if (i < current->children.size() - 1)
        {
            std::cout << " ";
            i++;
        }
    }

    std::cout << "))";
}

template <typename T>
void Tree<T>::serialise()
{
    serialise(root);
}

template <typename T>
Tree<T> Tree<T>::deserialize(std::istream &in)
{
    Tree<T> result(parseNode(in));
    return result;
}

template <typename T>
TNode<T> *Tree<T>::parseNode(std::istream &in)
{
    // Всяко дърво започва с отваряща скоба
    assert(in.peek() == '(');
    in.get();
    // Ако дървото е празно, връщаме nullptr
    if (in.peek() == ')')
    {
        in.get();
        return nullptr;
    }
    // Четем корена
    T data;
    in >> data;
    TNode<T> *node = new TNode<T>(data);

    // След корена следва празно простраснтво
    assert(in.peek() == ' ');
    in.get();
    // И отваряща скоба за наследниците
    assert(in.peek() == '(');
    in.get();
    // Докато не стигнем до затварящата скоба за наследниците
    while (in.peek() != ')')
    {
        // Четем дете
        TNode<T> *child = parseNode(in);
        if (child != nullptr)
            node->addChild(child);
        // Изчитаме спейса, който следва след всяко дете(освен последното)
        if (in.peek() == ' ')
            in.get();
    }
    // Изчитаме затварящата скоба за наследниците
    in.get();

    // Изчитаме затварящата скоба за дървото
    in.get();

    return node;
}

template <typename T>
std::list<std::list<T>> Tree<T>::allLevels()
{
    // Списък, в който ще трупаме резултата
    std::list<std::list<T>> result;
    // Списък, в който ще трупаме текущо необходените елементи, заедно с височината в дървото, на която се намират
    std::list<std::pair<int, TNode<T> *>> nodes;
    // Започваме от корена, който е на първо ниво
    nodes.push_back({1, root});

    // Докато не обходим всички възли в дървото
    while (!nodes.empty())
    {
        // Вземаме първия
        std::pair<int, TNode<T> *> current = nodes.front();
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

        // Обхождаме всички наследници на текущия и ги слагаме на опашката
        for (TNode<T> *child : current.second->children)
        {
            if (child != nullptr)
            {
                nodes.push_back({current.first + 1, child});
            }
        }
    }

    return result;
}

std::string toSentence(std::list<std::string> l)
{
    std::string sentence;
    int i = 0;
    for (std::string word : l)
    {
        sentence += word;
        if (i < l.size() - 1)
        {
            sentence += " ";
            i++;
        }
    }
    return sentence;
}

bool areAllLevelsTheSameSentence(Tree<std::string> &t)
{
    std::list<std::list<std::string>> levels = t.allLevels();

    if (levels.empty())
        return true;

    std::string sentence = toSentence(levels.front());

    for (std::list<std::string> l : levels)
    {
        if (toSentence(l) != sentence)
            return false;
    }

    return true;
}