#include <iostream>

#include "hashtable.h"

int main()
{
    HashTable<std::string, std::string> ht(100);

    ht.put("abc", "cdf");

    std::cout << ht.get("abc") << std::endl;

    std::cout << ht.containsKey("abc") << std::endl;
    ht.remove("abc");
    std::cout << ht.containsKey("abc") << std::endl;
    std::cout << ht.containsKey("sdafasdf") << std::endl;

    std::cout << ht.size() << std::endl;

    return 0;
}