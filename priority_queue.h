#pragma once
#include "vector.h"

namespace mystl{

template <class T, class Container = mystl::Vector<T>>
class priority_queue 
{
public:
    // ���ȶ��еײ�ṹ�õ���С����
    Container data;

    // ���϶��¶�ά��(����)
    void heapFixDown()
    {
        int index = 0;
        int largeIndex = index;
        int size = data.getSize();
        while(1)
        {
            // ��������Ϊi��Ԫ�أ������ӽڵ������Ϊ2*i + 1�����ӽڵ������Ϊ2*i + 2�����ڵ������Ϊ(i-1)/2, �丸�ڵ������Ϊi//2
            int leftSon = 2*index + 1;
            int rightSon = 2*index + 2;
            if(leftSon < size && rightSon < size)
            {
                (data[leftSon] < data[rightSon])? (largeIndex = leftSon) : (largeIndex = rightSon);
            }
            // �Һ���Խ����
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

    // ���¶��϶�ά��(����)
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
        // ���Ƚ�������ڶѵ�, Ȼ��͸��ڵ���бȽ�, ����µĽڵ��С, �ͽ������ӽڵ�, һֱ�ݹ�ؽ���ֱ�����ڵ�򸸽ڵ�С���ӽڵ�
        data.push_back(value);
        heapFixUp();
    }

    void pop()
    {
        //  ɾ��ʱ�öѵ׽ڵ�����滻, Ȼ�󽫸����ڵ�������, ע������ʱҪѡ���С�ĺ��ӽ��н���
        if(!this->empty())
        {
            // �ڶ��У�ɾ������ͨ��ָ����ɾ�����ڵ㣬�����Ԫ�ػ���СԪ��
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