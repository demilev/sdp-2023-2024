#pragma once

template <typename T>
class Node
{
public:
    T data;
    Node<T> *previous;
    Node<T> *next;

    Node(const T &);
};

template <typename T>
class DoublyLinkedList
{
private:
    Node<T> *start;
    Node<T> *end;

    void remove(Node<T> *);

public:
    void popFront();
    void popBack();

    void removeDuplicates();
    void removeDuplicatesSorted();
};

template <typename T>
void DoublyLinkedList<T>::remove(Node<T> *node)
{
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

    Node<T> *nodeBefore = node->previous;
    Node<T> *nodeAfter = node->next;
    nodeBefore->next = nodeAfter;
    nodeAfter->previous = nodeBefore;

    delete node;
}

template <typename T>
void DoublyLinkedList<T>::popFront()
{
    if (start == nullptr && end == nullptr)
    {
        return;
    }

    if (start == end)
    {
        delete start;
        start = nullptr;
        end = nullptr;

        return;
    }

    Node<T> *toRemove = start;

    start = start->next;
    start->previous = nullptr;

    delete toRemove;
}

template <typename T>
void DoublyLinkedList<T>::popBack()
{
    if (start == nullptr && end == nullptr)
    {
        return;
    }

    if (start == end)
    {
        delete start;
        start = nullptr;
        end = nullptr;

        return;
    }

    Node<T> *toRemove = end;

    end = end->previous;
    end->next = nullptr;

    delete toRemove;
}

// Решение, коете не се възползва от факта, че списъкът е сортиран
// Сложност по време - O(n^2)
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

// Сложност по време - O(n)
template <typename T>
void DoublyLinkedList<T>::removeDuplicatesSorted()
{
    if (start == end)
        return;

    Node<T> *current = start;
    Node<T> *next = current->next;

    // Докато не обходим списъка
    while (next != nullptr)
    {
        // Проверяваме дали текущия елемент е равен на следващия
        if (current->data == next->data)
        {
            // Ако да, трием следващия
            // Забележете, че триенето е с константна сложност
            remove(next);
            next = current->next;
        }
        else
        {
            // В противен случай преминаваме към следващите елементи
            current = current->next;
            next = next->next;
        }
    }
}