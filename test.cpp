#include "vector.h"
#include "list.h"
#include "deque.h"
#include "HashTable.h"
#include "RedBlackTree.h"

// beta≤‚ ‘∞Ê

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
    mystl::RedBlackTree<int> rbt(15);
    rbt.insert(9);
    rbt.insert(18);
    rbt.insert(6);
    rbt.insert(13);
    rbt.insert(17);
    rbt.insert(27);
    rbt.insert(10);
    rbt.insert(23);
    rbt.insert(34);
    rbt.insert(25);
    rbt.insert(37);
    rbt.printTree();

    rbt.deleteNode(18);
    rbt.deleteNode(25);
    rbt.deleteNode(15);
    rbt.deleteNode(6);
    rbt.deleteNode(13);
    rbt.printTree();
}

int main()
{
    // vectorTest();
    // listTest();
    // dequeTest();
    //HashTableTest();
    RedBlackTree();
    system("pause");
    return 0;
}