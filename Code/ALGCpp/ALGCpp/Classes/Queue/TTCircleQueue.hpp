//
//  TTCircleQueue.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/6.
//

#ifndef TTCircleQueue_hpp
#define TTCircleQueue_hpp

#include <iostream>

using namespace std;

/// 循环队列，支持动态扩容
template <class T>
class TTCircleQueue {
private:
    int m_front = 0;
    int m_size = 0;
    /// 数组容量
    int m_capacity = 10;
    /// 指向数组的指针，不安全，需要替换
    T *m_elements;
    
    int index(int index) const {
        index += m_front;
        if (index < 0) {
            return index + m_capacity;
        }
        
        return index - (index >= m_capacity ? m_capacity : 0);
    }
    
    int rearIndex() const {
        return index(m_size - 1);
    }
    
    void ensureCapacity(const int capacity) {
        int oldCapacity = m_capacity;
        if (oldCapacity >= capacity) return;
        int newCapacity = oldCapacity + (oldCapacity >> 1);
        T *newElements = (T*)malloc(newCapacity * sizeof(T));
        for (int i = 0; i < m_size; i++) {
            newElements[i] = m_elements[index(i)];
        }
        
        m_elements = newElements;
        m_capacity = newCapacity;
        m_front = 0;
    }
public:
    TTCircleQueue() {
        T *elements = (T*)malloc(m_capacity * sizeof(T));
        m_elements = elements;
        m_front = 0;
        m_size = 0;
    }
    
    ~TTCircleQueue() {
        clear();
    }
    
    int size() const {
        return m_size;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void en_queue_rear(const T &element) {
        ensureCapacity(m_size + 1);
        m_elements[index(m_size)] = element;
        m_size++;
    }
    
    T de_queue_rear() {
        int rear = index(m_size - 1);
        T ele = m_elements[rear];
        m_elements[rear] = NULL;
        m_size--;
        return ele;
    }
    
    void en_queue_front(const T &element) {
        ensureCapacity(m_size + 1);
        m_front = index(-1);
        m_elements[m_front] = element;
        m_size++;
    }
    
    T de_queue_front() {
        T ele = m_elements[m_front];
        m_elements[m_front] = NULL;
        m_front = index(1);
        m_size--;
        return ele;
    }
    
    T front() const {
        return m_elements[m_front];
    }
    
    T rear() const {
        return m_elements[m_size - 1];
    }
    
    void clear() {
        m_size = 0;
        m_front = 0;
        if (m_elements != nullptr) {
            free(m_elements);
            m_elements = nullptr;
        }
    }
};

#endif /* TTCircleQueue_hpp */
