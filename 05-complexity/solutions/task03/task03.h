#include <list>
#include <iostream>

// n - размер на първи списък, m - размер на втори списък
// Сложност по време - О(max(n,m))
// Сложност по памет - О(max(n,m))
std::list<int> sum(std::list<int> first, std::list<int> second)
{
    // Започваме от краищата на двата списъкa и ще обхождаме отзад напред
    std::list<int>::iterator secondCurrent = --second.end();
    std::list<int>::iterator firstCurrent = --first.end();

    std::list<int> result;
    int sum = 0;
    int rem = 0;
    // Докато не обходим някой от списъците
    while (firstCurrent != --first.begin() && secondCurrent != --second.begin())
    {
        sum += *firstCurrent;
        sum += *secondCurrent;
        sum += rem;
        rem = 0;

        // Извършваме операцията събиране и се грижим за пренасянето на остатъка
        if (sum >= 10)
        {
            sum = sum % 10;
            rem += 1;
        }

        result.push_front(sum);
        sum = 0;
        --firstCurrent;
        --secondCurrent;
    }

    // Ако първо сме изчерпали първи списък
    if (firstCurrent == --first.begin())
    {
        // Трябва да дообходим втория
        while (secondCurrent != --second.begin())
        {
            // И да добавим цифрите му към резултата
            result.push_front(*secondCurrent + rem);
            if (rem > 0)
                rem = 0;
            --secondCurrent;
        }
    }
    else
    {
        // Същата логика за първия списък в случай, че втория е бил изчерпан първо
        while (firstCurrent != --first.begin())
        {
            result.push_front(*firstCurrent + rem);
            if (rem > 0)
                rem = 0;
            --firstCurrent;
        }
    }

    return result;
}
