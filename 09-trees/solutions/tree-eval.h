#pragma once

#include "btree.h"
#include "tree.h"
#include <string>

// Обхождаме дървото чрез Visitor класа
bool evalBooleanTree(BTreeVisitor<std::string> visitor)
{
    if (visitor.empty())
        return true;

    if (visitor.get() == "true")
        return true;
    if (visitor.get() == "false")
        return false;

    if (visitor.get() == "AND")
        return evalBooleanTree(visitor.goLeft()) && evalBooleanTree(visitor.goRight());

    if (visitor.get() == "OR")
        return evalBooleanTree(visitor.goLeft()) || evalBooleanTree(visitor.goRight());

    return false;
}

bool evalBooleanTree(BTree<std::string> &tree)
{
    return evalBooleanTree(tree.visitor());
}

int evalNumberTree(BTreeVisitor<std::string> visitor)
{
    if (visitor.empty())
        return 0;

    if (visitor.get() == "+")
        return evalNumberTree(visitor.goLeft()) + evalNumberTree(visitor.goRight());

    if (visitor.get() == "-")
        return evalNumberTree(visitor.goLeft()) - evalNumberTree(visitor.goRight());

    if (visitor.get() == "*")
        return evalNumberTree(visitor.goLeft()) * evalNumberTree(visitor.goRight());

    return std::stoi(visitor.get());
}

int evalNumberTree(BTree<std::string> &tree)
{
    return evalNumberTree(tree.visitor());
}

int evalNumberTree(TNode<std::string> *node)
{
    if (node == nullptr)
        return 0;

    if (node->data == "+")
    {
        int result = 0;
        for (TNode<std::string> *child : node->children)
        {
            result += evalNumberTree(child);
        }
        return result;
    }

    if (node->data == "-")
    {
        if (node->children.empty())
            return 0;
        int result = evalNumberTree(node->children.front());
        int i = 0;
        for (TNode<std::string> *child : node->children)
        {
            if (i != 0)
                result -= evalNumberTree(child);
            i++;
        }
        return result;
    }

    if (node->data == "*")
    {
        int result = 1;
        for (TNode<std::string> *child : node->children)
        {
            result *= evalNumberTree(child);
        }
        return result;
    }

    return std::stoi(node->data);
}