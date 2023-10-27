#pragma once

#include <stdexcept>

template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;

    Node();
    Node(const T &);
};

template <typename T>
class Stack
{
private:
    Node<T> *head;
    int numberOfElements;

    void copy(const Stack<T> &);
    void cleanup();

public:
    Stack();
    ~Stack();
    Stack(const Stack<T> &);
    Stack<T> &operator=(const Stack<T> &);

    void push(const T &); // - слага елемент на върха на стека
    void pop();           // - премахва елемента от върха на стека
    T top();              // - връща елемента от върха на стека
    int size();           // - връща броя на елементите в стека
    bool empty();         // - проверява дали стекът е празен
};

template <typename T>
Node<T>::Node() : data(), next(nullptr) {}

template <typename T>
Node<T>::Node(const T &data) : data(data), next(nullptr) {}

template <typename T>
void Stack<T>::cleanup()
{
    // Докато има елементи,
    while (!empty())
    {
        // ги махаме един по един
        pop();
    }
}

template <typename T>
void Stack<T>::copy(const Stack<T> &other)
{
    // Ако другият е празен, няма какво да копираме
    if (other.head == nullptr)
    {
        this->head = nullptr;
        return;
    }

    // Създаваме началната кутия
    Node<T> *newhead = new Node<T>(other.head->data);
    this->head = newhead;

    // Ще пазим два указателя - един, който върви по другия стек и един, който върви по текущия
    Node<T> *currentOther = other.head->next;
    Node<T> *previous = newhead;

    // Докато не стигнем края на другия
    while (currentOther != nullptr)
    {
        // Създаваме нова кутийка
        Node<T> *newNode = new Node<T>(currentOther->data);
        // Добавяме я към текущия стек
        previous->next = newNode;
        // Местим указателите напред
        previous = newNode;
        currentOther = currentOther->next;
    }

    // Не забравяме и да "копираме" размера
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
        // Запазваме връзка към текущия елемент на стека
        Node<T> *toDelete = head;
        // Преместваме се към следващия елемент
        head = head->next;
        // Трием предишния
        delete toDelete;
        numberOfElements--;
    }
}

template <typename T>
void Stack<T>::push(const T &data)
{
    // Създаваме нова кутийка
    Node<T> *newNode = new Node<T>(data);
    // Свързваме я с тази, която е на върха на стека
    newNode->next = head;
    // Новата кутийка е на върха на стека
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
