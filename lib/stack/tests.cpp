#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

#include "stack.h"

TEST_CASE("testing the insertion of a Node")
{
    Stack<int> stack;

    stack.push(5);
    CHECK(stack.top() == 5);

    stack.push(6);
    CHECK(stack.top() == 6);
}

TEST_CASE("testing the removing of a Node")
{
    Stack<int> stack;

    stack.push(5);
    stack.push(6);

    stack.pop();
    CHECK(stack.top() == 5);
}

TEST_CASE("testing the removing of a Node in an empty stack")
{
    Stack<int> stack;
    stack.pop();

    stack.push(5);
    CHECK(stack.top() == 5);
}

TEST_CASE("testing the removing of a Node in an empty stack")
{
    Stack<int> stack;

    CHECK_THROWS_AS(stack.top(), std::exception);
}

TEST_CASE("testing the copying of Stack")
{
    Stack<int> stack;

    stack.push(5);
    stack.push(6);
    stack.push(2);
    stack.push(8);

    Stack<int> copystack(stack);

    copystack.push(10);

    CHECK(stack.top() == 8);
    CHECK(copystack.top() == 10);
}

TEST_CASE("testing the copying of Stack")
{
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