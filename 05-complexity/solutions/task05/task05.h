#include <list>
#include <iostream>

// Сложност по време О(n)
void partition(std::list<int> &l, int number)
{
    // Ще пазим две позиции в списъка:
    // lowerPosition - позицията на кутийката, в която има елемент, който има по-голяма стойност от числото, по което делим
    // higherPosition - позицията на кутийката, в която има елемент, който има по-малка стойност от числото, по което делим
    std::list<int>::iterator lowerPosition = l.begin();
    std::list<int>::iterator higherPosition = --l.end();

    // Докато двата указателя не се срещнат
    while (lowerPosition != higherPosition)
    {
        // Разменяме стойностите им
        if (*lowerPosition > number && *higherPosition <= number)
        {
            std::swap(*lowerPosition, *higherPosition);
        }
        else
        {
            // Или ги преместваме така че да изпълняват условието, което искаме
            while (*lowerPosition <= number)
            {
                lowerPosition++;
                // Правим проверка за разминаване на указателите
                if (lowerPosition == higherPosition)
                    return;
            }
            while (*higherPosition > number)
            {
                higherPosition--;
                if (lowerPosition == higherPosition)
                    return;
            }
        }
    }
}
