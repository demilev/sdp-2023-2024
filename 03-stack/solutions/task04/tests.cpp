#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task04.cpp"

// Тест за обръщане на стек
TEST_CASE("testing the reverse of Stack")
{
    Stack<int> stack;

    stack.push(5);
    stack.push(6);
    stack.push(2);
    stack.push(8);

    reverse(stack);

    CHECK(stack.top() == 5);
    stack.pop();
    CHECK(stack.top() == 6);
    stack.pop();
    CHECK(stack.top() == 2);
    stack.pop();
    CHECK(stack.top() == 8);
}