#pragma once

#include <stdexcept>

template <typename T>
class DoublyLinkedList
{
private:
    class Node
    {
    public:
        T data;
        Node *previous;
        Node *next;

        Node(const T &);
    };

    template <typename ReturnT>
    class Iterator
    {
    public:
        Node *current;
        Node *last;

        Iterator();
        Iterator(Node *);
        Iterator(Node *, Node *);

        ReturnT operator*();
        Iterator<ReturnT> &operator++();
        Iterator<ReturnT> &operator--();
        bool operator!=(const Iterator<ReturnT> &);
    };

    Node *firstElement;
    Node *lastElement;
    int numberOfElements;

    void copy(const DoublyLinkedList<T> &);
    void cleanup();
    void remove(Node *);
    void insertBefore(Node *, const T &);
    void insertAfter(Node *, const T &);

public:
    Iterator<T> begin() const;
    Iterator<T> end() const;

    Iterator<T &> begin();
    Iterator<T &> end();

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
    bool empty();
    int size();

    template <typename ReturnT>
    void deleteElement(Iterator<ReturnT>);

    template <typename ReturnT>
    void insertAfter(Iterator<ReturnT>, const T &);

    template <typename ReturnT>
    void insertBefore(Iterator<ReturnT>, const T &);
};

template <typename T>
template <typename ReturnT>
DoublyLinkedList<T>::Iterator<ReturnT>::Iterator() : current(nullptr), last(nullptr) {}

template <typename T>
template <typename ReturnT>
DoublyLinkedList<T>::Iterator<ReturnT>::Iterator(Node *current) : current(current), last(nullptr) {}

template <typename T>
template <typename ReturnT>
DoublyLinkedList<T>::Iterator<ReturnT>::Iterator(Node *current, Node *last) : current(current), last(last) {}

template <typename T>
template <typename ReturnT>
ReturnT DoublyLinkedList<T>::Iterator<ReturnT>::operator*()
{
    if (current == nullptr)
        throw std::out_of_range("trying to access elements outside of the list");
    return current->data;
}

template <typename T>
template <typename ReturnT>
typename DoublyLinkedList<T>::template Iterator<ReturnT> &DoublyLinkedList<T>::Iterator<ReturnT>::operator++()
{
    if (current == nullptr)
        throw std::out_of_range("trying to access elements outside of the list");
    current = current->next;
    return *this;
}

template <typename T>
template <typename ReturnT>
typename DoublyLinkedList<T>::template Iterator<ReturnT> &DoublyLinkedList<T>::Iterator<ReturnT>::operator--()
{
    if (current == nullptr && last == nullptr)
        throw std::out_of_range("trying to access elements outside of the list");

    if (current == nullptr)
        current = last;
    else
        current = current->previous;
    return *this;
}

template <typename T>
template <typename ReturnT>
bool DoublyLinkedList<T>::Iterator<ReturnT>::operator!=(const DoublyLinkedList<T>::Iterator<ReturnT> &other)
{
    return current != other.current;
}

template <typename T>
typename DoublyLinkedList<T>::template Iterator<T> DoublyLinkedList<T>::begin() const
{
    return Iterator<T>(firstElement);
}

template <typename T>
typename DoublyLinkedList<T>::template Iterator<T> DoublyLinkedList<T>::end() const
{
    return Iterator<T>(nullptr, lastElement);
}

template <typename T>
typename DoublyLinkedList<T>::template Iterator<T &> DoublyLinkedList<T>::begin()
{
    return Iterator<T &>(firstElement);
}

template <typename T>
typename DoublyLinkedList<T>::template Iterator<T &> DoublyLinkedList<T>::end()
{
    return Iterator<T &>(nullptr, lastElement);
}

template <typename T>
DoublyLinkedList<T>::Node::Node(const T &data) : data(data), next(nullptr), previous(nullptr) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : firstElement(nullptr), lastElement(nullptr), numberOfElements(0) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    cleanup();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &other) : firstElement(nullptr), lastElement(nullptr)
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
    if (other.firstElement == nullptr)
        return;

    Node *current = other.firstElement;
    while (current != other.lastElement)
    {
        pushBack(current->data);
        current = current->next;
    }

    pushBack(current->data);
}

template <typename T>
void DoublyLinkedList<T>::cleanup()
{
    if (firstElement == nullptr)
        return;

    Node *current = firstElement;
    while (current != lastElement)
    {
        Node *toRemove = current;
        current = current->next;
        delete toRemove;
    }

    delete current;
}

template <typename T>
void DoublyLinkedList<T>::remove(Node *node)
{
    if (node == nullptr)
        throw std::out_of_range("trying to access elements outside of the list");

    if (node == firstElement)
    {
        popFront();
        return;
    }
    if (node == lastElement)
    {
        popBack();
        return;
    }

    Node *nodeBefore = node->previous;
    Node *nodeAfter = node->next;
    nodeBefore->next = nodeAfter;
    nodeAfter->previous = nodeBefore;

    numberOfElements--;
    delete node;
}

template <typename T>
void DoublyLinkedList<T>::insertBefore(Node *node, const T &data)
{
    if (node == nullptr)
        throw std::out_of_range("trying to access elements outside of the list");

    if (node == firstElement)
    {
        pushFront(data);
        return;
    }

    Node *newNode = new Node(data);
    newNode->next = node;
    newNode->previous = node->previous;
    node->previous->next = newNode;
    node->previous = newNode;

    numberOfElements++;
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(Node *node, const T &data)
{
    if (node == nullptr)
        throw std::out_of_range("trying to access elements outside of the list");

    if (node == lastElement)
    {
        pushBack(data);
        return;
    }

    insertBefore(node->next, data);
}

template <typename T>
void DoublyLinkedList<T>::pushFront(const T &data)
{
    Node *newNode = new Node(data);

    if (firstElement == nullptr)
    {
        firstElement = newNode;
        lastElement = newNode;
    }
    else
    {
        newNode->next = firstElement;
        firstElement->previous = newNode;

        firstElement = newNode;
    }

    numberOfElements++;
}

template <typename T>
void DoublyLinkedList<T>::popFront()
{
    if (firstElement == nullptr && lastElement == nullptr)
    {
        return;
    }

    if (firstElement == lastElement)
    {
        delete firstElement;
        firstElement = nullptr;
        lastElement = nullptr;
        numberOfElements--;

        return;
    }

    Node *toRemove = firstElement;

    firstElement = firstElement->next;
    firstElement->previous = nullptr;

    delete toRemove;
    numberOfElements--;
}

template <typename T>
void DoublyLinkedList<T>::popBack()
{
    if (firstElement == nullptr && lastElement == nullptr)
    {
        return;
    }

    if (firstElement == lastElement)
    {
        delete firstElement;
        firstElement = nullptr;
        lastElement = nullptr;
        numberOfElements--;

        return;
    }

    Node *toRemove = lastElement;

    lastElement = lastElement->previous;
    lastElement->next = nullptr;

    delete toRemove;
    numberOfElements--;
}

template <typename T>
T DoublyLinkedList<T>::head()
{
    if (firstElement == nullptr)
        throw std::out_of_range("the list is empty");

    return firstElement->data;
}

template <typename T>
T DoublyLinkedList<T>::last()
{
    if (lastElement == nullptr)
        throw std::out_of_range("the list is empty");

    return lastElement->data;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T &data)
{
    Node *newNode = new Node(data);

    if (firstElement == nullptr)
    {
        firstElement = newNode;
        lastElement = newNode;
    }
    else
    {
        lastElement->next = newNode;
        newNode->previous = lastElement;

        lastElement = newNode;
    }

    numberOfElements++;
}

template <typename T>
bool DoublyLinkedList<T>::empty()
{
    return numberOfElements == 0;
}

template <typename T>
int DoublyLinkedList<T>::size()
{
    return numberOfElements;
}

template <typename T>
template <typename ReturnT>
void DoublyLinkedList<T>::deleteElement(DoublyLinkedList<T>::Iterator<ReturnT> iterator)
{
    remove(iterator.current);
}

template <typename T>
template <typename ReturnT>
void DoublyLinkedList<T>::insertBefore(DoublyLinkedList<T>::Iterator<ReturnT> iterator, const T &data)
{
    insertBefore(iterator.current, data);
}

template <typename T>
template <typename ReturnT>
void DoublyLinkedList<T>::insertAfter(DoublyLinkedList<T>::Iterator<ReturnT> iterator, const T &data)
{
    insertAfter(iterator.current, data);
}