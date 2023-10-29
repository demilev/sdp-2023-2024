#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

#include "dll.h"
#include <vector>

TEST_CASE("testing the insertion of a Node")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    CHECK(list.head() == 5);

    list.pushFront(6);
    CHECK(list.head() == 6);
}

TEST_CASE("testing the removing of a Node")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);

    list.popFront();
    CHECK(list.head() == 5);
}

TEST_CASE("testing the removing of a Node in an empty list")
{
    DoublyLinkedList<int> list;
    list.popFront();

    list.pushFront(5);
    CHECK(list.head() == 5);
}

TEST_CASE("testing accessing a Node in an empty list")
{
    DoublyLinkedList<int> list;

    CHECK_THROWS_AS(list.head(), std::exception);
    CHECK_THROWS_AS(list.last(), std::exception);
}

TEST_CASE("testing the copying of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    DoublyLinkedList<int> copyList(list);

    copyList.pushFront(10);

    CHECK(list.head() == 8);
    CHECK(copyList.head() == 10);
}

TEST_CASE("testing appending to a list")
{
    DoublyLinkedList<int> list;

    list.pushBack(5);
    CHECK(list.last() == 5);
    CHECK(list.head() == 5);

    list.pushBack(6);
    CHECK(list.last() == 6);
    CHECK(list.head() == 5);
}

TEST_CASE("testing removing the last element of a list")
{
    DoublyLinkedList<int> list;

    list.pushBack(5);
    list.pushBack(6);
    list.pushBack(3);
    CHECK(list.last() == 3);

    list.popBack();
    CHECK(list.last() == 6);
}

TEST_CASE("testing the iteration of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    std::vector<int> expected = {8, 2, 6, 5};

    int i = 0;
    for (int element : list)
    {
        CHECK(element == expected[i++]);
    }
}

TEST_CASE("testing modification via iteration of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    for (int &element : list)
    {
        element++;
    }

    std::vector<int> expected = {9, 3, 7, 6};

    int i = 0;
    for (int element : list)
    {
        CHECK(element == expected[i++]);
    }
}

TEST_CASE("testing accessing an invalid element of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    CHECK_THROWS_AS(*list.end(), std::exception);
}

TEST_CASE("testing going to an invalid element of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    CHECK_THROWS_AS(++list.end(), std::exception);
}

TEST_CASE("testing removing at a position of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    list.deleteElement(++list.begin());

    std::vector<int> expected = {8, 6, 5};

    int i = 0;
    for (int element : list)
    {
        CHECK(element == expected[i++]);
    }
}

TEST_CASE("testing removing at the first position of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    list.deleteElement(list.begin());

    std::vector<int> expected = {2, 6, 5};

    int i = 0;
    for (int element : list)
    {
        CHECK(element == expected[i++]);
    }
}

TEST_CASE("testing removing at the last position of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    list.deleteElement(--list.end());

    std::vector<int> expected = {8, 2, 6};

    int i = 0;
    for (int element : list)
    {
        CHECK(element == expected[i++]);
    }
}

TEST_CASE("testing removing at invalid position of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    CHECK_THROWS_AS(list.deleteElement(list.end()), std::exception);
}

TEST_CASE("testing inserting at a position of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    list.insertAfter(list.begin(), 3);
    list.insertBefore(--list.end(), 4);

    std::vector<int> expected = {8, 3, 2, 6, 4, 5};

    int i = 0;
    for (int element : list)
    {
        CHECK(element == expected[i++]);
    }
}

TEST_CASE("testing inserting at the first position of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    list.insertBefore(list.begin(), 1);

    std::vector<int> expected = {1, 8, 2, 6, 5};

    int i = 0;
    for (int element : list)
    {
        CHECK(element == expected[i++]);
    }
}

TEST_CASE("testing inserting at the last position of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    list.insertAfter(--list.end(), 10);

    std::vector<int> expected = {8, 2, 6, 5, 10};

    int i = 0;
    for (int element : list)
    {
        CHECK(element == expected[i++]);
    }
}

TEST_CASE("testing removing at invalid position of DoublyLinkedList")
{
    DoublyLinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    CHECK_THROWS_AS(list.insertAfter(list.end(), 12), std::exception);
}