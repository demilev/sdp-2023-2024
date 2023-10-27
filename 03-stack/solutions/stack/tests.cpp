#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "stack.h"

// Тест за създаване на Node
TEST_CASE("testing the creation of a Node")
{
    // Създаваме Node с конструктора му с един параметър
    Node<int> node(5);

    // Проверяваме, че данните, които държи, са тези, които сме подали в конструктора 
    CHECK(node.data == 5);
    // Проверяваме, че няма наследник
    CHECK(node.next == nullptr);
}

// Тест за добавяне на елемент в стек
TEST_CASE("testing the insertion of a Node")
{
    // Създаваме празен стек
    Stack<int> stack;

    // Добавяме му един елемент в началото
    stack.push(5);
    // Проверяваме, че в началото стои този елемент
    CHECK(stack.top() == 5);

    // Добавяме нов елемент в началото
    stack.push(6);
    // Проверяваме, че в началото стои този елемент
    CHECK(stack.top() == 6);
}

// Тест за премахване на елемент от стек
TEST_CASE("testing the removing of a Node")
{
    // Създаваме празен стек
    Stack<int> stack;

    // Добавяме му два елемента в началото
    stack.push(5);
    stack.push(6);

    // Премахваме единия
    stack.pop();
    // Проверяваме, че другият е в началото на стека
    CHECK(stack.top() == 5);
}

// Тест за опит за премахване на елемент от празен стек
TEST_CASE("testing the removing of a Node in an empty stack")
{
    // Създаваме празен стек
    Stack<int> stack;
    // Опитваме се да премахнем елемент - тази операция не трябва да прави нищо в такъв случай
    stack.pop();

    // Добавяме един елемент и проверяваме, че е на първа позиция
    stack.push(5);
    CHECK(stack.top() == 5);
}

// Тест за достъпване на елемент от празен стек
TEST_CASE("testing the removing of a Node in an empty stack")
{
    // Създаваме празен стек
    Stack<int> stack;
    
    // Проверяваме, че top и last за празен стек хвърлят грешка 
    // https://github.com/doctest/doctest/blob/master/doc/markdown/assertions.md#exceptions
    CHECK_THROWS_AS(stack.top(), std::exception);
}

// Тест за копиране на стек
TEST_CASE("testing the copying of Stack")
{
    // Създаваме стек и му добавяме няколко елемента
    Stack<int> stack;

    stack.push(5);
    stack.push(6);
    stack.push(2);
    stack.push(8);

    // Създаваме копие на стека
    Stack<int> copystack(stack);

    // Правим промяна по копието
    copystack.push(10);

    // Проверяваме, че само копието се е променило
    CHECK(stack.top() == 8);
    CHECK(copystack.top() == 10);
}

// Тест за вземане на размера на стек
TEST_CASE("testing the copying of Stack")
{
    // Създаваме стек и му добавяме няколко елемента
    Stack<int> stack;

    CHECK(stack.empty() == true);
    CHECK(stack.size() == 0);

    stack.push(5);
    stack.push(6);
    stack.push(2);
    stack.push(8);

    CHECK(stack.size() == 4);
    CHECK(stack.empty() == false);
}