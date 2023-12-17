#include <functional>
#include <iostream>
#include <string>

int main()
{
    std::hash<std::string> hashFunction;

    std::cout << hashFunction("Ivan Ivanov") << std::endl;
    std::cout << hashFunction("Boyan Petkov") << std::endl;
    std::cout << hashFunction("Ivan Ivanof") << std::endl;
    std::cout << hashFunction("Ivan Ivanov") << std::endl;

    return 0;
}