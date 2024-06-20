#pragma once
#include "HashTable.h"

namespace mystl{
template <class Key, class Value>
class unordered_set{
public:
    HashTable<Key, Value> hashtable;
    // �ùؼ��ָ��߱������������в��ᷢ���쳣,�������ڱ������Գ�����������Ż�
    bool empty() const noexcept { return hashtable.size() == 0; }

    size_t size() const noexcept { return hashtable.size(); }

    void clear() noexcept { hashtable.clear(); }

    void insert(Key key) { hashtable.insertKey(key); }

    void erase(Key key) { hashtable.erase(key); }

    bool find(const Key &key) { return hashtable.find(key) != nullptr; }

    void print()
    {
        hashtable.print();
    }
};

}