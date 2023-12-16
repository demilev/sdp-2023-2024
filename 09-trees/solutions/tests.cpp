#include "bstree.h"
#include "btree.h"
#include "tree.h"
#include "tree-eval.h"

int main()
{
    // задача 1
    Node<int> *root = new Node<int>(3);
    Node<int> *n1 = new Node<int>(4);
    Node<int> *n2 = new Node<int>(5);

    Node<int> *n3 = new Node<int>(6);
    Node<int> *n4 = new Node<int>(12);

    Node<int> *n5 = new Node<int>(7);

    root->left = n1;
    root->right = n2;

    n1->left = n3;
    n1->right = n5;

    n2->left = n4;

    BTree<int> tree(root);

    tree.printDot();

    std::cout << std::boolalpha << "Is the tree balanced: " << tree.isBalanced() << std::endl;

    // задача 2
    BSTree<int> bstree = BSTree<int>::balanced({-10, -6, 0, 1, 5, 8, 9, 12, 16, 25, 32, 44, 48, 55, 58, 62, 88, 103});
    bstree.printDot();

    std::cout << std::boolalpha << "Is the binary search tree balanced: " << bstree.isBalanced() << std::endl;

    // задача 3
    std::list<std::list<int>> allPaths = tree.allPaths();
    std::cout << "All Paths: " << std::endl;
    for (auto l : allPaths)
    {
        for (int i : l)
        {
            std::cout << i << " ";
        }

        std::cout << std::endl;
    }

    std::list<std::list<int>> allLevels = tree.allLevels();

    std::cout << "All Levels: " << std::endl;
    for (auto l : allLevels)
    {
        for (int i : l)
        {
            std::cout << i << " ";
        }

        std::cout << std::endl;
    }

    // задача 4
    TNode<std::string> *wtroot = new TNode<std::string>("Hello World!");

    TNode<std::string> *wt1 = new TNode<std::string>("Hello");
    TNode<std::string> *wt2 = new TNode<std::string>("World!");

    wtroot->addChild(wt1);
    wtroot->addChild(wt2);

    Tree<std::string> wordTree(wtroot);
    std::cout << "All levels represent the same sentence: " << std::boolalpha << areAllLevelsTheSameSentence(wordTree) << std::endl;

    // задача 5
    TNode<int> *troot = new TNode<int>(0);

    TNode<int> *t1 = new TNode<int>(1);
    TNode<int> *t2 = new TNode<int>(2);
    TNode<int> *t3 = new TNode<int>(3);

    TNode<int> *t4 = new TNode<int>(4);
    TNode<int> *t5 = new TNode<int>(5);
    TNode<int> *t6 = new TNode<int>(6);

    TNode<int> *t7 = new TNode<int>(7);
    TNode<int> *t8 = new TNode<int>(8);
    TNode<int> *t9 = new TNode<int>(9);
    TNode<int> *t10 = new TNode<int>(10);

    troot->addChild(t1);
    troot->addChild(t2);
    troot->addChild(t3);

    t1->addChild(t4);
    t2->addChild(t5);
    t2->addChild(t6);

    t5->addChild(t7);
    t5->addChild(t8);
    t5->addChild(t9);
    t5->addChild(t10);

    Tree<int> mtree(troot);
    mtree.serialise();
    std::cout << std::endl;

    Tree<int> mtree1 = Tree<int>::deserialize(std::cin);
    mtree1.serialise();
    std::cout << std::endl;

    // задача 6
    Node<std::string> *broot = new Node<std::string>("AND");
    Node<std::string> *bn1 = new Node<std::string>("OR");
    Node<std::string> *bn2 = new Node<std::string>("OR");

    Node<std::string> *bn3 = new Node<std::string>("true");
    Node<std::string> *bn4 = new Node<std::string>("false");
    Node<std::string> *bn5 = new Node<std::string>("false");
    Node<std::string> *bn6 = new Node<std::string>("false");

    broot->left = bn1;
    broot->right = bn2;

    bn1->left = bn3;
    bn1->right = bn4;
    bn2->left = bn5;
    bn2->right = bn6;

    BTree<std::string> booleanTree(broot);

    std::cout << "Bool eval: " << std::boolalpha << evalBooleanTree(booleanTree) << std::endl;

    Node<std::string> *nroot = new Node<std::string>("+");
    Node<std::string> *nn1 = new Node<std::string>("*");
    Node<std::string> *nn2 = new Node<std::string>("-");

    Node<std::string> *nn3 = new Node<std::string>("5");
    Node<std::string> *nn4 = new Node<std::string>("3");
    Node<std::string> *nn5 = new Node<std::string>("12");
    Node<std::string> *nn6 = new Node<std::string>("8");

    nroot->left = nn1;
    nroot->right = nn2;

    nn1->left = nn3;
    nn1->right = nn4;
    nn2->left = nn5;
    nn2->right = nn6;

    BTree<std::string> numberBinaryTree(nroot);

    TNode<std::string> *ntroot = new TNode<std::string>("+");

    TNode<std::string> *nt1 = new TNode<std::string>("12");
    TNode<std::string> *nt2 = new TNode<std::string>("35");
    TNode<std::string> *nt3 = new TNode<std::string>("-");

    TNode<std::string> *nt4 = new TNode<std::string>("*");
    TNode<std::string> *nt5 = new TNode<std::string>("4");
    TNode<std::string> *nt6 = new TNode<std::string>("5");

    TNode<std::string> *nt7 = new TNode<std::string>("3");
    TNode<std::string> *nt8 = new TNode<std::string>("2");

    ntroot->addChild(nt1);
    ntroot->addChild(nt2);
    ntroot->addChild(nt3);

    nt3->addChild(nt4);
    nt3->addChild(nt5);
    nt3->addChild(nt6);

    nt4->addChild(nt7);
    nt4->addChild(nt8);

    std::cout << "Number eval binary tree: " << evalNumberTree(numberBinaryTree) << std::endl;
    std::cout << "Number eval tree: " << evalNumberTree(ntroot) << std::endl;

    // задача 7
    std::list<BTree<int>> forest = tree.forest(bstree);

    for (BTree<int> bt : forest)
    {
        bt.printDot();
    }

    return 0;
}