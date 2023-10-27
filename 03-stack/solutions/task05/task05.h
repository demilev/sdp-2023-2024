#include "../stack/stack.h"
#include <string>

// Функция, която проверява дали символ е отваряща скоба
bool isOpenningParenthesis(char c)
{
    return c == '(' || c == '{' || c == '[';
}

// Функция, която проверява дали символ е затваряща скоба
bool isClosingParenthesis(char c)
{
    return c == ')' || c == '}' || c == ']';
}

// Функция, която проверява дали два символа съвпадат като отваряща и затваряща скоба
bool areMatching(char opening, char closing)
{

    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

bool validateParentheses(std::string text)
{
    // Ще държим стек с отварящите скоби
    Stack<char> openingParentheses;

    // Обхождаме символния низ
    for (char c : text)
    {
        // Ако е отваряща скоба, го слагаме в стека
        if (isOpenningParenthesis(c))
        {
            openingParentheses.push(c);
        }
        // Ако е затваряща
        else if (isClosingParenthesis(c))
        {
            // Проверяваме дали на върха на стека има отваряща от същия тип
            if (!openingParentheses.empty() && areMatching(openingParentheses.top(), c))
            {
                // Ако има, я махаме
                openingParentheses.pop();
            }
            else
            {
                // Ако няма, изразът не е добре скобуван
                return false;
            }
        }
    }

    // Ако не са останали отварящи скоби, значи изразът е добре скобуван
    return openingParentheses.empty();
}