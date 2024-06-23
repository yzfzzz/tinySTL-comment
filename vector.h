#pragma once
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

/*
    ���һ�� Vector �࣬����Ӧ�߱����¹��ܺ����ԣ�
    1��������Ա������
    ���캯������ʼ�� Vector ʵ��
    ����������������Դ��ȷ�����ڴ�й¶
    �������캯��������ͨ�����е� MyVector ʵ��������һ����ʵ��
    ������ֵ��������ʵ�� MyVector ʵ��֮��ĸ�ֵ����

    2�����Ĺ��ܣ�
    ���Ԫ�ص�ĩβ�������� Vector ��ĩβ�����Ԫ��
    ��ȡԪ�ظ��������� Vector ��ǰ������Ԫ������
    ��ȡ���������� Vector �������ɵ�Ԫ������
    ����ָ����������Ԫ�أ�ͨ�����������ض�λ�õ�Ԫ��
    ��ָ��λ�ò���Ԫ�أ��� Vector ���ض�λ�ò���һ����Ԫ��
    ɾ������ĩβԪ�أ��Ƴ� Vector ĩβ��Ԫ��
    ������飺ɾ�� Vector �е�����Ԫ�أ�������״̬

    3�������������
    ʹ�õ�����������ʵ�ֵ�������֧�ֶ� Vector �ӿ�ʼλ�õ�����λ�õı���
    ��������ӡ����Ԫ�أ��ṩһ��������ͨ����������������ӡ������Ԫ��

    4���߼����ԣ�
    �������ݣ���ǰ�������������ɸ���Ԫ��ʱ���Զ���չ Vector �������Դ洢����Ԫ��
*/

namespace mystl{
template <typename T>
class Vector
{
private:
    T *elements;    // ָ��̬�����ָ��
    size_t capacity;    // ���������, size_t = unsigned int
    size_t size;    // ������Ԫ�صĸ���
    
public:
    // ���캯������ʼ��Vector����Ĭ������ָ�����գ���������Ϊ0����ǰԪ�ص�����ҲΪ0
    Vector():elements(nullptr), capacity(0), size(0){};
    //  ��������������Vector�����ͷ�ָ��
    ~Vector()
    {
        delete[] elements; // elements������ָ��
    }
    // �������캯����cap��size��Ĭ�Ϻ͸�����ͬ
    Vector(const Vector& other):capacity(other.capacity),size(other.size)
    {
        // ��һ��ط����ٵ�ַ�ռ�
        elements = new T[capacity];
        /* 
            ���ã���һ����������Ԫ�ص���һ��������std::copy��Ҫ����������
            ����ָ��Ҫ���Ƶ�Ԫ�ط�Χ�ĵ���������ʼ�������ͽ��������������Լ�һ��ָ��Ŀ��λ�ÿ�ʼ�ĵ������� 
            ָ��Ҳ��һ����Ȼ�ĵ�����
        */
        std::copy(other.elements, other.elements+size, elements);
    }
    // ��������+���������
    Vector& operator=(const Vector& other)  // ��vector����ǿתΪ����
    {
        if(this != &other)  // ͨ���ж�����ָ���Ƿ���ͬ������ǲ����Ը�ֵ�����
        {
            delete[] elements;  // ɾ����һ���ַ�����ݡ�ָ��
            // ��ȡ����������
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            // �������ڴ棬����������Ԫ��
            std::copy(other.elements, other.elements+size, elements);
        }
        return *this;  // ���ص�ǰ���������
    }
    // push_back����
    void push_back(const T& value)
    {
        // ����ڴ潫Ҫ������򿪱ٸ���Ŀռ�
        if(size == capacity)
        {
            // ���ܼ򵥵Ľ�capacity��������, ��Ҫ����0�ı߽����
            // ����ǿ�ʼʱ�̣�û�з����ڴ棬�����1���ڴ棬�����ڴ�ռ�ӱ�
            reserve(capacity==0? 1:2*capacity);
        }
        elements[size++] = value;
    }
    // ����Vector�е�Ԫ������
    size_t getSize() const
    {
        return size;
    }
    // ����Vector������
    size_t getCapacity() const
    {
        return capacity;
    }
    // �±���������أ�����ͨ���±����Vector�е�Ԫ��
    T& operator[](size_t index)
    {
        // ���ָ�����±�Խ�磨���ڻ���� size�������׳� std::out_of_range �쳣
        if(index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        /*
            �� int arr[] = { 99, 15, 100, 888, 252 } ʱ��arr��ָ�������׵�ַ��ָ�롣���Բ��� arr[i] ����ʽ��������Ԫ�ء�
            ��� p ��ָ������ arr ��ָ�룬��ôҲ����ʹ�� p[i] ����������Ԫ�أ����ȼ��� arr[i]
        */ 
        return elements[index];
    }
    // insert����
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
        // ����Ԫ�غ���
        for(size_t i = size; i>index;--i)  // TODO:Ϊʲô����i--��
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
    // �� const �汾����ָ�� elements ��ָ�룬���������޸� Vector �е�Ԫ��
    T* begin()
    {
        return elements;
    }
    T* end()
    {
        return elements+size;
    }
    // const �汾���� const ָ�룬����ֻ������
    const T* begin() const
    {
        return elements;
    }
    const T* end() const
    {
        return elements+size;
    }
    void printElements() const // const �ؼ����ڳ�Ա��������֮���ʾ�ú��������޸�����κγ�Ա����
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
            // �������ط���һ���ռ�
            T* newElements = new T[newCapacity];
            // ��Ԫ�ؿ�����ȥ
            std::copy(elements,elements+size,newElements);
            // �ͷž��ڴ�
            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }
    }
    
};
}
