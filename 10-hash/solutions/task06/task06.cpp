#include <iostream>
#include <vector>

#include "../hashtable.h"

// O(n) - сложност по време, O(n) - сложност по памет
void electionResults(std::list<int> votes)
{
    // Създаваме хеш таблица. Ключовете ще са партиите, а стойностите ще са гласовете им
    HashTable<int, int> ht(100);

    // обхождаме гласовете - O(n)
    for (int vote : votes)
    {
        // Ако досега не сме отчели вот за дадена партия, я добаваме в таблицата - О(1)
        if (!ht.containsKey(vote))
        {
            ht.put(vote, 0);
        }

        // Увеличаваме гласовете на текущата партия с 1 - О(1)
        int currentVotes = ht.get(vote);
        ht.put(vote, currentVotes + 1);
    }

    // Накрая отпечатваме резултатие на екрана
    std::vector<int> parties = ht.keys();

    for (int party : parties)
    {
        std::cout << "Party " << party << " - Votes " << ht.get(party) << std::endl;
    }
}

int maxSubArrayLen(std::vector<int> numbers, int k)
{
    int maxLen = 0;
    int cumulativeSum = 0;
    // Поддържаме хеш таблица, която съдържа наредени двойки <s, i>, където s e сумата на първите i елемента във вектора
    HashTable<int, int> ht(100);

    for (int i = 0; i < numbers.size(); ++i)
    {
        cumulativeSum += numbers[i];

        if (cumulativeSum == k)
        {
            maxLen = i + 1;
        }

        // Ако има индекс j, който е равен на сумата на елементите до текущия индекс i - k, това означава, че подредицата от j до i има сума k
        if (ht.containsKey(cumulativeSum - k))
        {
            // обновяваме стойността на maxLen
            maxLen = std::max(maxLen, i - ht.get(cumulativeSum - k));
        }

        // добавяме текущата кумулативна сума
        ht.put(cumulativeSum, i);
    }

    return maxLen;
}

int main()
{
    electionResults({1, 83, 32, 28, 32, 1, 32});

    std::cout << "The max length of subaray with sum 10 is: " << maxSubArrayLen({1, 2, 4, 3, 1, 1, 1}, 10) << std::endl;

    return 0;
}