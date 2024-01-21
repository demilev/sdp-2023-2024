#include "hash.h"

#include <iostream>

int main()
{
    std::vector<int> firstList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> secondList = {0, 2, 4, 5, 8, 12};
    std::vector<int> result = findCommonElements(firstList, secondList);

    std::cout << "Common elements: ";
    for (int element : result)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "Two numbers with sum 10 in secondList exist: " << std::boolalpha << twoSum(secondList, 10) << std::endl;
    std::cout << "Two numbers with sum 11 in secondList exist: " << std::boolalpha << twoSum(secondList, 11) << std::endl;
    return 0;
}