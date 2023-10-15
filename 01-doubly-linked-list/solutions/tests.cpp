#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "dll.h"

// Тест за създаване на Node
TEST_CASE("testing the creation of a Node")
{
    // Създаваме Node с конструктора му с един параметър
    Node<int> node(5);

    // Проверяваме, че данните, които държи, са тези, които сме подали в конструктора 
    CHECK(node.data == 5);
    // Проверяваме, че няма наследник
    CHECK(node.next == nullptr);
    // Проверяваме, че няма предшественик
    CHECK(node.previous == nullptr);
}

// Тест за добавяне на елемент в началото на списък
TEST_CASE("testing the insertion of a Node")
{
    // Създаваме празен списък
    DoublyLinkedList<int> list;

    // Добавяме му един елемент в началото
    list.pushFront(5);
    // Проверяваме, че в началото стои този елемент
    CHECK(list.head() == 5);

    // Добавяме нов елемент в началото
    list.pushFront(6);
    // Проверяваме, че в началото стои този елемент
    CHECK(list.head() == 6);
}

// Тест за премахване на елемент от началото на списък
TEST_CASE("testing the removing of a Node")
{
    // Създаваме празен списък
    DoublyLinkedList<int> list;

    // Добавяме му два елемента в началото
    list.pushFront(5);
    list.pushFront(6);

    // Премахваме единия
    list.popFront();
    // Проверяваме, че другият е в началото на списъка
    CHECK(list.head() == 5);
}

// Тест за опит за премахване на елемент от празен списък
TEST_CASE("testing the removing of a Node in an empty list")
{
    // Създаваме празен списък
    DoublyLinkedList<int> list;
    // Опитваме се да премахнем елемент - тази операция не трябва да прави нищо в такъв случай
    list.popFront();

    // Добавяме един елемент и проверяваме, че е на първа позиция
    list.pushFront(5);
    CHECK(list.head() == 5);
}

// Тест за достъпване на елемент от празен списък
TEST_CASE("testing the removing of a Node in an empty list")
{
    // Създаваме празен списък
    DoublyLinkedList<int> list;
    
    CHECK_THROWS_AS(list.head(), std::exception);
    CHECK_THROWS_AS(list.last(), std::exception);
}

// Тест за копиране на списък
TEST_CASE("testing the copying of DoublyLinkedList")
{
    // Създаваме списък и му добавяме няколко елемента
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    // Създаваме копие на списъка
    DoublyLinkedList<int> copyList(list);

    // Правим промяна по копието
    copyList.pushFront(10);

    // Проверяваме, че само копието се е променило
    CHECK(list.head() == 8);
    CHECK(copyList.head() == 10);
}

// Тест за добавяне на елемент в края на списък
TEST_CASE("testing appending to a list")
{   
    // Създаваме празен списък
    DoublyLinkedList<int> list;

    // Добавяме му елемент в края
    list.pushBack(5);
    // Проверяваме, че последният и първият елемент съвпадат
    CHECK(list.last() == 5);
    CHECK(list.head() == 5);

    // Добавяме нов елемент в края
    list.pushBack(6);
    // Проверяваме, че последният елемент е променен, а първият не
    CHECK(list.last() == 6);
    CHECK(list.head() == 5);
}

// Тест за премахване на елемент от края на списък
TEST_CASE("testing removing the last element of a list")
{
    // Създаваме списък и му добавяме няколко елемента
    DoublyLinkedList<int> list;

    list.pushBack(5);
    list.pushBack(6);
    list.pushBack(3);
    CHECK(list.last() == 3);

    // Махаме последния и виждаме, че новият последен е променен
    list.popBack();
    CHECK(list.last() == 6);
}

// Тест за обръщане на свързан списък
TEST_CASE("testing reversing of a LinkedList")
{   
    // Създаваме списък и му добавяме няколко елемента
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    // обръщаме го
    list.reverse();

    // Проверяваме, че наредбата е обърната
    CHECK(list.head() == 5);
    CHECK(list.last() == 8);
}

// Тест за премахване на повтарящи се елементи в свързан списък
TEST_CASE("testing removing duplicates from a DoublyLinkedList")
{   
    // Създаваме списък и му добавяме няколко елемента
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(6);
    list.pushFront(5);
    list.pushFront(3);

    // обръщаме го
    list.removeDuplicates();

    // Проверяваме, че наредбата е обърната
    CHECK(list.head() == 3);
    CHECK(list.last() == 6);
}
