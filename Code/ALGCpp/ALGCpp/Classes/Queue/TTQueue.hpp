//
//  TTQueue.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/4.
//

#ifndef TTQueue_hpp
#define TTQueue_hpp

#include "TTLinkedList.hpp"

template <class T>
class TTQueue {
private:
    TTLinkedList<T> *linkedList;
public:
    TTQueue(T element) {
        linkedList = new TTLinkedList<T>();
        en_queue(element);
    }
    
    ~TTQueue() {
        delete linkedList;
    }
    
    int size() const {
        return linkedList->size();
    }
    
    bool isEmpty() const {
        return linkedList->isEmpty();
    }
    
    /// 出队
    T de_queue() {
        return linkedList->remove(0);
    }
    
    /// 入队
    void en_queue(const T &element) {
        linkedList->add(element);
    }
    
    /// 获取队头
    T front() {
        return linkedList->get(0);
    }
    
    void clear() {
        linkedList->clear();
    }
};

#endif /* TTQueue_hpp */
