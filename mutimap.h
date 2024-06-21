#pragma once
#include "RedBlackTree.h"
#include "list.h"

namespace mystl
{
template <class Key, class Value>
class mutimap{
public:
    using ValueType = list<Value>;
    mystl::RedBlackTree<Key, ValueType> rbt;
    size_t size = 0;

    void insert(const Key& k, const Value& v)
    {
        ValueType* p = rbt.at(k);
        if(p != nullptr)
        {
            p->push_back(v);
        }
        else
        {
            ValueType newList;
            newList.push_back(v);
            rbt.insert(k,newList);
        }
        size++;
    }

    void remove(const Key& k)
    {
        ValueType* p = rbt.at(k);
        if(p != nullptr)
        {
            p->pop_back();
            size -= p->getSize();
            rbt.deleteKey(k);
        }
    }

    void remove(const Key& k, const Value& v)
    {
        ValueType* p = rbt.at(k);
        if(p != nullptr)
        {
            p->remove(v);
            size --;
            if(p->empty())
            {
                rbt.deleteKey(k);
            }
        }
    }

    ValueType *at(const Key& k) 
    {
        // 获取键对应的所有值的列表
        return rbt.at(k);
    }

    int getSize() { return size; }

    bool empty() { return size == 0; }
};
}