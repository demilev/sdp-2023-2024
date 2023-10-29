#pragma once

#include <stdexcept>

template <typename T>
class Stack
{
private:
    class Node
    {
    public:
        T data;
        Node *next;

        Node(const T &);
    };

    Node *head;
    int numberOfElements;

    void copy(const Stack<T> &);
    void cleanup();

public:
    Stack();
    ~Stack();
    Stack(const Stack<T> &);
    Stack<T> &operator=(const Stack<T> &);

    void push(const T &);
    void pop();
    T top();
    int size();
    bool empty();
};

template <typename T>
Stack<T>::Node::Node(const T &data) : data(data), next(nullptr) {}

template <typename T>
void Stack<T>::cleanup()
{
    while (!empty())
    {
        pop();
    }
}

template <typename T>
void Stack<T>::copy(const Stack<T> &other)
{
    if (other.head == nullptr)
    {
        this->head = nullptr;
        return;
    }

    Node *newHead = new Node(other.head->data);
    this->head = newHead;

    Node *currentOther = other.head->next;
    Node *previous = newHead;

    while (currentOther != nullptr)
    {
        Node *newNode = new Node(currentOther->data);
        previous->next = newNode;
        previous = newNode;
        currentOther = currentOther->next;
    }

    this->numberOfElements = other.numberOfElements;
}

template <typename T>
Stack<T>::Stack() : head(nullptr), numberOfElements(0) {}

template <typename T>
Stack<T>::~Stack()
{
    cleanup();
}

template <typename T>
Stack<T>::Stack(const Stack<T> &other) : head(nullptr), numberOfElements(0)
{
    copy(other);
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other)
{
    if (this != &other)
    {
        cleanup();
        copy(other);
    }

    return *this;
}

template <typename T>
T Stack<T>::top()
{
    if (head != nullptr)
    {
        return head->data;
    }
    else
    {
        throw std::out_of_range("the stack is empty");
    }
}

template <typename T>
void Stack<T>::pop()
{
    if (head != nullptr)
    {
        Node *toDelete = head;
        head = head->next;
        delete toDelete;
        numberOfElements--;
    }
}

template <typename T>
void Stack<T>::push(const T &data)
{
    Node *newNode = new Node(data);
    newNode->next = head;
    head = newNode;
    numberOfElements++;
}

template <typename T>
int Stack<T>::size()
{
    return numberOfElements;
}

template <typename T>
bool Stack<T>::empty()
{
    return numberOfElements == 0;
}
