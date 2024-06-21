#pragma once

#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

namespace mystl{
template <class T>
class list{
public:
    class Node{
    public:
        // 每个节点都包含3个变量
        T value;
        Node* next;
        Node* prev;

        // Node构造函数,()里面是需要填的参数，:后面是给变量赋值
        Node(const T &value, Node *nextNode = nullptr, Node *prevNode = nullptr)
            : value(value), next(nextNode), prev(prevNode) {}
    };

    Node* head; // 指向链表的第一个节点
    Node* tail; // 指向链表的最后一个节点
    size_t size; // 链表长度

public:
    list():head(nullptr),tail(nullptr),size(0){};

    // TODO: 可以考虑使用智能指针以避免显式的空间回收
    ~list()
    {
        this->size = 0;
        head = nullptr;
    }

    // 在链表后面加节点
    void push_back(const T& c_value)
    {
        // 新建一个节点，前指针指向当前链表的tail指针
        Node* newNode = new Node(c_value, nullptr, this->tail);
        if(tail != nullptr)
        {
            // 如果链表非空，那么链表的尾指针的后一个节点，是newNode
            this->tail->next = newNode;
        }
        else
        {
            // 如果链表是空的，则新链表的头指针就是newNode
            this->head = newNode;
        }
        tail = newNode;
        this->size++;
    }

    void push_front(const T& c_value)
    {
        Node* newNode = new Node(c_value, this->head, nullptr);
        if(this->head != NULL)
        {
            this->head->prev = newNode;
        }
        else
        {
            this->tail = newNode;
        }
        this->head = newNode;
        this->size++;
    }

    size_t getSize()
    {
        return this->size;
    }

    // 访问链表中的元素, 注意返回的是引用, 否则就不能通过[]更新元素
    T& operator[](const size_t& index)
    {
        // 如果索印大于等于链表长度，则抛出异常
        if(index >= this->size)
        {
            throw std::out_of_range("out of range");
        }
        Node* elements = this->head;
        for(size_t i = 0;i<index;i++)
        {
            elements = elements->next; // 指针移到目标节点
        }
        // 返回该节点的数值
        return elements->value;
    }

    // TODO: 考虑使用智能指针shared_ptr以避免显式的空间回收
    void pop_back()
    {
        if(this->size > 0)
        {
            Node* newTail = this->tail->prev; // 创建一个新的临时指针，指向前一个节点
            delete tail;
            tail = newTail; // 尾指针前移一个节点
            if(tail == NULL) // 考虑一个节点的情况
            {
                head = tail;
            }
            else
            {
                tail->next = nullptr;
            }
            size--;
        }
    }

    void pop_front()
    {
        if(this->size > 0)
        {
            Node* newHead = this->head->next;
            delete head;
            head = newHead;
            if(head == NULL)
            {
                tail = head;
            }
            else
            {
                head->prev = nullptr;
            }
            size--;
        }
    }

    // 获得第一个指定数值的节点
    Node* getNode(const T& c_value)
    {
        Node* elements = head;
        while(elements != nullptr && elements->value != c_value)
        {
            elements = elements->next;
        }
        return elements;
    }

    // 删除指定值的节点
    void remove(const T& c_value)
    {
        Node* elements = head;
        while(elements != nullptr && elements->value != c_value)
        {
            elements = elements->next;
        }
        if(!elements)
            return;
        if(elements != head && elements != tail)
        {
            elements->prev->next = elements->next;
            elements->next->prev = elements->prev;
        }
        else if(elements == head && elements == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else if(elements == head && elements != tail)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete elements;
        size--;
    }

    bool empty()
    {
        if(size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void clear()
    {
        while(head)
        {
            Node* elements = head;
            head = head->next;
            delete elements;
        }
        tail = nullptr;
        size = 0;
    }

    Node* begin()
    {
        return head;
    }

    Node* end()
    {
        return nullptr;
    }

    void printElements()
    {
        Node* temp = head;
        while(temp)
        {
            std::cout<< temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

}