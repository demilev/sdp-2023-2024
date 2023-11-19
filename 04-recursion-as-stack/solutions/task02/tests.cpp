#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task02.h"

// Базов тест
TEST_CASE("basic example")
{
    std::vector<std::string> operations = {"5", "2", "C", "D", "+"};

    CHECK(evaluate(operations) == 30);
}