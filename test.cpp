#include <string>
#include "vector.h"
#include "list.h"
#include "deque.h"
#include "HashTable.h"
#include "RedBlackTree.h"
#include "set.h"
#include "unordered_set.h"
#include "mutiset.h"
#include "map.h"
#include "unordered_map.h"
#include "mutimap.h"
#include "stack.h"
#include "queue.h"
#include "priority_queue.h"

void vectorTest();
void listTest();
void dequeTest();
void HashTableTest();
void RedBlackTree();
void setTest();
void unordered_set_Test();
void mutisetTest();
void mapTest();
void unordered_map_Test();
void mutimapTest();
void stackTest();
void queueTest();
void priority_queueTest();

// beta≤‚ ‘
int main()
{
    // vectorTest();
    // listTest();
    // dequeTest();
    // HashTableTest();
    // RedBlackTree();
    // setTest();
    // unordered_set_Test();
    // mutisetTest();
    // mapTest();
    // unordered_map_Test();
    // mutimapTest();
    // stackTest();
    // queueTest();
    // priority_queueTest();
    system("pause");
    return 0;
}

void priority_queueTest()
{
    mystl::priority_queue<int> pq;
    for(int i =0; i < 5; i++)
    {
        pq.push(i);
    }
    int a = pq.top();
    int b;
    for(int i = 0; i< 2; i++)
    {
        pq.pop();
    }
    int c= pq.top();
}

void queueTest()
{
    mystl::queue<int> qt;
    for(int i =0; i < 5; i++)
    {
        qt.push(i);
    }
    int a = qt.back();
    int b = qt.front();
    for(int i = 0; i< 2; i++)
    {
        qt.pop();
    }
    int c = qt.front();
}

void stackTest()
{
    mystl::stack<int> st;
    for(int i = 0; i < 5; i++)
    {
        st.push(i);
    }
    int a = st.top();
    for(int i = 0; i < 3; i++)
    {
        st.pop();
    }
    int b = st.top();
}

void mutimapTest()
{
    mystl::mutimap<std::string, int> mm;
    mm.insert("apple",10);
    mm.insert("apple",10);
    mm.insert("orange", 20);
    mm.insert("water",30);
    mm.remove("apple", 10);
    mm.remove("apple");
}

void unordered_map_Test()
{
    mystl::unordered_map<int, std::string> um;
    um.insert(10,"Apple");
    um.insert(15,"Lemon");
    um.insert(5,"Orange");
    um.erase(15);
    um.insert(15,"Lemon");
}

void mapTest()
{
    mystl::map<int, std::string> m;
    m.insert(1,"Apple");
    m.insert(2,"Benana");
    m.insert(3,"Orange");
    m.insert(4,"Lemon");
    m.insert(5,"Peach");
    auto v = m[2];
    m.remove(2);
    m.remove(1);
}

void mutisetTest()
{
    mystl::mutiset<int> ms;
    ms.insert(10);
    ms.insert(15);
    ms.insert(15);
    ms.insert(5);
    ms.erase(15);
    ms.print();
}

void unordered_set_Test()
{
    mystl::unordered_set<int, int> us;
    us.insert(10);
    us.insert(15);
    us.insert(5);
    us.erase(15);
    us.print();
}

void setTest()
{
    mystl::set<int, int> s;
    s.insert(10, 0);
    s.insert(15, 0);
    s.insert(5,0);
    s.erase(15);
    s.print();
}

void vectorTest()
{
    mystl::Vector<int> v1;
    v1.push_back(10);
    mystl::Vector<int> v2(v1);
    mystl::Vector<int> v3 = v2;
    for(int i = 0; i < 5; i++)
    {
        v3.push_back(i);
    }
    int size = v3.getSize();
    int cap = v3.getCapacity();
    int t = v3[3];
    std::cout << t << std::endl;
    v3.insert(2,88);
    v3.pop_back();
    int* ptr = v3.begin();
    v3.printElements();
    v3.clear();
}

void listTest()
{
    mystl::list<int> l1;
    l1.push_back(15);
    l1.push_front(18);
    for(int i = 0; i<5;i++)
    {
        l1.push_back(i);
    }
    l1.printElements();
    std::cout << l1[3] << std::endl;
    l1.pop_back();
    l1.pop_front();
    l1.printElements();
    mystl::list<int>::Node* ptr = l1.getNode(0);
    std::cout << ptr->value << std::endl;
    l1.remove(0);
    l1.printElements();
}

void dequeTest()
{
    mystl::deque<int> d1;
    d1.push_front(10);
    d1.push_back(20);
    d1.push_front(30);
    d1.push_back(0);
    d1.printElements();
    std::cout << d1[2] << std::endl;
    d1.pop_back();
    d1.printElements();
    d1.pop_front();
    d1.printElements();
    d1.clear();
    d1.printElements();
}

void HashTableTest()
{
    mystl::HashTable<int, int> hashTable;
    for(int i = 0;i<5;i++)
    {
        hashTable.insert(i, i*2);
        hashTable.print();
    }
    hashTable.print();
    int* t = hashTable.find(3);
    std::cout << *t << std::endl;
    hashTable.erase(3);
    hashTable.print();
    hashTable.clear();
    hashTable.print();
}

void RedBlackTree()
{
    mystl::RedBlackTree<int, int> rbt;
    rbt.insert(15, 0);
    rbt.insert(9, 0);
    rbt.insert(18, 0);
    rbt.insert(6, 0);
    rbt.insert(13, 0);
    rbt.insert(17, 0);
    rbt.insert(27, 0);
    rbt.insert(10, 0);
    rbt.insert(23, 0);
    rbt.insert(34, 0);
    rbt.insert(25, 0);
    rbt.insert(37, 0);
    rbt.printTree();
    rbt.deleteKey(18);
    rbt.deleteKey(25);
    rbt.deleteKey(15);
    rbt.deleteKey(6);
    rbt.deleteKey(13);
    rbt.deleteKey(37);
    rbt.deleteKey(27);
    rbt.deleteKey(17);
    rbt.deleteKey(34);
    rbt.deleteKey(9);
    rbt.deleteKey(10);
    rbt.deleteKey(23);
    rbt.printTree();
}