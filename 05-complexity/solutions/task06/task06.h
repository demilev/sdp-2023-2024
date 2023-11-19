#include <list>
#include <iostream>

// Ще използваме функцията от миналата задача като помощна за функция, която сортира свързан списък
// Разликата е, че този път фунцкията ще приема итератори за начало и край на частта от списъка, която трябва да бъде разделена
// и ще връша позицията, след която всички елементи са по-големи от number, а преди която всички са по-малки от number
std::list<int>::iterator partition(std::list<int>::iterator lowerPosition, std::list<int>::iterator higherPosition, int number)
{
    while (lowerPosition != higherPosition)
    {
        if (*lowerPosition > number && *higherPosition <= number)
        {
            std::swap(*lowerPosition, *higherPosition);
        }
        else
        {
            while (*lowerPosition <= number)
            {
                lowerPosition++;
                if (lowerPosition == higherPosition)
                    return lowerPosition;
            }
            while (*higherPosition > number)
            {
                higherPosition--;
                if (lowerPosition == higherPosition)
                    return lowerPosition;
            }
        }
    }
    return lowerPosition;
}

// Сортиращата ти функция в такъв случай е следната
void sort(std::list<int>::iterator begin, std::list<int>::iterator end)
{
    // Списъкът с <= 1 елементи вече е сортиран
    if (begin == end)
        return;

    // Разбиваме списъка по последния му елемент
    std::list<int>::iterator position = partition(begin, end, *end);
    // Сортираме първата част
    sort(begin, --position);
    // Сортираме втората част
    sort(++position, end);
}

void sort(std::list<int> &l)
{
    sort(l.begin(), --l.end());
}

void electionResults(std::list<int> votes)
{
    // О(nlgn)
    sort(votes);

    // Веднъж сортиран списък с гласове, трябва просто да бъде обходен и да преброим гласовете за всяка партия.
    // Гласовете за дадена партия ще са съседни елементи, т.е. едно обхождане на списъка ни стига.
    int current = votes.front();
    int currentCount = 1;
    votes.pop_front();
    for (int vote : votes)
    {
        if (vote == current)
        {
            currentCount++;
        }
        else
        {
            std::cout << currentCount << " vote" << (currentCount > 1 ? "s" : "") << " for " << current << std::endl;
            current = vote;
            currentCount = 1;
        }
    }

    std::cout << currentCount << " vote" << (currentCount > 1 ? "s" : "") << " for " << current << std::endl;
}
