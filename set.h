#pragma once
#include "RedBlackTree.h"

namespace mystl{

template <class Key, class Value>
class set{
public:
    // set�ĵײ�ṹ�Ǻ����
    mystl::RedBlackTree<Key, Value> rbt;

    // ����
    void insert(Key k, Value v)
    {
        rbt.insert(k, v);
    }

    // ɾ��
    void erase(Key k)
    {
        rbt.deleteKey(k);
    }

    // ���ش�С
    size_t size()
    {
        return rbt.size();
    }

    // �ж��Ƿ�Ϊ��
    bool empty()
    {
        return rbt.empty();
    }

    // ��ӡ���
    void print()
    {
        rbt.printTree();
    }
};

}