#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

#include "hashtable.h"

TEST_CASE("testing the size of an empty HashTable")
{
    HashTable<int, int> ht(100);

    CHECK(ht.size() == 0);
    CHECK(ht.empty());
}

TEST_CASE("testing the check for inclusion of a key in a HashTable")
{
    HashTable<int, int> ht(100);

    CHECK(!ht.containsKey(5));

    ht.put(5, 3);

    CHECK(ht.containsKey(5));
}

TEST_CASE("testing getting a value for a given key in a HashTable")
{
    HashTable<int, int> ht(100);

    ht.put(5, 3);
    ht.put(6, 12);

    CHECK(ht.get(5) == 3);
    CHECK(ht.get(6) == 12);
}

TEST_CASE("testing getting a value for a missing key in a HashTable")
{
    HashTable<int, int> ht(100);

    ht.put(5, 3);

    CHECK_THROWS_AS(ht.get(6), std::exception);
}

TEST_CASE("testing removing a key from a HashTable")
{
    HashTable<int, int> ht(100);

    ht.put(5, 3);
    ht.put(6, 12);

    CHECK(ht.get(5) == 3);
    CHECK(ht.containsKey(5));
    CHECK(ht.size() == 2);

    ht.remove(5);
    CHECK(!ht.containsKey(5));
    CHECK_THROWS_AS(ht.get(5), std::exception);
    CHECK(ht.size() == 1);
}

TEST_CASE("testing the size of a non-empty HashTable")
{
    HashTable<int, int> ht(100);

    ht.put(5, 3);
    ht.put(6, 12);

    CHECK(ht.size() == 2);
    CHECK(!ht.empty());
}

TEST_CASE("testing getting all keys of a HashTable")
{
    HashTable<int, int> ht(100);

    ht.put(5, 3);
    ht.put(6, 12);

    std::vector<int> expected({5, 6});

    CHECK(ht.keys() == expected);
}

TEST_CASE("testing getting all values of a HashTable")
{
    HashTable<int, int> ht(100);

    ht.put(5, 3);
    ht.put(6, 12);

    std::vector<int> expected({3, 12});

    CHECK(ht.values() == expected);
}
