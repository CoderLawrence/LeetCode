//
//  TTListSet.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/16.
//

#ifndef TTListSet_hpp
#define TTListSet_hpp

#include <iostream>
#include "TTLinkedList.hpp"

using namespace std;

template <class T>
class TTListSet {
private:
    TTLinkedList<T> *m_list;
public:
    TTListSet() {
        m_list = new TTLinkedList<T>();
    }
    
    ~TTListSet() {
        delete m_list;
    }
    
    int size() {
        return m_list->size();
    }
    
    bool isEmpty() {
        return m_list->isEmpty();
    }
    
    void clear() {
        m_list->clear();
    }
    
    bool contains(const T element) {
        return m_list->indexOf(element) != TTLinkedList<T>::ELEMENT_NOT_FOUND;
    }
    
    void add(const T element) {
        int index = m_list->indexOf(element);
        if (index != TTLinkedList<T>::ELEMENT_NOT_FOUND) {
            m_list->set(index, element);
            return;
        }
        
        m_list->add(element);
    }
    
    void remove(const T element) {
        m_list->remove(element);
    }
    
    void traversal() {
        for (int i = 0; i < m_list->size(); i++) {
            cout << m_list->get(i) << endl;
        }
    }
};

#endif /* TTListSet_hpp */
