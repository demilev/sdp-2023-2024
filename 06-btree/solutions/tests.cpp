#include "btree.h"
#include <iostream>

int main()
{
    Node<int> *root = new Node<int>(4);
    Node<int> *n1 = new Node<int>(33);
    Node<int> *n2 = new Node<int>(8);

    Node<int> *n3 = new Node<int>(-4);
    Node<int> *n4 = new Node<int>(24);

    Node<int> *n5 = new Node<int>(5);

    Node<int> *n6 = new Node<int>(8);
    Node<int> *n7 = new Node<int>(33);

    Node<int> *n8 = new Node<int>(1);
    Node<int> *n9 = new Node<int>(2);

    root->left = n1;
    root->right = n2;

    n1->left = n3;
    n1->right = n4;

    n2->right = n5;

    n4->left = n6;
    n4->right = n7;

    n5->left = n8;
    n5->right = n9;

    BTree<int> tree(root);

    std::cout << "1 is member of the tree: " << tree.member(1) << std::endl;
    std::cout << "55 is member of the tree: " << tree.member(55) << std::endl; 

    std::cout << "The height of the tree is: " << tree.height() << std::endl; 

    std::cout << "The number of leafs of the tree is: " << tree.leafs() << std::endl; 

    tree.print();

    tree.printDot();

    std::cout << "The left most leaf of the tree is: " << tree.leftMostLeaf() << std::endl; 

    std::cout << "The minimum element of the tree is: " << tree.min() << std::endl; 

    std::cout << "The level of 24 in the tree is: " << tree.level(24) << std::endl; 

    std::cout << "The level of 2 in the tree is: " << tree.level(2) << std::endl; 

    std::cout << "The level of 56 in the tree is: " << tree.level(56) << std::endl; 

    return 0;
}