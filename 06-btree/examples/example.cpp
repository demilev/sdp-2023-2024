#include <iostream>

void f1(int a)
{
    a = 5;
}

void f2(int &a)
{
    a = 5;
}

void g1(int *p)
{
    p = new int(10);
}

void g2(int *&p)
{
    p = new int(10);
}

int main()
{
    int x = 3;

    f1(x);
    std::cout << "x after f1: " << x << std::endl;

    f2(x);
    std::cout << "x after f2: " << x << std::endl;

    int *y = new int(3);

    g1(y);
    std::cout << "y after g1: " << *y << std::endl;

    g2(y);
    std::cout << "y after g2: " << *y << std::endl;

    return 0;
}