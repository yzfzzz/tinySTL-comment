# deque容器

[TOC]

## 基本概念

功能： 双端数组，可以对头端进行插入删除操作 

deque与vector区别： 

- vector对于头部的插入删除效率低，数据量越大，效率越低 
- deque相对而言，对头部的插入删除速度回比vector快 
- vector访问元素时的速度会比deque快,这和两者内部实现有关

![image-20240520214345386](https://yzfzzz.oss-cn-shenzhen.aliyuncs.com/image/image-20240520214345386.png)

## 功能

设计一个名为 Deque 的 Deque 类，该类具有以下功能和特性：

**1、基础成员函数**

- 构造函数：初始化 Deque 实例
- 析构函数：清理资源，确保无内存泄露

**2、核心功能**

- 在 Deque 末尾添加元素
- 在 Deque 开头添加元素
- 删除 Deque 末尾的元素
- 删除 Deque 开头的元素
- 获取 Deque 中节点的数量
- 删除 Deque 中所有的元素

**3、迭代与遍历**

- 打印 Deque 中的元素

**4、辅助功能**

- 重载[]运算符以对 Deque 进行索引访问

## 思路

下面代码将会使用循环数组的方式来模拟双端队列，实现了一个模板类 `deque`

### 数据结构

- `elements`：指向队列元素的指针
- `frontIndex`：队列第一个元素的索引
- `backIndex`：指向队列最后一个元素，下一位地址的索引。如果空间满了，则指向最后一个元素
- `size`：当前队列元素个数
- `capacity`：队列的最大容量

### 循环数组实现

如下图所示：

1. `push_front(10)`：首先要开辟一块连续的地址空间 `unuseded`（与vector一样，当存储容量capacity满了之后，我们要扩展空间，扩展后的容量将会翻倍），此时`frontIndex`和`backIndex`都指向`NULL`。随后，该块内存会分配数据（10），然后`frontIndex`和`backIndex`都会指向这个地址。
2. `push_back(20)`：由于存储空间不够用了，系统会再开辟一块内存，其大小为2，分配数据（20），然后`backIndex`移动到该地址，`frontIndex`不动
3. `push_front(30)`：同上，系统会再开辟一段存储空间，其大小为4。由于是在队头插入，且地址是连续的，为了模拟出循环队列的效果，我们会让`frontIndex`指针移到队尾，并将数据（30）存在队尾。当我们想遍历元素的时候，`frontIndex`会沿着 ♻ 绿色箭头的方向遍历（不用担心，这其实很好实现）
4. `push_back(0)`：存储空间够用，则`backIndex`指向的地址赋值（0），然后`backIndex`后移一位

![image-20240520193850545](https://yzfzzz.oss-cn-shenzhen.aliyuncs.com/image/image-20240520193850545.png)

## 代码实现

### deque.h

```cpp
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
        size = 0;
        elements = nullptr;
        frontIndex = 0;
        backIndex = 0;
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
```

### test.cpp

```cpp
#include "deque.h"
void dequeTest()
{
    mystl::deque<int> d1;
    d1.push_front(10);
    d1.push_back(20);
    d1.push_front(30);
    d1.push_back(0);
    d1.printElements();
    std::cout << d1[2] << std::endl;
    d1.pop_back();
    d1.printElements();
    d1.pop_front();
    d1.printElements();
    d1.clear();
    d1.printElements();
}

int main()
{
    dequeTest();
    system("pause");
    return 0;
}
```

## 代码详解

### 变量

```cpp
T* elements;
size_t frontIndex;
size_t backIndex;
size_t size;
size_t capacity;
```

- `elements`：指向队列元素的指针
- `frontIndex`：队列第一个元素的索引
- `backIndex`：指向队列最后一个元素，下一位地址的索引。如果空间满了，则指向最后一个元素
- `size`：当前队列元素个数
- `capacity`：队列的最大容量

除了elements是T指针外，其它都是整型

### push_front

记住我们赋值的1、2、3、4……都是常量，所以输入形参是 `const T& value`

```cpp
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
```

- 在队列前端插入元素。首先检查容量并调整数组大小（如果需要）

- 更新 `frontIndex`：`frontIndex = (frontIndex - 1 + capacity) % capacity;`

  如果`frontIndex`不在队头，那`frontIndex`往前移一位
  
  如果`frontIndex`在队头，即 `frontIndex = 0`，那么`frontIndex-1= -1`，`（-1 + capacity）% capcitys = capcitys - 1`，也就是当前存储空间的最后一个地址
  
- 在新位置插入元素，最后增加 `size`

### push_back

```cpp
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
```

- 在队列后端插入元素。首先检查容量并调整数组大小（如果需要），在 `backIndex`位置插入元素

- 更新 `backIndex` ：`backIndex = (backIndex + 1)%capacity`

  `backIndex`一般都是小于`capacity`，因此实际情况下`backIndex = backIndex + 1`

- 最后增加 `size`

### pop_front、pop_back

```c++
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
```

从队列前（后）端移除元素。首先检查队列是否为空，然后更新 `frontIndex`（`backIndex`），最后减少 `size`。

### operator[]

```cpp
T& operator[](int index)
{
    if(index >= size)
    {
    throw std::out_of_range("deque is empty");
    }
    return elements[(frontIndex+index)%capacity];
}
```

`(frontIndex+index)%capacity`：

把取值范围限定在[0，capacity-1]这个区间，如下图：当frontIndex = 3，在后面时，如果index = 2，capacity = 4，则（3+2）% 4 = 1；则是 20 这个元素

![image-20240520211909053](https://yzfzzz.oss-cn-shenzhen.aliyuncs.com/image/image-20240520211909053.png)

如下图：当frontIndex = 0，在后面时，如果index = 2，capacity = 4，则（0+2）% 4 = 2；则是 0 这个元素

![image-20240520212242898](https://yzfzzz.oss-cn-shenzhen.aliyuncs.com/image/image-20240520212242898.png)

### clear

```cpp
void clear()
{
    while(size > 0)
    {
    	pop_front();
    }
}
```

清空队列中的所有元素，通过不断调用 `pop_front` 方法实现。

### printElements

```cpp
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
```

打印队列中的所有元素，从 `frontIndex` 开始遍历，直到打印完所有元素。这里使用的`index`是是从`frontIndex`开始计算的索引, 而不是实际上的数组索引

`frontIndex`会沿着 ♻ 绿色箭头的方向遍历

![image-20240520213130054](https://yzfzzz.oss-cn-shenzhen.aliyuncs.com/image/image-20240520213130054.png)

### resize

```cpp
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
```

当数组容量不足以容纳更多元素时，创建一个新的数组，将现有元素复制到新数组中，释放旧数组，并更新相关成员变量。

需要注意的是, 原来的数组中, 逻辑上索引为0的位置(也就是`frontIndex`)并不一定存储在数组实际上的0索引处, 但`resize`后将逻辑索引和实际索引都统一起来。如图所示：

![image-20240520214054837](https://yzfzzz.oss-cn-shenzhen.aliyuncs.com/image/image-20240520214054837.png)

## 本实现版本 和 C++ STL标准库实现版本的区别：

标准库中的 `std::deque`（双端队列）通常是通过一个或者多个连续存储区域（即一维数组）来实现的，而不是单一的连续数组, 这多个一维数组连接起来形成了`deque`数组, 目前的实现采用的是循环数组, 缺点就是`resize`时要复制旧数组, 而官方的`std::deque`只需要再串联一个一维数组就可以了, 效率更高

内存管理、异常安全性、迭代器、性能优化均未实现
