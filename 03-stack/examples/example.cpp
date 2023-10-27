void f1()
{
    // ...
    return;
}

void f2()
{
    // ...
    f1();
    return;
}

void f3()
{
    // ...

    f2();
    return;
}

int main()
{
    f3();
    return 0;
}