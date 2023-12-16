#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

#include "bstree.h"

TEST_CASE("testing the size of an empty BSTree")
{
    BSTree<int> tree;

    CHECK(tree.size() == 0);
}

TEST_CASE("testing member of an empty BSTree")
{
    BSTree<int> tree;

    CHECK(tree.member(5) == false);
}

TEST_CASE("testing deleting from an empty BSTree")
{
    BSTree<int> tree;

    CHECK(tree.size() == 0);
    tree.remove(5);
    CHECK(tree.size() == 0);
}

TEST_CASE("testing min/max on an empty BSTree")
{
    BSTree<int> tree;

    CHECK_THROWS_AS(tree.min(), std::exception);
    CHECK_THROWS_AS(tree.max(), std::exception);
}

TEST_CASE("testing inserting in a BSTree")
{
    BSTree<int> tree;

    CHECK(tree.member(5) == false);

    tree.add(5);
    CHECK(tree.member(5) == true);
    CHECK(tree.size() == 1);

    tree.add(6);
    CHECK(tree.member(5) == true);
    CHECK(tree.member(6) == true);
    CHECK(tree.size() == 2);
}

TEST_CASE("testing removing from a BSTree")
{
    BSTree<int> tree;

    tree.add(5);
    tree.add(6);
    CHECK(tree.member(5) == true);
    CHECK(tree.member(6) == true);
    CHECK(tree.size() == 2);

    tree.remove(6);
    CHECK(tree.member(5) == true);
    CHECK(tree.member(6) == false);
    CHECK(tree.size() == 1);

    tree.remove(5);
    CHECK(tree.member(5) == false);
    CHECK(tree.member(6) == false);
    CHECK(tree.size() == 0);
}

TEST_CASE("testing range in a BSTree")
{
    BSTree<int> tree;

    tree.add(5);
    tree.add(6);
    tree.add(10);
    tree.add(2);
    tree.add(18);
    tree.add(-5);
    tree.add(13);
    tree.add(7);

    std::vector<int> expected({6, 7, 10, 13});
    CHECK(tree.range(5, 15) == expected);
    CHECK(tree.range(20, 25) == std::vector<int>());
}

TEST_CASE("testing copying of BSTree")
{
    BSTree<int> tree;

    tree.add(5);
    tree.add(6);
    tree.add(10);

    BSTree<int> copyTree = tree;
    CHECK(copyTree.member(5) == true);
    CHECK(copyTree.member(6) == true);
    CHECK(copyTree.member(10) == true);
    CHECK(copyTree.size() == 3);

    tree.remove(5);
    CHECK(copyTree.member(5) == true);
    CHECK(tree.member(5) == false);
    CHECK(copyTree.size() == 3);
    CHECK(tree.size() == 2);

    copyTree.remove(6);
    CHECK(copyTree.member(6) == false);
    CHECK(tree.member(6) == true);
    CHECK(copyTree.size() == 2);
    CHECK(tree.size() == 2);
}

TEST_CASE("testing iteration of a BSTree")
{
    BSTree<int> tree;

    tree.add(5);
    tree.add(6);
    tree.add(10);
    tree.add(2);
    tree.add(18);
    tree.add(-5);
    tree.add(13);
    tree.add(7);

    std::vector<int> expected({-5, 2, 5, 6, 7, 10, 13, 18});
    std::vector<int> result;

    for (int i : tree)
        result.push_back(i);

    CHECK(result == expected);
}

TEST_CASE("testing iteration of an empty BSTree")
{
    BSTree<int> tree;

    CHECK((tree.begin() != tree.end()) == false);
}

TEST_CASE("testing min/max of a BSTree")
{
    BSTree<int> tree;

    tree.add(5);
    tree.add(6);
    tree.add(10);
    tree.add(2);
    tree.add(18);
    tree.add(-5);
    tree.add(13);
    tree.add(7);

    CHECK(tree.min() == -5);
    CHECK(tree.max() == 18);
}