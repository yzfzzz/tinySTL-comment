#pragma once
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

namespace mystl{
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable{
  
  // 链表中要维护的
  class HashNode{
  public:
    Key key;
    Value value;
    
    // 从Key构造节点，Value使用默认构造
    explicit HashNode(const Key &key): key(key), value(){}
    
    // 从Key和Value构造节点
    HashNode(const Key &key, const Value &value):key(key), value(value){}
    
    // 比较运算符重载，比较key
    bool operator==(const HashNode &other) const { return key == other.key;}
    bool operator!=(const HashNode &other) const { return key != other.key; }
    bool operator<(const HashNode &other) const { return key < other.key; }
    bool operator>(const HashNode &other) const { return key > other.key; }
    bool operator==(const Key &key_) const { return key == key_; }
    
    void print() const
    {
        std::cout<<"(" << key <<","<< value<<")" << " ";
    }
  };
  
private:
    // 定义表中一个桶（Bucket），桶里面装的是一个个HashNode节点组成的链表
    using Bucket = std::list<HashNode>;
    std::vector<Bucket> buckets;    // 定义由多个槽连续组成的数组
    std::hash<Key> hashFunction;    // 定义一个哈希函数
    size_t tableSize;               // 哈希表的最大容量
    size_t numElements;             // 哈希表中当前元素的数量
    float maxLoadFactor = 0.75;     // 默认的最大负载因子
    
    // 哈希函数计算key的值，取模防止溢出，作为哈希表的索引
    size_t hash(const Key &key) const { return hashFunction(key)%tableSize; }
    
    // 当元素数量大于最大容量时，增加桶的数量并重新分配所有键
    void rehash(size_t newSize)
    {
        std::vector<Bucket> newBuckets(newSize);// 创建一个新的桶数组，大小为newsize
        for(Bucket &bucket : buckets)           // 遍历原来的桶数组buckets，轮流取出其中的一个桶（bucket）
        {
            // 链表遍历
            for(HashNode &hashNode : bucket)    // 遍历原来的桶bucket，它是一个链表，轮流取出其中的一个节点（hashNode）
            {
                // 新的索引与原来的索引相同
                size_t newIndex = hashFunction(hashNode.key)%newSize;// 计算新的索引
                newBuckets[newIndex].push_back(hashNode);
            }
        }
        // 移动语义
        buckets = std::move(newBuckets);
        tableSize = newSize;
    }
    
public:
    // 哈希表构造函数初始化, 注意：typename Hash = std::hash<Key>
    /* 
        std::hash<Key>() 创建了一个临时的 std::hash<Key> 对象。
        因为 std::hash<Key> 有一个默认的构造函数（无参数的构造函数），所以可以直接这样调用它来创建一个临时对象。
        这个临时对象被用来初始化之后，就销毁
    */ 
    HashTable(size_t size = 0, const std::hash<Key> &hashFunc = Hash()):buckets(size),hashFunction(hashFunc),tableSize(size),numElements(0){}
    // 将键值对插入哈希表中
    void insert(const Key &key, const Value &value)
    {
        if((numElements + 1) > maxLoadFactor * tableSize)   // 乘以一个负载因子，保证哈希表预留的空间足够多，计算出的索引不容易发生冲突，减少拷贝次数
        {
            if(tableSize == 0)
                tableSize = 1;
            rehash(tableSize * 2);
        }
        size_t index = hash(key);   // 计算索引
        Bucket &bucket = buckets[index];    // 找出该索引对应的桶
        if(std::find(bucket.begin(),bucket.end(),key) == bucket.end())  //  如果桶中没有链表，则在该桶中插入该链表；如果有，则直接跳过
        {
            bucket.push_back(HashNode(key, value));
            numElements++;
        }
    }
    
    void insertKey(const Key &key) { insert(key, Value{}); }    // 值为空的情况
    
    void erase(const Key &key)
    {
        size_t index = hash(key);   // 计算索引
        auto &bucket = buckets[index];  // 找出该索引对应的桶
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if(it != bucket.end())
        {
            // 找到该链表，删除它
            bucket.erase(it);
            numElements--;
        }
    }
    
    Value* find(const Key &key)
    {
        size_t index = hash(key);
        auto &bucket = buckets[index];
        auto ans = std::find(bucket.begin(), bucket.end(), key);
        if(ans != bucket.end())
        {
            return &ans->value; // 返回结点value所在的地址
        }
        return nullptr;
    }
    
    size_t size() const { return numElements; }
    void print() const 
    {
        for(size_t i = 0; i < buckets.size(); i++)
        {
            for(const HashNode &element : buckets[i])
            {
                element.print();    // 调用HashNode类的成员函数print
            }
        }
        std::cout << std::endl;
    }
    
    void clear()
    {
        this->buckets.clear();
        this->numElements = 0;
        this->tableSize = 0;
    }
};
}