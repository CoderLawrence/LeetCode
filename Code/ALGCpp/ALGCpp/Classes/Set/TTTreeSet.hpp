//
//  TTTreeSet.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/22.
//

#ifndef TTTreeSet_hpp
#define TTTreeSet_hpp

#include <iostream>
#include "TTRBTree.hpp"

using namespace std;

template <class T>
class TTTreeSet {
private:
    TTRBTree<T> *m_tree;
public:
    TTTreeSet() {
        m_tree = new TTRBTree<T>();
    }
    
    ~TTTreeSet() {
        delete m_tree;
    }
    
    int size() {
        return m_tree->size();
    }
    
    bool isEmpty() {
        return m_tree->isEmpty();
    }
    
    void clear() {
        m_tree->clear();
    }
    
    bool contains(const T element) {
        return m_tree->contains(element);
    }
    
    void add(const T element) {
        m_tree->add(element);
    }
    
    void remove(const T element) {
        return m_tree->remove(element);
    }
    
    void traversal() {
        m_tree->inorderTraversal();
    }
};

#endif /* TTTreeSet_hpp */
