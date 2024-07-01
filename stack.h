#pragma once
#include "deque.h"

namespace mystl{
template <class T, class Container = deque<T>>
class stack{
public:
    // stack�ĵײ��õ���˫������
    Container data;

    void pop()
    {
        if(data.empty())
        {
            throw std::runtime_error("Stack is empty.");
        }
        else
        {
            data.pop_back();
        }
    }

    void push(const T& value)
    {
        data.push_back(value);
    }

    T& top()
    {
        if(data.empty())
        {
            throw std::runtime_error("Stack is empty.");
        }
        else
        {
            return data[data.getSize()-1];
        }
    }

    size_t size() const
    {
        return data.getSize();
    }

    bool empty() const
    {
        return data.empty();
    }
};
}