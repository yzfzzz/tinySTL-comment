#pragma once
#include "HashTable.h"

namespace mystl{
template <class Key, class Value>
class unordered_set{
public:
    HashTable<Key, Value> hashtable;
    // 该关键字告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化
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