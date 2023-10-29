#pragma once

#include <list>

/*
    Имплементация на стека използвайки свързан списък от стандартната библиотека.
    Стекът на практика е по-лимитиран модел за достъп на данните организирани по същия начин
    като свързан списък.
*/
template <typename T>
class Stack
{
private:
    std::list<T> elements;

public:
    void push(const T &);
    void pop();
    T top();
    int size();
    bool empty();
};

template <typename T>
T Stack<T>::top()
{
    return elements.front();
}

template <typename T>
void Stack<T>::pop()
{
    elements.pop_front();
}

template <typename T>
void Stack<T>::push(const T &data)
{
    elements.push_front(data);
}

template <typename T>
int Stack<T>::size()
{
    return elements.size();
}

template <typename T>
bool Stack<T>::empty()
{
    return elements.empty();
}
