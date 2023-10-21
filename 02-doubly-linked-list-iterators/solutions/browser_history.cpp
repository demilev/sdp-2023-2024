#include "browser_history.h"

BrowserPage::BrowserPage(std::string url, std::string content) : url(url), content(content) {}

std::string BrowserPage::getUrl()
{
    return url;
}

std::string BrowserPage::getContent()
{
    return content;
}

bool BrowserPage::operator==(const BrowserPage &other) const
{
    return url == other.url && content == other.content;
}

void BrowserHistory::back()
{
    // Проверка за коректност
    if (allPages.isEmpty())
        return;

    // Само ако вече не сме на първа страница, местим назад
    if (currentPage != allPages.begin())
        --currentPage;
}
void BrowserHistory::forward()
{
    // Проверка за коректност
    if (allPages.isEmpty())
        return;

    // Само ако вече не сме на последна страница, местим напред
    if (currentPage != --allPages.end()) // Извикваме -- на end, защото той сочи след последния елемент
        ++currentPage;
}
BrowserPage BrowserHistory::get()
{
    // Проверка за коректност. Можем да хвърлим exception
    if (allPages.isEmpty())
        return BrowserPage("", "");

    return *currentPage;
}

void BrowserHistory::close()
{
    // Проверка за коректност.
    if (allPages.isEmpty())
        return;

    if (currentPage != allPages.begin())
    {
        // Изтриваме текущия елемент от списъка
        allPages.deleteElement(currentPage);

        // Местим се на предишния
        --currentPage;
    }
    else
    {
        // Специален случай, в който сме на първата страница и я затваряме
        allPages.popFront();
        currentPage = allPages.begin();
    }
}

void BrowserHistory::visit(const BrowserPage &page)
{
    if (!allPages.isEmpty())
    {
        // Махаме всичко, което е след текущата страница
        while (currentPage != --allPages.end())
            allPages.popBack();

        // Добавяме новата страница
        allPages.pushBack(page);
        // Преместваме се към нея
        ++currentPage;
    }
    else
    {
        // Ако списъкът е бил празен досега, просто добавяме новия елемент и насочваме итератора към него
        allPages.pushBack(page);
        currentPage = allPages.begin();
    }
}
