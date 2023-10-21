#include "dll.h"
#include <string>

class BrowserPage
{
private:
    std::string url;
    std::string content;

public:
    BrowserPage(std::string, std::string);
    std::string getUrl();
    std::string getContent();
    bool operator==(const BrowserPage&) const;
};

class BrowserHistory
{
private:
    DoublyLinkedList<BrowserPage> allPages;
    DoublyLinkedListIterator<BrowserPage, BrowserPage &> currentPage;

public:
    void back();
    void forward();
    BrowserPage get();
    void close();
    void visit(const BrowserPage &page);
};