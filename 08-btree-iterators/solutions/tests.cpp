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

    tree.printDot();

    return 0;
}