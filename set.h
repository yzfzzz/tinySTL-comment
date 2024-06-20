#pragma once
#include "RedBlackTree.h"

namespace mystl{

template <class Key, class Value>
class set{
public:
    mystl::RedBlackTree<Key, Value> rbt;

    void insert(Key k, Value v)
    {
        rbt.insert(k, v);
    }

    void erase(Key k)
    {
        rbt.deleteKey(k);
    }

    size_t size()
    {
        return rbt.size();
    }

    bool empty()
    {
        return rbt.empty();
    }

    void print()
    {
        rbt.printTree();
    }
};

}