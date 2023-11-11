#pragma once

#include <iostream>
#include <exception>

template <typename T>
class Node
{
public:
    T data;
    Node<T> *previous;
    Node<T> *next;

    Node();
    Node(const T &);
    Node(const T &, Node<T> *, Node<T> *);
};

template <typename T>
class DoublyLinkedList
{
private:
    Node<T> *start;
    Node<T> *end;

    void copy(const DoublyLinkedList<T> &);
    void cleanup();
    void remove(Node<T> *);

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T> &);
    DoublyLinkedList<T> &operator=(const DoublyLinkedList<T> &);
    void pushFront(const T &);
    void popFront();
    void pushBack(const T &);
    void popBack();
    T head();
    T last();
    void print();
    void reverse();
    void removeDuplicates();
    void removeDuplicatesSorted();
};

template <typename T>
Node<T>::Node() : data(), next(nullptr), previous(nullptr) {}

template <typename T>
Node<T>::Node(const T &data) : Node(data, nullptr, nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node<T> *next, Node<T> *previous) : data(data), next(next), previous(previous) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : start(nullptr), end(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    cleanup();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &other): start(nullptr), end(nullptr)
{
    copy(other);
}

template <typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &other)
{
    if (this != &other)
    {
        cleanup();
        copy(other);
    }

    return *this;
}

template <typename T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T> &other)
{
    // Ако другият списък е празен, няма какво да копираме
    if (other.start == nullptr)
        return;

    // Обхобдаме другия списък
    Node<T> *current = other.start;
    while (current != other.end)
    {
        // И добавяме елементите му един по един към текущия списък
        pushBack(current->data);
        current = current->next;
    }

    // Не забравяме да добавим и последния елемент
    pushBack(current->data);
}

template <typename T>
void DoublyLinkedList<T>::cleanup()
{
    // Ако списъкът е празен, няма нужда да правим нищо
    if (start == nullptr)
        return;

    // Обхождаме списъка
    Node<T> *current = start;
    while (current != end)
    {
        // На всяка стъпка изтриваме паметта заделена за текущата кутийка и минаваме на следващата
        Node<T> *toRemove = current;
        current = current->next;
        delete toRemove;
    }

    // Не забравяме да изтрием и последната кутийка
    delete current;
}

// Помощен метод за изтриване на произволна кутийка в списъка
template <typename T>
void DoublyLinkedList<T>::remove(Node<T> *node)
{
    // Първо проверяваме за граничните случаи
    if (node == start)
    {
        popFront();
        return;
    }
    if (node == end)
    {
        popBack();
        return;
    }

    // Преди да изтрием текущата трябва да свържем тази преди нея и тази след нея помежду им
    Node<T> *nodeBefore = node->previous;
    Node<T> *nodeAfter = node->next;
    nodeBefore->next = nodeAfter;
    nodeAfter->previous = nodeBefore;

    delete node;
}

template <typename T>
void DoublyLinkedList<T>::pushFront(const T &data)
{
    // Създаваме новата кутийка
    Node<T> *newNode = new Node<T>(data);

    // Ако списъкът е празен
    if (start == nullptr)
    {
        // И началото и краят ще сочат към новата кутийка
        start = newNode;
        end = newNode;
    }
    // В противен случай
    else
    {
        // Свързаваме новата кутийка с текущата първа
        newNode->next = start;
        start->previous = newNode;

        // Новата кутийка е новата първа
        start = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::print()
{
    // Ако списъкът е празен, няма нужда да правим нищо
    if (start == nullptr)
        return;

    // Обжодаме списъка
    Node<T> *current = start;
    while (current != end)
    {
        // На всяка стъпка отпечатваме текущия елемент и преминаваме на следващия
        std::cout << current->data << " ";
        current = current->next;
    }

    // Не забравяме да отпечатаме и последния
    std::cout << current->data << " ";
}

template <typename T>
void DoublyLinkedList<T>::popFront()
{
    // Ако списъкът е празен, не правим нищо
    if (start == nullptr && end == nullptr)
    {
        return;
    }

    // Ако имаме само един елемент
    if (start == end)
    {
        // Освобождаваме паметта заделена за него
        delete start;
        start = nullptr;
        end = nullptr;

        return;
    }

    Node<T> *toRemove = start;

    // Преместваме началната кутийка
    start = start->next;
    start->previous = nullptr;

    // Изтриваме паметта заделена за нея
    delete toRemove;
}

template <typename T>
void DoublyLinkedList<T>::popBack()
{
    // Ако списъкът е празен, не правим нищо
    if (start == nullptr && end == nullptr)
    {
        return;
    }

    // Ако имаме само един елемент
    if (start == end)
    {
        // Освобождаваме паметта заделена за него
        delete start;
        start = nullptr;
        end = nullptr;

        return;
    }

    Node<T> *toRemove = end;

    // Преместваме крайната кутийка
    end = end->previous;
    end->next = nullptr;

    // Изтриваме паметта заделена за нея
    delete toRemove;
}

template <typename T>
T DoublyLinkedList<T>::head()
{
    if (start == nullptr)
        throw std::out_of_range("the list is empty");

    return start->data;
}

template <typename T>
T DoublyLinkedList<T>::last()
{
    if (end == nullptr)
        throw std::out_of_range("the list is empty");

    return end->data;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T &data)
{
    // Създаваме новата кутийка
    Node<T> *newNode = new Node<T>(data);

    // Ако списъкът е празен
    if (start == nullptr)
    {
        // И началото и краят ще сочат към новата кутийка
        start = newNode;
        end = newNode;
    }
    // В противен случай
    else
    {
        // Свързаваме новата кутийка с текущата последна
        end->next = newNode;
        newNode->previous = end;

        // Новата кутийка е новата последна
        end = newNode;
    }
}

// Един списък може да бъде обърнат, ако му разменим началото и края и ако
// обърнем връзките между всеки две кутийки.
template <typename T>
void DoublyLinkedList<T>::reverse()
{
    // Ако списъкът има <= 1 елемента, няма какво да правим
    if (start == nullptr || start == end)
        return;

    // Ще обхождаме списъка от началото към края
    Node<T> *current = start;

    // Докато не обходим целия списък
    while (current != nullptr)
    {
        // Това което трябва да направим е да "обърнем" текущата кутийка.
        Node<T> *tmp = current->next;
        // next става previous
        current->next = current->previous;
        // а previous става next
        current->previous = tmp;

        // Преминаваме към следващата кутийка в оригиналната наредба
        current = tmp;
    }

    // За финал остава да разменим началото и края
    Node<T> *tmp = start;
    start = end;
    end = tmp;
}

// O(n^2)
template <typename T>
void DoublyLinkedList<T>::removeDuplicates()
{
    // Ще обхождаме списъка от началото към края
    Node<T> *current = start;

    // Докато не обходим списъка
    while (current != nullptr)
    {
        // За всяка кутийка обхождаме всички след нея и махаме тези, които имат същата стойност
        Node<T> *rest = current->next;
        while (rest != nullptr)
        {
            Node<T> *next = rest->next;

            if (rest->data == current->data)
            {
                remove(rest);
            }

            rest = next;
        }

        current = current->next;
    }
}

// O(n)
template <typename T>
void DoublyLinkedList<T>::removeDuplicatesSorted()
{
    if(start == end)
        return;

    Node<T> *current = start;
    Node<T> *next = current->next;

    while (current != end)
    {
        if (current->data == next->data)
        {
            remove(next);
            next = current->next;
        }
        else
        {
            current = current->next;
            if (next != nullptr)
                next = next->next;    
        }


        
    }
}