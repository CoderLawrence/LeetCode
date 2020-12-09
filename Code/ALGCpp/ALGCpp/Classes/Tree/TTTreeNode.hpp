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
    /// 是否为叶子节点
    bool isLeaf() {
        return this->left == nullptr && this->right == nullptr;
    }
    
    ///是否为左子节点
    bool isLeftChild() {
        return this->parent != nullptr && this == this->parent->left;
    }
    
    ///是否为右子节点
    bool isRightChild() {
        return this->parent != nullptr && this == this->parent->right;
    }
};

#endif /* TTTreeNode_hpp */
