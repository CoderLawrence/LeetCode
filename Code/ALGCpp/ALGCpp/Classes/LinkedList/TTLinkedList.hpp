//
//  TTLinkedList.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/4.
//

#ifndef TTLinkedList_hpp
#define TTLinkedList_hpp

#include <iostream>

using namespace std;

template <class T>
class TTNode {
public:
    T data;
    TTNode<T> *next;
    TTNode<T> *prev;
    TTNode():TTNode(NULL, NULL, NULL) {}
    TTNode(TTNode<T> *prev, T data, TTNode<T> *next):
        prev(prev),data(data), next(next) {}
    
    ~TTNode() {
        cout << "TTNode::~TTNode()->data:" << data << endl;
    }
};

template <class T>
class TTLinkedList {
private:
    int m_size;
    TTNode<T> *first;
    TTNode<T> *last;
public:
    int size() const {
        return m_size;
    }
    
    void add(T element) {
        TTNode<T> *node = new TTNode<T>(NULL, element, NULL);
        if (m_size == 0) {
            first = node;
            last = first;
        } else {
            TTNode<T> *curr = last;
            node->prev = curr;
            curr->next = node;
        }
        
        m_size++;
    }
    
    void add(int index, T element) {
        
    }
    
    T remove(int index) {
        return NULL;
    }
    
    T remove() {
        return NULL;
    }
    
    int indexOf(T element) {
        int index = 0;
        TTNode<T> curr = first;
        if (curr->data == element) {
            return index;
        } else {
            while (curr != NULL) {
                index++;
                curr = curr->next;
            }
        }
        
        return -1;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void clear() {
        first = NULL;
        last = NULL;
    }
};

#endif /* TTLinkedList_hpp */
