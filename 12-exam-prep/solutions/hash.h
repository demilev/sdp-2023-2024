#include <vector>
#include <unordered_set>

// 1. функция, която намира общите елементи на два вектора
std::vector<int> findCommonElements(std::vector<int> &firstList, std::vector<int> &secondList)
{
    std::vector<int> result;
    std::unordered_set<int> uniques;

    // обхождаме първия списък
    for (int element : firstList)
    {
        // от първия списък запазваме всички уникални елементи в множество
        uniques.insert(element);
    }

    // обхождаме втория списък
    for (int element : secondList)
    {
        // ако елемент от втория списък се съдържа в uniques,
        // то той е общ за двата списъка => го добавяме към резултата
        if (uniques.count(element) > 0)
        {
            result.push_back(element);
        }
    }
    return result;
}

// 2. функция, която проверява дали съществуват два елемента в даден вектор, чиято сума е дадено число
bool twoSum(std::vector<int> &list, int sum)
{
    std::unordered_set<int> visited; // празно множество, в което ще добавяме обходените елементи от списъка

    // обхождаме списъка
    for (int element : list)
    {
        // Проверяваме дали в списъка с посетени елементи има такъв,
        // който заедно с текущия елемент да се допълва до стойността на sum
        // Пример: Ако element = 2 и sum = 10, проверяваме дали във visited има елемент 8 (sum - el = 8)
        if (visited.count(sum - element) > 0)
        {
            return true;
        }
        else
        {
            // добавяме елемента в списъка с обходените
            visited.insert(element);
        }
    }
    return false;
}