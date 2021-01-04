//
//  TTBinaryHeap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2021/1/4.
//

#ifndef TTBinaryHeap_hpp
#define TTBinaryHeap_hpp

#include "TTHeap.hpp"

template <class T>
class TTBinaryHeap: public TTHeap<T> {
private:
    T *m_data;
    int m_size = 0;
    int m_capacity = 0;
    static constexpr int DEFUALT_CAPACITY = 10;
    
    /// e1 > e2  >> 1；e1 == e2 >> 0；e1 < e2 >> -1
    int compare(const T &e1, const T &e2) {
        return e1 > e2 ? 1 : e1 == e2 ? 0 : -1;
    }
    
    void emptyCheck() {
        if (m_size == 0) {
            throw out_of_range("TTBinaryHeap:: heap is empty");
        }
    }
    
    void ensureCapacity(const int capacity) {
        int oldCapacity = m_capacity;
        if (oldCapacity >= capacity) return;
        int newCapacity = oldCapacity + (oldCapacity >> 1);
        T *newElements =  new T[newCapacity];
        for (int i = 0; i < m_size; i++) {
            newElements[i] = m_data[i];
        }
        
        m_data = newElements;
        m_capacity = newCapacity;
    }
public:
    TTBinaryHeap() {
        m_capacity = DEFUALT_CAPACITY;
        m_data = new T[m_capacity];
    }
    
    ~TTBinaryHeap() {
        clear();
        delete [] m_data;
    }
    
    /// 获取堆大小
    int size() const {
        return m_size;
    }
    
    /// 判断堆是否为空
    bool isEmpty() const {
        return m_size == 0;
    }
    
    /// 添加元素
    void add(const T &element) {
        ensureCapacity(m_size + 1);
        m_data[0] = element;
        m_size++;
    }
    
    /// 获取对顶元素
    T get() {
        emptyCheck();
        return m_data[0];
    }
    
    /// 删除堆顶元素
    void remove() {
        m_data[0] = NULL;
    }
    
    void clear () {
        for (int i = 0; i < m_size; i++) {
            m_data[i] = NULL;
        }
        
        m_size = 0;
    }
};

#endif /* TTBinaryHeap_hpp */
