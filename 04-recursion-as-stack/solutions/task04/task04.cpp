#include <stack>
#include <vector>
#include <iostream>

int trap(std::vector<int> &blocks)
{
    // Ще пазим стек с блокчетата на текущо изградената дупка за вода
    std::stack<int> activeTrap;
    activeTrap.push(blocks[0]);
    // Ще пазим и височината на най-високото блокче в текущата дупка
    int maxHeight = blocks[0];
    // Общия обем вода, който ще върнем като резултата накрая
    int totalVolume = 0;

    // Обхождаме блокчетата
    for (int i = 1; i < blocks.size(); i++)
    {
        // Ако текущото блокче е по-високо от най-високото в текущата дупка, това означава, че тази дупка няма
        // да може да събере повече вода. Изчисляваме колко вода може да събере и добавяме към резултата
        if (blocks[i] > maxHeight)
        {
            while (!activeTrap.empty())
            {
                totalVolume += maxHeight - activeTrap.top();
                activeTrap.pop();
            }
            // blocks[i] е най-високото блокче в новата дупка, която ще изграждаме
            maxHeight = blocks[i];
        }

        // Слагаме блокчето към текущата дупка
        activeTrap.push(blocks[i]);
    }

    // Накрая остава да сметнем колко събира най-дясната дупка(ако събира нещо)
    // Последният й елемент е дясната стена.
    // Забележете, че най-дясната дупка може да съдържа по-малки дупки в себе си и може да завършва с нещо, което няма дясна стена
    // Пример:
    /*
        \
         \  /\  /\
          \/  \/  \
    */
    maxHeight = activeTrap.top();
    while (!activeTrap.empty())
    {
        // Взимаме текущото блокче
        int currentHeight = activeTrap.top();
        activeTrap.pop();
        // Ако е с по-голяма височина, това означава, че досега сме обхобдали по-малка дупка в текущата и е време да преминем към следващата
        // като обновим maxHeight
        if (currentHeight > maxHeight)
        {
            maxHeight = currentHeight;
        }
        // В противен случай добавяме обема вода за текущото блокче
        else
        {
            totalVolume += maxHeight - currentHeight;
        }
    }

    return totalVolume;
}

int main()
{

    std::vector<int> blocks = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    std::cout << trap(blocks);
    return 0;
}