#pragma once
#include "vector.h"

namespace mystl{

template <class T, class Container = mystl::Vector<T>>
class priority_queue 
{
public:
    // 小顶堆
    Container data;

    // 自上而下堆维护(向下)
    void heapFixDown()
    {
        int index = 0;
        while(1)
        {
            int lastIndex = index;
            int size = data.getSize();
            while(1)
            {
                int leftSon = 2*index + 1;
                int rightSon = 2*index + 2;

                if(leftSon < size && data[leftSon] > data[index])
                {
                    lastIndex = index;
                }
                if(rightSon < size && data[rightSon] > data[index])
                {
                    lastIndex = index;
                }

                if(lastIndex != index)
                {
                    std::swap(data[lastIndex], data[index]);
                    index = lastIndex;
                }
                else{
                    break;
                }
            } 
        }
    }

    // 自下而上堆维护(向上)
    void heapFixUp()
    {
        int parent;
        int index = data.getSize() - 1;
        while(index > 0)
        {
            parent = (index-1)/2;
            if(data[parent] < data[index])
            {
                break;
            }
            else
            {
                std::swap(data[parent] , data[index]);
                index = parent;
            }
        }
    }

    void push(const T& value)
    {
        data.push_back(value);
        heapFixUp();
    }

    void pop()
    {
        if(!this->empty())
        {
            std::swap(data[0], data[data.getSize() - 1]);
            data.pop_back();
            heapFixDown();
        }
        else
        {
            throw std::runtime_error("priority_queue is empty!");
        }
    }

    T& top()
    {
        if (!this->empty()) {
            return data[0];
        } else {
            throw std::runtime_error("Priority queue is empty.");
        }
    }

    bool empty() const
    {
        if(data.getSize() == 0)
            return true;
        return false;
    }

    size_t size() const
    {
        return data.size();
    }
};
}