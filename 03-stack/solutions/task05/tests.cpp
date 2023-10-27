#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "task05.h"

// Тест за валидация на добре скобуван израз
TEST_CASE("testing the reverse of Stack")
{
    
    CHECK(validateParentheses("(([{}()]))") == true);
    CHECK(validateParentheses("(({})]") == false);
    CHECK(validateParentheses("(({)})") == false);
    CHECK(validateParentheses("(({}))[()") == false);
}