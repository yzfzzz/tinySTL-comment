#pragma once
#include "deque.h"

namespace mystl{
template <class T, class Container = deque<T>>
class queue{
public:
    Container data;

    void push(const T& value)
    {
        data.push_back(value);
    }

    void pop()
    {
        if(!data.empty())
        {
            data.pop_front();
        }
        else
        {
            throw std::runtime_error("Queue is empty!");
        }
    }

    T& front()
    {
        if(!data.empty())
        {
            return data[0];
        }
        else
        {
            throw std::runtime_error("Queue is empty!");
        }
    }

    T& back()
    {
        if(!data.empty())
        {
            return data[data.size-1];
        }
        else
        {
            throw std::runtime_error("Queue is empty!");
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