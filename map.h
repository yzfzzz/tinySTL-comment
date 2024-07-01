#pragma once
#include "RedBlackTree.h"

namespace mystl{

template <class Key, class Value>
class map{
public:
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    mystl::RedBlackTree<Key, Value> rbt;

    void insert(const Key k, const Value v)
    {
        rbt.insert(k, v);
    }

    void remove(const Key k)
    {
        rbt.deleteKey(k);
    }

    size_t size()
    {
        return rbt.getSize();
    }

    bool empty()
    {
        return rbt.empty();
    }

    Value* at(const Key k)
    {
        auto p = rbt.at(k);
        if(p != nullptr)
        {
            return p;
        }
        else
        {
            throw std::out_of_range("error! Key not found");
        }
    }

    Value& operator[](const Key k)
    {
        auto p = this->at(k);
        return *p;
    }

    void print()
    {
        rbt.printTree();
    }
};
}