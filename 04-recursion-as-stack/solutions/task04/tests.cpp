#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task04.h"

// Базов тест
TEST_CASE("basic example")
{
    std::vector<int> blocks = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    CHECK(trap(blocks) == 6);
}