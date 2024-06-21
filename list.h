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
        // ÿ���ڵ㶼����3������
        T value;
        Node* next;
        Node* prev;

        // Node���캯��,()��������Ҫ��Ĳ�����:�����Ǹ�������ֵ
        Node(const T &value, Node *nextNode = nullptr, Node *prevNode = nullptr)
            : value(value), next(nextNode), prev(prevNode) {}
    };

    Node* head; // ָ������ĵ�һ���ڵ�
    Node* tail; // ָ����������һ���ڵ�
    size_t size; // ������

public:
    list():head(nullptr),tail(nullptr),size(0){};

    // TODO: ���Կ���ʹ������ָ���Ա�����ʽ�Ŀռ����
    ~list()
    {
        this->size = 0;
        head = nullptr;
    }

    // ���������ӽڵ�
    void push_back(const T& c_value)
    {
        // �½�һ���ڵ㣬ǰָ��ָ��ǰ�����tailָ��
        Node* newNode = new Node(c_value, nullptr, this->tail);
        if(tail != nullptr)
        {
            // �������ǿգ���ô�����βָ��ĺ�һ���ڵ㣬��newNode
            this->tail->next = newNode;
        }
        else
        {
            // ��������ǿյģ����������ͷָ�����newNode
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

    // ���������е�Ԫ��, ע�ⷵ�ص�������, ����Ͳ���ͨ��[]����Ԫ��
    T& operator[](const size_t& index)
    {
        // �����ӡ���ڵ��������ȣ����׳��쳣
        if(index >= this->size)
        {
            throw std::out_of_range("out of range");
        }
        Node* elements = this->head;
        for(size_t i = 0;i<index;i++)
        {
            elements = elements->next; // ָ���Ƶ�Ŀ��ڵ�
        }
        // ���ظýڵ����ֵ
        return elements->value;
    }

    // TODO: ����ʹ������ָ��shared_ptr�Ա�����ʽ�Ŀռ����
    void pop_back()
    {
        if(this->size > 0)
        {
            Node* newTail = this->tail->prev; // ����һ���µ���ʱָ�룬ָ��ǰһ���ڵ�
            delete tail;
            tail = newTail; // βָ��ǰ��һ���ڵ�
            if(tail == NULL) // ����һ���ڵ�����
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

    // ��õ�һ��ָ����ֵ�Ľڵ�
    Node* getNode(const T& c_value)
    {
        Node* elements = head;
        while(elements != nullptr && elements->value != c_value)
        {
            elements = elements->next;
        }
        return elements;
    }

    // ɾ��ָ��ֵ�Ľڵ�
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