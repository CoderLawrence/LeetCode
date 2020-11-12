//
//  TTTreeNode.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/11.
//

#ifndef TTTreeNode_hpp
#define TTTreeNode_hpp

#include <iostream>

using namespace std;

template <class T>
class TTTreeNode {
public:
    T element;
    TTTreeNode<T> *left;
    TTTreeNode<T> *right;
    TTTreeNode<T> *parent;
    TTTreeNode():TTTreeNode(NULL, NULL) {}
    TTTreeNode(const T &x, TTTreeNode<T> *parent):
        element(x), left(NULL), right(NULL), parent(parent) {}
    void log() {
        cout << "element->" << element << ", right->" << right << ", left->" << left << endl;
    }
};

#endif /* TTTreeNode_hpp */
