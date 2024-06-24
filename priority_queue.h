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
        int largeIndex = index;
        int size = data.getSize();
        while(1)
        {
            int leftSon = 2*index + 1;
            int rightSon = 2*index + 2;
            if(leftSon < size && rightSon < size)
            {
                (data[leftSon] < data[rightSon])? (largeIndex = leftSon) : (largeIndex = rightSon);
            }
            // 右孩子越界了
            else if(leftSon < size)
            {
                if(data[leftSon] < data[index])
                {
                    largeIndex = leftSon;
                }
            }

            if(largeIndex != index)
            {
                std::swap(data[largeIndex], data[index]);
                index = largeIndex;
            }
            else
            {
                break;
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
            // 在堆中，删除操作通常指的是删除根节点，即最大元素或最小元素
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