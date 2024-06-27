#pragma once
#include "vector.h"

namespace mystl{

template <class T, class Container = mystl::Vector<T>>
class priority_queue 
{
public:
    // 优先队列底层结构用的是小顶堆
    Container data;

    // 自上而下堆维护(向下)
    void heapFixDown()
    {
        int index = 0;
        int largeIndex = index;
        int size = data.getSize();
        while(1)
        {
            // 给定索引为i的元素，其左子节点的索引为2*i + 1，右子节点的索引为2*i + 2，父节点的索引为(i-1)/2, 其父节点的索引为i//2
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
        // 首先将其插入在堆底, 然后和父节点进行比较, 如果新的节点更小, 就交换父子节点, 一直递归地进行直到根节点或父节点小于子节点
        data.push_back(value);
        heapFixUp();
    }

    void pop()
    {
        //  删除时用堆底节点进行替换, 然后将根顶节点逐步下游, 注意下游时要选择更小的孩子进行交换
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