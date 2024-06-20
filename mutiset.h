#pragma once
#include "RedBlackTree.h"

namespace mystl{

template <class Key>
class mutiset{
public:
    // Value��������
    mystl::RedBlackTree<Key, size_t> rbt;
    size_t mutiset_size;
    void insert(Key k)
    {
        auto p_num = rbt.at(k);
        if(p_num != nullptr)
        {
            (*p_num)++;
        }
        else
        {
            rbt.insert(k, 1);
        }
        mutiset_size++;
    }

    void erase(Key k)
    {
        auto p_num = rbt.at(k);
        if(p_num != nullptr)
        {
            (*p_num)--;
        }
        if(*p_num == 0)
        {
            rbt.deleteKey(k);
        }
        mutiset_size--;
    }

    // ����������Ԫ�ص�����
    size_t size() const { return mutiset_size; }

    // �ж������Ƿ�Ϊ��
    bool empty() const { return mutiset_size == 0; }

    // ������ multiset �е��ڸ���ֵ��Ԫ�ص�����
    size_t count(const Key &key) 
    {
        if (rbt.at(key) != nullptr) 
        {
            return *rbt.at(key);
        }
        return 0;
    }

    void clear() {
        mutiset_size = 0;
        rbt.clear();
    }

    void print()
    {
        rbt.printTree();
    }
};

}