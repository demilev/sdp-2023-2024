#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task05.h"

// Базов тест
TEST_CASE("basic example")
{
    std::vector<int> tasks = {0, 1, 2, 3, 4};
    std::vector<std::vector<int>> dependencies = {{3, 4}, {2}, {}, {4}, {}};

    std::list<int> order = toposort(tasks, dependencies);

    std::list<int> expected = {1, 2, 0, 3, 4};

    CHECK(order == expected);
}