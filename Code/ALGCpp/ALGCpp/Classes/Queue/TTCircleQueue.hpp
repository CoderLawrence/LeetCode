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

/// 循环队列
template <class T>
class TTCircleQueue {
private:
    int m_front;
    int m_size;
    T *m_elements;
public:
    TTCircleQueue() {
        T elements[10] = {NULL};
        m_elements = elements;
        m_front = 0;
        m_size = 0;
    }
    
    ~TTCircleQueue() {
        
    }
    
    int size() const {
        return m_size;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void en_queue_rear(const T &element) {
        
    }
    
    T de_queue_rear() {
        
    }
    
    void en_queue_front(const T &element) {
        *(m_elements + m_front) = element;
       // m_elements = {};
        m_front++;
        m_size++;
    }
    
    T de_queue_front() {
        
    }
    
    T front() const {
        return *m_elements;
    }
    
    T rear() const {
        return m_elements[m_size - 1];
    }
    
    void clear() const {
//        elements.clear();
        m_size = 0;
        m_front = 0;
    }
};

#endif /* TTCircleQueue_hpp */
