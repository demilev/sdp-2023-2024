#include <iostream>
#include <stack>

void f(long n)
{
    if (n <= 0)
    {
        std::cout << n << std::endl;
        return;
    }

    f(n - 1);

    std::cout << n << std::endl;
}

struct Operation
{
    long number;
    char type; // 'r' - рекурсивно извикване, 'p' - отпечатай числото
};

void fStack(long n)
{
    std::stack<Operation> numbers;
    numbers.push({n, 'p'});
    numbers.push({n, 'r'});

    while (!numbers.empty())
    {
        Operation current = numbers.top();
        numbers.pop();
        if (current.number >= 0)
        {

            if (current.type == 'p')
            {
                std::cout << current.number << std::endl;
            }
            if (current.type == 'r')
            {
                numbers.push({current.number - 1, 'p'});
                numbers.push({current.number - 1, 'r'});
            }
        }
    }
}

int main()
{
    fStack(10);
    return 0;
}