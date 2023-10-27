#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../lib/doctest.h"

#include "text_editor.h"

std::function<std::string(std::string)> appendOperation(std::string toAppend) {
    return [toAppend](std::string s) -> std::string { return s + toAppend; };
}

// Тест за създаване на текстов редактор
TEST_CASE("testing the creation of TextEditor")
{
    TextEditor te;

    CHECK(te.get() == "");
}

// Тест за промяна на съдържанието на текстов редактор
TEST_CASE("testing the edit of TextEditor")
{
    TextEditor te;

    te.edit([](std::string s) -> std::string { return s + "abc";});

    CHECK(te.get() == "abc");
}

// Тест за връшане на съдържанието на текстов редактор
TEST_CASE("testing the edit of TextEditor")
{
    TextEditor te;

    te.edit(appendOperation("abc"));
    CHECK(te.get() == "abc");

    te.edit(appendOperation("efg"));
    CHECK(te.get() == "abcefg");

    te.edit(appendOperation("hij"));
    CHECK(te.get() == "abcefghij");

    te.undo();
    CHECK(te.get() == "abcefg");

    te.undo();
    CHECK(te.get() == "abc");

    te.undo();
    CHECK(te.get() == "");

    te.undo();
    CHECK(te.get() == "");
}