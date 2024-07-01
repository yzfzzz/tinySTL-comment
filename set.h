#pragma once
#include "RedBlackTree.h"

namespace mystl{

template <class Key, class Value>
class set{
public:
    // set的底层结构是红黑树
    mystl::RedBlackTree<Key, Value> rbt;

    // 插入
    void insert(Key k, Value v)
    {
        rbt.insert(k, v);
    }

    // 删除
    void erase(Key k)
    {
        rbt.deleteKey(k);
    }

    // 返回大小
    size_t size()
    {
        return rbt.size();
    }

    // 判断是否为空
    bool empty()
    {
        return rbt.empty();
    }

    // 打印结点
    void print()
    {
        rbt.printTree();
    }
};

}