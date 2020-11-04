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
        linkedList->clear();
        delete linkedList;
    }
    
    int size() const {
        return linkedList->size();
    }
    
    bool isEmpty() const {
        return linkedList->isEmpty();
    }
    
    T de_queue() {
        return linkedList->remove();
    }
    
    void en_queue(T element) {
        linkedList->add(element);
    }
    
    T front() {
        return NULL;
    }
    
    void clear() {
        linkedList->clear();
    }
};

#endif /* TTQueue_hpp */
