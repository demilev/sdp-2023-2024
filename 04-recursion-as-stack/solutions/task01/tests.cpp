#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task01.h"

// Базов тест
TEST_CASE("basic example")
{
    bool labyrinth[100][100] = {{1, 0, 0, 0},
                                {1, 1, 1, 1},
                                {0, 1, 0, 1},
                                {0, 1, 0, 1}};
    CHECK(pathExistsStack(labyrinth, 4, 4));
    CHECK(pathExists(labyrinth, 4, 4));
}