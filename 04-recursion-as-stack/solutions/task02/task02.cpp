#include <string>
#include <vector>
#include <stack>
#include <iostream>

int evaluate(std::vector<std::string> operations)
{
    // Ще поддържаме стек с числата и резултатите от изпълнение на операциите
    std::stack<int> numbers;
    // Обхождаме входните данни операция по операция
    for (std::string operation : operations)
    {
        // Операцията за премахване на последния резултата се превежда до pop от стека
        if (operation == "C")
        {
            numbers.pop();
        }
        // Операция за удвояване на последния резултата се превежда до слагане на нов елемент на върха на стека
        else if (operation == "D")
        {
            numbers.push(2 * numbers.top());
        }
        // Операция за сумиране изисква да вземем последните два елемента от стека. Не забравяме и да ги върнем обратно там.
        else if (operation == "+")
        {
            int op1 = numbers.top();
            numbers.pop();
            int op2 = numbers.top();

            numbers.push(op1);
            numbers.push(op1 + op2);
        }
        else
        {
            // Ако нямаме операция, значи имаме число, което слагаме на стека
            numbers.push(std::stoi(operation));
        }
    }

    // Накрая сумираме резултата
    int result = 0;
    while (!numbers.empty())
    {
        int n = numbers.top();
        numbers.pop();
        result += n;
    }

    return result;
}

int main()
{
    std::vector<std::string> operations = {"5", "2", "C", "D", "+"};

    std::cout << evaluate(operations) << std::endl;

    return 0;
}