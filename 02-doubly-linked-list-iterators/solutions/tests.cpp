#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "browser_history.h"

// Тест за посещаване на първа страница
TEST_CASE("testing opening a new page")
{
    BrowserPage page("test.com", "Test Content");
    BrowserHistory history;
    history.visit(page);

    CHECK(history.get() == page);
}

// Тест за обхождане на страници
TEST_CASE("testing browsing through pages")
{
    BrowserPage page1("test1.com", "Test Content 1");
    BrowserPage page2("test2.com", "Test Content 2");
    BrowserPage page3("test3.com", "Test Content 3");
    BrowserHistory history;
    history.visit(page1);
    history.visit(page2);
    history.visit(page3);

    CHECK(history.get() == page3);
    history.back();
    CHECK(history.get() == page2);
    history.back();
    CHECK(history.get() == page1);
    history.forward();
    CHECK(history.get() == page2);
    history.forward();
    CHECK(history.get() == page3);
}

// Тест за затваряне на страница
TEST_CASE("testing closing a pages")
{
    BrowserPage page1("test1.com", "Test Content 1");
    BrowserPage page2("test2.com", "Test Content 2");
    BrowserPage page3("test3.com", "Test Content 3");
    BrowserHistory history;
    history.visit(page1);
    history.visit(page2);
    history.visit(page3);

    history.back();
    CHECK(history.get() == page2);
    history.close();
    CHECK(history.get() == page1);
    history.forward();
    CHECK(history.get() == page3);
}

// Тест за затваряне на първа страница
TEST_CASE("testing closing a pages")
{
    BrowserPage page1("test1.com", "Test Content 1");
    BrowserPage page2("test2.com", "Test Content 2");
    BrowserPage page3("test3.com", "Test Content 3");
    BrowserHistory history;
    history.visit(page1);
    history.visit(page2);
    history.visit(page3);

    history.back();
    history.back();
    CHECK(history.get() == page1);
    history.close();
    CHECK(history.get() == page2);
    history.forward();
    CHECK(history.get() == page3);
}

// Тест за отваряне на нова страница назад в историята
TEST_CASE("testing closing a pages")
{
    BrowserPage page1("test1.com", "Test Content 1");
    BrowserPage page2("test2.com", "Test Content 2");
    BrowserPage page3("test3.com", "Test Content 3");
    BrowserPage page4("test4.com", "Test Content 4");
    BrowserPage page5("test5.com", "Test Content 5");
    BrowserHistory history;
    history.visit(page1);
    history.visit(page2);
    history.visit(page3);
    history.visit(page4);

    history.back();
    history.back();
    CHECK(history.get() == page2);
    history.visit(page5);
    CHECK(history.get() == page5);
    history.forward();
    CHECK(history.get() == page5);
    history.back();
    CHECK(history.get() == page2);
    history.back();
    CHECK(history.get() == page1);
}
