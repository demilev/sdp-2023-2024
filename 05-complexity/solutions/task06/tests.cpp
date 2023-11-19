#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task06.h"

// Базов тест
TEST_CASE("basic example")
{
    std::list<int> l;
    l.push_back(5);
    l.push_back(4);
    l.push_back(2);
    l.push_back(-2);

    sort(l);

    std::list<int> expected = {-2, 2, 4, 5};

    CHECK(l == expected);
}