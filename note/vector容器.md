# vector容器

[TOC]

## 基本概念

- vector数据结构和数组非常相似，也称为单端数组 
- vector与普通数组区别： 不同之处在于数组是静态空间，而vector可以动态扩展 
- 动态扩展： 并不是在原空间之后续接新空间，而是找更大的内存空间，然后将原数据拷贝新空间，释放原空间

## 功能

设计一个 Vector 类，该类应具备以下功能和特性：

**1、基础成员函数：**

- 构造函数：初始化 Vector 实例
- 析构函数：清理资源，确保无内存泄露
- 拷贝构造函数：允许通过现有的 MyVector 实例来创建一个新实例
- 拷贝赋值操作符：实现 MyVector 实例之间的赋值功能

**2、核心功能：**

- 添加元素到末尾：允许在 Vector 的末尾添加新元素
- 获取元素个数：返回 Vector 当前包含的元素数量
- 获取容量：返回 Vector 可以容纳的元素总数
- 访问指定索引处的元素：通过索引访问特定位置的元素
- 在指定位置插入元素：在 Vector 的特定位置插入一个新元素
- 删除数组末尾元素：移除 Vector 末尾的元素
- 清空数组：删除 Vector 中的所有元素，重置其状态

**3、遍历：**

- 遍历并打印数组元素：提供一个函数，通过迭代器遍历并打印出所有元素

**4、高级特性：**

- 容器扩容：当前容量不足以容纳更多元素时，自动扩展 Vector 的容量以存储更多元素

## 思路

**内存分配**

当容量不足以容纳新元素时，`std::vector` 会分配一块新的内存空间，将原有元素复制到新的内存中，然后释放原内存。这个过程确保了元素的连续存储。

**动态扩容**

当需要进行扩容时，`std::vector` 通常会将容量翻倍，以避免频繁的内存分配操作，从而减少系统开销。

涉及以下步骤：

1. 分配一个更大的内存块，通常是当前大小的两倍（这个增长因子取决于实现）。
2. 将当前所有元素移到新分配的内存中。
3. 销毁旧元素，并释放旧内存块。
4. 插入新元素。

---------------------------------------

![image-20240521155911371](https://yzfzzz.oss-cn-shenzhen.aliyuncs.com/image/image-20240521155911371.png)

- 在上图中, 有一个`vector<int> v`对象, 其成员变量存储在在了栈上, 包括`size`, `capacity`, `data pointer`,分别表示数组已经使用的大小、数组的容量、数组的首地址, 最左边表示初始时刻的堆栈状态,
- 某时刻调用`v.push_back(20)`, 检查发现此操作不会超出容量上限, 因此在中间的堆栈示意图中插入了20, 并更新控制结构中的`size = 2`
- 下一时刻调用`v.push_back(30)`, 此时检查发现此操作要求的容量不足, 因此需要重新在堆内存申请容量为4的内存空间, 如右边的示意图所示, 并且复制原来的内容到新的地址, 完成此操作后可以丢弃原来的堆内存空间, 并插入30

## 代码实现

### vector.h

```cpp
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

namespace mystl{
template <typename T>
class Vector
{
private:
    T *elements;    
    size_t capacity;    
    size_t size;    
    
public:
    
    Vector():elements(nullptr), capacity(0), size(0){};
    
    ~Vector()
    {
        delete[] elements; 
    }
    
    Vector(const Vector& other):capacity(other.capacity),size(other.size)
    {
        
        elements = new T[capacity];
        std::copy(other.elements, other.elements+size, elements);
    }
    
    Vector& operator=(const Vector& other)  
    {
        if(this != &other)  
        {
            delete[] elements;  
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements+size, elements);
        }
        return *this;  
    }
    void push_back(const T& value)
    {
       
        if(size == capacity)
        {
            reserve(capacity==0? 1:2*capacity);
        }
        elements[size++] = value;
    }
    size_t getSize() const
    {
        return size;
    }
    size_t getCapacity() const
    {
        return capacity;
    }
    T& operator[](size_t index)
    {
        if(index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }
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
    T* begin()
    {
        return elements;
    }
    T* end()
    {
        return elements+size;
    }
    const T* begin() const
    {
        return elements;
    }
    const T* end() const
    {
        return elements+size;
    }
    void printElements() const 
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
            T* newElements = new T[newCapacity];
            std::copy(elements,elements+size,newElements);
            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }
    }
    
};
}
```

### test.cpp

```cpp
#include "vector.h"
#include "list.h"
#include "deque.h"

void vectorTest()
{
    mystl::Vector<int> v1;
    v1.push_back(10);
    mystl::Vector<int> v2(v1);
    mystl::Vector<int> v3 = v2;
    for(int i = 0; i < 5; i++)
    {
        v3.push_back(i);
    }
    int size = v3.getSize();
    int cap = v3.getCapacity();
    int t = v3[3];
    std::cout << t << std::endl;
    v3.insert(2,88);
    v3.pop_back();
    int* ptr = v3.begin();
    v3.printElements();
    v3.clear();
}

int main()
{
    vectorTest();
    system("pause");
    return 0;
}
```

## 代码详解

### 变量

```cpp
T *elements;    // 指向动态数组的指针
size_t capacity;    // 数组的容量, size_t = unsigned int
size_t size;    // 数组中元素的个数
```

- elements： 指向动态数组的指针
- capacity：数组的容量, size_t = unsigned int
- size： 数组中元素的个数

###  构造函数

```cpp
Vector():elements(nullptr), capacity(0), size(0){};
```

构造函数：初始化Vector对象，默认设置指针悬空，容量设置为0，当前元素的数量也为0

### 析构函数

```cpp
  ~Vector()
  {
	delete[] elements; // elements是数组指针
  }
```

析构函数：销毁Vector对象，释放指针

### 拷贝构造

```cpp
Vector(const Vector& other):capacity(other.capacity),size(other.size)
{
    // 找一块地方开辟地址空间
    elements = new T[capacity];
    std::copy(other.elements, other.elements+size, elements);
}
```

拷贝构造函数，cap、size都默认和副本相同

`std::copy()`：

- 作用：从一个容器复制元素到另一个容器。
- std::copy需要三个参数：两个指定要复制的元素范围的迭代器（起始迭代器和结束迭代器），以及一个指向目标位置开始的迭代器。 
  指针也是一种天然的迭代器

### operator=

```cpp
    // 拷贝复制+运算符重载
    Vector& operator=(const Vector& other) 
    {
        
        {
            delete[] elements; 
            // 获取副本的数据
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            // 分配新内存，并复制所有元素
            std::copy(other.elements, other.elements+size, elements);
        }
        return *this; 
    }
```

- `if(this != &other)`：通过判断两个指针是否相同，检查是不是自赋值的情况
- `delete[] elements;`：删除这一块地址的数据、指针
- `return *this;`： 返回当前对象的引用

### push_back

```cpp
    // push_back函数
    void push_back(const T& value)
    {
        if(size == capacity)
        {
            reserve(capacity==0? 1:2*capacity);
        }
        elements[size++] = value;
    }
```

-  `if(size == capacity)`：如果内存将要溢出，则开辟更大的空间
- `reserve(capacity==0? 1:2*capacity);`：不能简单的将capacity容量翻倍, 需要考虑0的边界情况，如果是开始时刻，没有分配内存，则分配1块内存，否则内存空间加倍

### operator[]

下标操作符重载，允许通过下标访问Vector中的元素

```cpp
T& operator[](size_t index)
{
    // 如果指定的下标越界（大于或等于 size），则抛出 std::out_of_range 异常
    if(index >= size)
    {
    throw std::out_of_range("Index out of range");
    }
    return elements[index];
}
```

当 `int arr[] = { 99, 15, 100, 888, 252 }` 时，arr是指向数组首地址的指针。可以采用 `arr[i]` 的形式访问数组元素。如果 p 是指向数组 arr 的指针，那么也可以使用 p[i] 来访问数组元素，它等价于 `arr[i]`。因此，`elements[index]`等同于`vector v[index]`

### insert

```cpp

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
    for(size_t i = size; i>index;--i)
    {
    	elements[i] = elements[i-1];
    }
    elements[index] = value;
    ++size;
}
```

- 在 `Vector` 的指定位置 `index` 插入一个元素 `value`；
- 如果 `index` 大于 `size`，则抛出 `std::out_of_range` 异常；
- 如果当前没有足够的容量来存储新元素，则通过 `reserve` 函数扩展数组的容量；
- 将 `index` 之后的所有元素向后移动一个位置，为新元素腾出空间；
- 将新元素放置在 `index` 位置；
- 增加 `Vector` 的 `size`

```cpp
for(size_t i = size; i>index;--i)
{
	elements[i] = elements[i-1];
}
```

for循环执行顺序如图：

![image-20240521162919322](https://yzfzzz.oss-cn-shenzhen.aliyuncs.com/image/image-20240521162919322.png)

### printElements

```cpp
void printElements() const
{
    for(size_t i = 0; i<size; ++i)
    {
    	std::cout << elements[i] << " ";
    }
    std::cout << std::endl;
}
```

const 关键字在成员函数声明之后表示该函数不会修改类的任何成员变量

## 本实现版本 和 C++ STL标准库实现版本的区别：

内存分配策略不同、无范围检查和异常处理、只实现了一些基本的功能，例如插入、删除、访问元素等，而没有涵盖 `std::vector` 的所有功能和特性