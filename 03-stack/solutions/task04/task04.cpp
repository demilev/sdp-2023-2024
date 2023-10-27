#include "../stack/stack.h"

template <typename T>
void reverse(Stack<T> &stack)
{
    Stack<T> tmp;
    while (!stack.empty())
    {
        // Един по един елементите ги слагаме в нов стек. Така този, който е бил на върха, ще отиде най-отдолу в новия стек.
        tmp.push(stack.top());
        stack.pop();
    }

    stack = tmp;
}
