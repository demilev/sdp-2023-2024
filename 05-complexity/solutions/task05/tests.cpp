#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task05.h"

// Базов тест
TEST_CASE("basic example")
{
    std::list<int> l;
    l.push_back(1);
    l.push_back(4);
    l.push_back(2);
    l.push_back(10);

    partition(l, 3);

    std::list<int> expected = {1, 2, 4, 10};

    CHECK(l == expected);
}