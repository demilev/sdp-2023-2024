#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task03.h"

// Базов тест
TEST_CASE("basic example")
{
    std::list<int> first, second;
    first.push_front(3);
    first.push_front(2);
    first.push_front(4);
    first.push_front(1);

    second.push_front(7);
    second.push_front(8);
    second.push_front(3);

    std::list<int> result = sum(first, second);

    std::list<int> expected = {1, 8, 1, 0};

    CHECK(result == expected);
}