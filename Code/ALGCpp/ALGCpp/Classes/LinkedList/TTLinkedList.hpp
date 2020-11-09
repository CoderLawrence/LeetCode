//
//  TTLinkedList.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/4.
//

#ifndef TTLinkedList_hpp
#define TTLinkedList_hpp

#include <iostream>
#include <set>

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

/// 双向链表
template <class T>
class TTLinkedList {
private:
    const int ELEMENT_NOT_FOUND = -1;
    
    int m_size;
    TTNode<T> *first;
    TTNode<T> *last;
    
    void rangeCheck(int index) {
        if (m_size < 0 || index >= m_size) {
            outOfBounds(index);
        }
    }
    
    void rangeCheckForAdd(int index) {
        if (m_size < 0 || index > m_size) {
            outOfBounds(index);
        }
    }
    
    void outOfBounds(int index) {
        throw string("outOfBounds index %d", index);
    }
    
    TTNode<T> *getNode(const int index) {
        rangeCheck(index);
        if (index < (m_size >> 1)) { //如果索引小于size的一半，从头开始查找
            TTNode<T> *node = first;
            for (int i = 0; i < index; i++) {
                node = node->next;
            }
            
            return node;
        } else { //从尾部开始查找
            TTNode<T> *node = last;
            for (int i = m_size - 1; i > index; i--) {
                node = node->prev;
            }
            
            return node;
        }
    }
    
public:
    TTLinkedList() {}
    ~TTLinkedList() {
        clear();
    }
    
    int size() const {
        return m_size;
    }
    
    void add(const T &element) {
        TTNode<T> *node = new TTNode<T>(NULL, element, NULL);
        if (m_size == 0) {
            first = node;
            last = first;
        } else {
            TTNode<T> *curr = last;
            node->prev = curr;
            curr->next = node;
            last = node;
        }
        
        m_size++;
    }
    
    void add(const int index, const T &element) {
        rangeCheckForAdd(index);
        if (index == m_size) { //往末尾添加元素
            TTNode<T> *oldLast = last;
            last = new TTNode<T>(oldLast, element, NULL);
            if (first == NULL) { //这是链表添加的第一个元素
                first = last;
            } else {
                oldLast->next = last;
            }
        } else {
            TTNode<T> *next = getNode(index);
            TTNode<T> *prev = next->prev;
            TTNode<T> *node = new TTNode<T>(prev, element, next);
            if (prev == NULL) {
                first = node;
            } else {
                prev->next = node;
            }
        }
        
        m_size++;
    }
    
    T get(const int index) {
        return getNode(index)->data;
    }
    
    T set(const int index, const T &element) {
        TTNode<T> *node = getNode(index);
        T oldElement = node->data;
        node->data = element;
        return oldElement;
    }
    
    T remove(const int index) {
        rangeCheck(index);
        TTNode<T> *node = getNode(index);
        TTNode<T> *prev = node->prev;
        TTNode<T> *next = node->next;
        if (prev == NULL) {
            first = next;
        } else {
            prev->next = next;
        }
        
        if (next == NULL) {
            last = prev;
        } else {
            next->prev = prev;
        }
        
        T element = node->data;
        delete node;
        m_size--;
        return element;
    }
    
    T remove() {
        return remove(m_size);
    }
    
    int indexOf(const T &element) {
        TTNode<T> *node = first;
        for (int i = 0; i < m_size; i++) {
            if (node->data == element) return i;
            node = node->next;
        }
        
        return ELEMENT_NOT_FOUND;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void clear() {
        if (first == NULL) return;
        for (TTNode<T> *x = first; x != NULL;) { //断开所有节点，回收内存
            TTNode<T> *next = x->next;
            x->data = NULL;
            x->next = NULL;
            x->prev = NULL;
            delete x;
            x = next;
        }
        
        first = last = NULL;
        m_size = 0;
    }
};

#endif /* TTLinkedList_hpp */
