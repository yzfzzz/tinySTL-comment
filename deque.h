#pragma once

#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

namespace mystl{
template <class T>
class deque{

public:
    T* elements;
    size_t frontIndex;
    size_t backIndex;
    size_t size;
    size_t capacity;
    
    deque():elements(nullptr), size(0), capacity(0),frontIndex(0),backIndex(0){};
    ~deque()
    {
        clear();
        delete[] elements;
    }
    
    void push_front(const T& value)
    {
        if(size == capacity)
        {
            resize();
        }
        frontIndex = (frontIndex - 1 + capacity)%capacity;
        elements[frontIndex] = value;
        size++;
    }
    
    void push_back(const T& value)
    {
        if(size == capacity)
        {
            resize();
            
        }
        elements[backIndex] = value; // ?
        backIndex = (backIndex + 1)%capacity;
        size++;
    }
    
    void pop_front()
    {
        if(size == 0)
        {
            throw std::out_of_range("deque is empty");
        }
        frontIndex = (frontIndex+1)%capacity;
        size--;
    }
    
    void pop_back()
    {
        if(size == 0)
        {
            throw std::out_of_range("deque is empty");
        }
        backIndex = (backIndex - 1 + capacity)%capacity;
        size--;
    }
    
    T& operator[](int index)
    {
        if(index >= size)
        {
            throw std::out_of_range("deque is empty");
        }
        return elements[(frontIndex+index)%capacity];
    }
    
    size_t getSize() const
    {
        return size;
    }
    
    void clear()
    {
        while(size > 0)
        {
            pop_front();
        }
    }
    
    void printElements() const
    {
        size_t index = frontIndex;
        for(size_t i = 0; i<size;++i)
        {
            std::cout <<  elements[index] << " ";
            index = (index+1)%capacity;
        }
        std::cout << std::endl;
    }
    


private:
    void resize()
    {
        size_t newCapacity = (capacity == 0)? 1:2*capacity;
        T* newElements = new T[newCapacity];
        size_t index = frontIndex;
        for(size_t i =0; i<size; ++i)
        {
            newElements[i] = elements[index];
            index = (index+1)%capacity;
        }
        delete[] elements;
        
        elements = newElements;
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = size;
    }
};

}
