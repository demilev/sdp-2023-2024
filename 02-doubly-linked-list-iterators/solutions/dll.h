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

template <typename T, typename ReturnT>
class DoublyLinkedListIterator
{
private:
    Node<T> *current;
    // Ще пазим указател и към последния елемент, за да можем да изпълняваме -- операция върху end() итератора на DoublyLinkedList
    Node<T> *last;

public:
    DoublyLinkedListIterator();
    DoublyLinkedListIterator(Node<T> *);
    DoublyLinkedListIterator(Node<T> *, Node<T> *);

    ReturnT operator*();                                           // Оператор за вземане на текущата стойност
    DoublyLinkedListIterator<T, ReturnT> &operator++();            // Оператор за преместване на итератора към следващ елемент
    DoublyLinkedListIterator<T, ReturnT> &operator--();            // Оператор за преместване на итератора към предишен елемент
    bool operator!=(const DoublyLinkedListIterator<T, ReturnT> &); // Оператор за сравнение с друг итератор

    template <typename C>
    friend class DoublyLinkedList;
};

template <typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT>::DoublyLinkedListIterator() : current(nullptr), last(nullptr) {}

template <typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT>::DoublyLinkedListIterator(Node<T> *current) : current(current), last(nullptr) {}

template <typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT>::DoublyLinkedListIterator(Node<T> *current, Node<T> *last) : current(current), last(last) {}

template <typename T, typename ReturnT>
ReturnT DoublyLinkedListIterator<T, ReturnT>::operator*()
{
    return current->data;
}

template <typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT> &DoublyLinkedListIterator<T, ReturnT>::operator++()
{
    current = current->next;
    return *this;
}

template <typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT> &DoublyLinkedListIterator<T, ReturnT>::operator--()
{
    /*
        "Хак", с който си позволяваме да направим следното:

        DoublyLinkedList<int> list;
        DoublyLinkedListIterator<int, int> iterator = list.end(); // тук iterator сочи след последния елемент
        --iterator; // iterator вече сочи към последния елемент
    */
    if (current == nullptr)
        current = last;
    else
        current = current->previous;
    return *this;
}

template <typename T, typename ReturnT>
bool DoublyLinkedListIterator<T, ReturnT>::operator!=(const DoublyLinkedListIterator<T, ReturnT> &other)
{
    return current != other.current;
}

template <typename T>
class DoublyLinkedList
{
private:
    Node<T> *start;
    Node<T> *_end;

    void copy(const DoublyLinkedList<T> &);
    void cleanup();
    void remove(Node<T> *);

public:
    // Версия на методите за константни DoublyLinkedList обекти. За тях връщаме итератор, през който не можем да променяме елементите, а само да ги четем.
    DoublyLinkedListIterator<T, T> begin() const;
    DoublyLinkedListIterator<T, T> end() const;

    DoublyLinkedListIterator<T, T &> begin();
    DoublyLinkedListIterator<T, T &> end();

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
    bool isEmpty();

    template <typename ReturnT>
    void deleteElement(DoublyLinkedListIterator<T, ReturnT>);
};

template <typename T>
DoublyLinkedListIterator<T, T> DoublyLinkedList<T>::begin() const
{
    return DoublyLinkedListIterator<T, T>(start);
}

template <typename T>
DoublyLinkedListIterator<T, T> DoublyLinkedList<T>::end() const
{
    return DoublyLinkedListIterator<T, T>(nullptr, _end);
}

template <typename T>
DoublyLinkedListIterator<T, T &> DoublyLinkedList<T>::begin()
{
    return DoublyLinkedListIterator<T, T &>(start);
}

template <typename T>
DoublyLinkedListIterator<T, T &> DoublyLinkedList<T>::end()
{
    return DoublyLinkedListIterator<T, T &>(nullptr, _end);
}

template <typename T>
Node<T>::Node() : data(), next(nullptr), previous(nullptr) {}

template <typename T>
Node<T>::Node(const T &data) : Node(data, nullptr, nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node<T> *next, Node<T> *previous) : data(data), next(next), previous(previous) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : start(nullptr), _end(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    cleanup();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &other) : start(nullptr), _end(nullptr)
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
    while (current != other._end)
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
    while (current != _end)
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
    if (node == _end)
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
        _end = newNode;
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
    while (current != _end)
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
    if (start == nullptr && _end == nullptr)
    {
        return;
    }

    // Ако имаме само един елемент
    if (start == _end)
    {
        // Освобождаваме паметта заделена за него
        delete start;
        start = nullptr;
        _end = nullptr;

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
    if (start == nullptr && _end == nullptr)
    {
        return;
    }

    // Ако имаме само един елемент
    if (start == _end)
    {
        // Освобождаваме паметта заделена за него
        delete start;
        start = nullptr;
        _end = nullptr;

        return;
    }

    Node<T> *toRemove = _end;

    // Преместваме крайната кутийка
    _end = _end->previous;
    _end->next = nullptr;

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
    if (_end == nullptr)
        throw std::out_of_range("the list is empty");

    return _end->data;
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
        _end = newNode;
    }
    // В противен случай
    else
    {
        // Свързаваме новата кутийка с текущата последна
        _end->next = newNode;
        newNode->previous = _end;

        // Новата кутийка е новата последна
        _end = newNode;
    }
}

// Един списък може да бъде обърнат, ако му разменим началото и края и ако
// обърнем връзките между всеки две кутийки.
template <typename T>
void DoublyLinkedList<T>::reverse()
{
    // Ако списъкът има <= 1 елемента, няма какво да правим
    if (start == nullptr || start == _end)
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
    start = _end;
    _end = tmp;
}

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

template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
    return start == nullptr;
}

template <typename T>
template <typename ReturnT>
void DoublyLinkedList<T>::deleteElement(DoublyLinkedListIterator<T, ReturnT> iterator)
{
    remove(iterator.current);
}