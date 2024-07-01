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
  
  // ������Ҫά����
  class HashNode{
  public:
    Key key;
    Value value;
    
    // ��Key����ڵ㣬Valueʹ��Ĭ�Ϲ���
    explicit HashNode(const Key &key): key(key), value(){}
    
    // ��Key��Value����ڵ�
    HashNode(const Key &key, const Value &value):key(key), value(value){}
    
    // �Ƚ���������أ��Ƚ�key
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
    // �������һ��Ͱ��Bucket����Ͱ����װ����һ����HashNode�ڵ���ɵ�����
    using Bucket = std::list<HashNode>;
    std::vector<Bucket> buckets;    // �����ɶ����������ɵ�����
    std::hash<Key> hashFunction;    // ����һ����ϣ����
    size_t tableSize;               // ��ϣ����������
    size_t numElements;             // ��ϣ���е�ǰԪ�ص�����
    float maxLoadFactor = 0.75;     // Ĭ�ϵ����������
    
    // ��ϣ��������key��ֵ��ȡģ��ֹ�������Ϊ��ϣ�������
    size_t hash(const Key &key) const { return hashFunction(key)%tableSize; }
    
    // ��Ԫ�����������������ʱ������Ͱ�����������·������м�
    void rehash(size_t newSize)
    {
        std::vector<Bucket> newBuckets(newSize);// ����һ���µ�Ͱ���飬��СΪnewsize
        for(Bucket &bucket : buckets)           // ����ԭ����Ͱ����buckets������ȡ�����е�һ��Ͱ��bucket��
        {
            // �������
            for(HashNode &hashNode : bucket)    // ����ԭ����Ͱbucket������һ����������ȡ�����е�һ���ڵ㣨hashNode��
            {
                // �µ�������ԭ����������ͬ
                size_t newIndex = hashFunction(hashNode.key)%newSize;// �����µ�����
                newBuckets[newIndex].push_back(hashNode);
            }
        }
        // �ƶ�����
        buckets = std::move(newBuckets);
        tableSize = newSize;
    }
    
public:
    // ��ϣ���캯����ʼ��, ע�⣺typename Hash = std::hash<Key>
    /* 
        std::hash<Key>() ������һ����ʱ�� std::hash<Key> ����
        ��Ϊ std::hash<Key> ��һ��Ĭ�ϵĹ��캯�����޲����Ĺ��캯���������Կ���ֱ������������������һ����ʱ����
        �����ʱ����������ʼ��֮�󣬾�����
    */ 
    HashTable(size_t size = 0, const std::hash<Key> &hashFunc = Hash()):buckets(size),hashFunction(hashFunc),tableSize(size),numElements(0){}
    // ����ֵ�Բ����ϣ����
    void insert(const Key &key, const Value &value)
    {
        if((numElements + 1) > maxLoadFactor * tableSize)   // ����һ���������ӣ���֤��ϣ��Ԥ���Ŀռ��㹻�࣬����������������׷�����ͻ�����ٿ�������
        {
            if(tableSize == 0)
                tableSize = 1;
            rehash(tableSize * 2);
        }
        size_t index = hash(key);   // ��������
        Bucket &bucket = buckets[index];    // �ҳ���������Ӧ��Ͱ
        if(std::find(bucket.begin(),bucket.end(),key) == bucket.end())  //  ���Ͱ��û���������ڸ�Ͱ�в������������У���ֱ������
        {
            bucket.push_back(HashNode(key, value));
            numElements++;
        }
    }
    
    void insertKey(const Key &key) { insert(key, Value{}); }    // ֵΪ�յ����
    
    void erase(const Key &key)
    {
        size_t index = hash(key);   // ��������
        auto &bucket = buckets[index];  // �ҳ���������Ӧ��Ͱ
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if(it != bucket.end())
        {
            // �ҵ�������ɾ����
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
            return &ans->value; // ���ؽ��value���ڵĵ�ַ
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
                element.print();    // ����HashNode��ĳ�Ա����print
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