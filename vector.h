#pragma once
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

/*
    设计一个 Vector 类，该类应具备以下功能和特性：
    1、基础成员函数：
    构造函数：初始化 Vector 实例
    析构函数：清理资源，确保无内存泄露
    拷贝构造函数：允许通过现有的 MyVector 实例来创建一个新实例
    拷贝赋值操作符：实现 MyVector 实例之间的赋值功能

    2、核心功能：
    添加元素到末尾：允许在 Vector 的末尾添加新元素
    获取元素个数：返回 Vector 当前包含的元素数量
    获取容量：返回 Vector 可以容纳的元素总数
    访问指定索引处的元素：通过索引访问特定位置的元素
    在指定位置插入元素：在 Vector 的特定位置插入一个新元素
    删除数组末尾元素：移除 Vector 末尾的元素
    清空数组：删除 Vector 中的所有元素，重置其状态

    3、迭代与遍历：
    使用迭代器遍历：实现迭代器以支持对 Vector 从开始位置到结束位置的遍历
    遍历并打印数组元素：提供一个函数，通过迭代器遍历并打印出所有元素

    4、高级特性：
    容器扩容：当前容量不足以容纳更多元素时，自动扩展 Vector 的容量以存储更多元素
*/

namespace mystl{
template <typename T>
class Vector
{
private:
    T *elements;    // 指向动态数组的指针
    size_t capacity;    // 数组的容量, size_t = unsigned int
    size_t size;    // 数组中元素的个数
    
public:
    // 构造函数：初始化Vector对象，默认设置指针悬空，容量设置为0，当前元素的数量也为0
    Vector():elements(nullptr), capacity(0), size(0){};
    //  析构函数：销毁Vector对象，释放指针
    ~Vector()
    {
        delete[] elements; // elements是数组指针
    }
    // 拷贝构造函数，cap、size都默认和副本相同
    Vector(const Vector& other):capacity(other.capacity),size(other.size)
    {
        // 找一块地方开辟地址空间
        elements = new T[capacity];
        /* 
            作用：从一个容器复制元素到另一个容器。std::copy需要三个参数：
            两个指定要复制的元素范围的迭代器（起始迭代器和结束迭代器），以及一个指向目标位置开始的迭代器。 
            指针也是一种天然的迭代器
        */
        std::copy(other.elements, other.elements+size, elements);
    }
    // 拷贝复制+运算符重载
    Vector& operator=(const Vector& other)  // 将vector副本强转为常量
    {
        if(this != &other)  // 通过判断两个指针是否相同，检查是不是自赋值的情况
        {
            delete[] elements;  // 删除这一块地址的数据、指针
            // 获取副本的数据
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            // 分配新内存，并复制所有元素
            std::copy(other.elements, other.elements+size, elements);
        }
        return *this;  // 返回当前对象的引用
    }
    // push_back函数
    void push_back(const T& value)
    {
        // 如果内存将要溢出，则开辟更大的空间
        if(size == capacity)
        {
            // 不能简单的将capacity容量翻倍, 需要考虑0的边界情况
            // 如果是开始时刻，没有分配内存，则分配1块内存，否则内存空间加倍
            reserve(capacity==0? 1:2*capacity);
        }
        elements[size++] = value;
    }
    // 返回Vector中的元素数量
    size_t getSize() const
    {
        return size;
    }
    // 返回Vector的容量
    size_t getCapacity() const
    {
        return capacity;
    }
    // 下标操作符重载，允许通过下标访问Vector中的元素
    T& operator[](size_t index)
    {
        // 如果指定的下标越界（大于或等于 size），则抛出 std::out_of_range 异常
        if(index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        /*
            当 int arr[] = { 99, 15, 100, 888, 252 } 时，arr是指向数组首地址的指针。可以采用 arr[i] 的形式访问数组元素。
            如果 p 是指向数组 arr 的指针，那么也可以使用 p[i] 来访问数组元素，它等价于 arr[i]
        */ 
        return elements[index];
    }
    // insert函数
    void insert(size_t index, const T& value)
    {
        if(index > size)
        {
            throw std::out_of_range("Index out of range");
        }
        if(size == capacity)
        {
            reserve(capacity == 0? 1:capacity*2);
        }
        // 后续元素后移
        for(size_t i = size; i>index;--i)  // TODO:为什么不是i--？
        {
            elements[i] = elements[i-1];
        }
        elements[index] = value;
        ++size;
    }
    void pop_back()
    {
        if(size > 0)
        {
            --size;   
        }
    }
    void clear()
    {
        size = 0;
    }
    // 非 const 版本返回指向 elements 的指针，可以用来修改 Vector 中的元素
    T* begin()
    {
        return elements;
    }
    T* end()
    {
        return elements+size;
    }
    // const 版本返回 const 指针，用于只读访问
    const T* begin() const
    {
        return elements;
    }
    const T* end() const
    {
        return elements+size;
    }
    void printElements() const // const 关键字在成员函数声明之后表示该函数不会修改类的任何成员变量
    {
        for(size_t i = 0; i<size; ++i)
        {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }
    
private:
    void reserve(size_t newCapacity)
    {
        if(newCapacity > capacity)
        {
            // 在其它地方找一个空间
            T* newElements = new T[newCapacity];
            // 把元素拷贝过去
            std::copy(elements,elements+size,newElements);
            // 释放旧内存
            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }
    }
    
};
}
