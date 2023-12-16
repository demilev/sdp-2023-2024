#include "bstree.h"
#include "treeset.h"
#include <iostream>

int main()
{
    Node<int> *root = new Node<int>(33);
    Node<int> *n1 = new Node<int>(12);
    Node<int> *n2 = new Node<int>(42);

    Node<int> *n3 = new Node<int>(8);
    Node<int> *n4 = new Node<int>(15);

    Node<int> *n5 = new Node<int>(40);
    Node<int> *n6 = new Node<int>(55);

    Node<int> *n7 = new Node<int>(4);

    Node<int> *n8 = new Node<int>(38);
    Node<int> *n9 = new Node<int>(41);

    Node<int> *n10 = new Node<int>(50);
    Node<int> *n11 = new Node<int>(62);

    Node<int> *n12 = new Node<int>(2);

    root->left = n1;
    root->right = n2;

    n1->left = n3;
    n1->right = n4;

    n2->left = n5;
    n2->right = n6;

    n3->left = n7;

    n5->left = n8;
    n5->right = n9;

    n6->left = n10;
    n6->right = n11;

    n7->left = n12;

    BSTree<int> tree(root);

    tree.printDot();

    std::cout << "The tree is BST: " << std::boolalpha << tree.isBST() << std::endl;

    std::cout << "Max element in the tree: " << tree.max() << std::endl;
    std::cout << "Min element in the tree: " << tree.min() << std::endl;

    std::cout << "8 is in the tree: " << std::boolalpha << tree.member(8) << std::endl;
    std::cout << "16 is in the tree: " << std::boolalpha << tree.member(16) << std::endl;

    tree.add(13);
    tree.printDot();

    tree.remove(8);
    tree.printDot();

    std::vector<int> range = tree.range(14, 48);
    std::cout << "The numbers between 14 and 48 in the tree are: " << std::endl;
    for (int i : range)
        std::cout << i << " ";
    std::cout << std::endl;

    std::vector<int> numbers({0, 3, 0, 15, 4, 2, 3, 0, 1, 1, 8});
    std::cout << "Number of unique elements: " << countUniques(numbers) << std::endl;
    std::cout << "Numbers with sum 19 exist: " << std::boolalpha << twoSum(numbers, 19) << std::endl;
    std::cout << "Numbers with sum 13 exist: " << std::boolalpha << twoSum(numbers, 13) << std::endl;
    
    return 0;
}