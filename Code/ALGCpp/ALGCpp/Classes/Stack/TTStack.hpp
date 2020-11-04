//
//  TTStack.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/2.
//

#ifndef TTStack_hpp
#define TTStack_hpp

#include <vector>

using namespace std;

template<class T>
class TTStack {
private:
    int m_size;
    vector<T> vecs;
public:
    TTStack();
    TTStack(T element);
    ~TTStack();
    bool isEmpty();
    T top();
    T pop();
    void push(T element);
};

template<class T>
TTStack<T>::TTStack() {
    
}

template<class T>
TTStack<T>::TTStack(T element) {
    push(element);
}

template<class T>
TTStack<T>::~TTStack() {
    if (m_size > 0) {
        vecs.clear();
    }
}

template<class T>
bool TTStack<T>::isEmpty() {
    return m_size == 0;
}

template<class T>
void TTStack<T>::push(T element) {
    vecs.push_back(element);
    m_size++;
}

template<class T>
T TTStack<T>::pop() {
    if (m_size == 0) { return NULL; }
    T element = vecs.pop_back();
    m_size--;
    return element;
}

template<class T>
T TTStack<T>::top() {
    if (m_size <= 0) return NULL;
    T element = vecs[m_size-1];
    return element;
}

#endif /* TTStack_hpp */
