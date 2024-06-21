#pragma once
#include "HashTable.h"

namespace mystl{
template<class Key, class Value>
class unordered_map{
public:
    HashTable<Key, Value> hashtable;

    bool empty() const noexcept { return hashtable.size() == 0; }

    size_t size() const noexcept { return hashtable.size(); }

    void clear() noexcept { hashtable.clear(); }

    void insert(Key key, Value value) { hashtable.insert(key, value); }

    void erase(Key key) { hashtable.erase(key); }

    bool find(const Key &key) { return hashtable.find(key) != nullptr; }

    void print()
    {
        hashtable.print();
    }
};

}