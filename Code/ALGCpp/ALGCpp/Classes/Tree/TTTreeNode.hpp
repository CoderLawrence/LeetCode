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
    
    /// 获得兄弟节点
    TTTreeNode<T> *sibling() {
        //如果是父节点的左子节点，那么兄弟节点为父节点的右节点
        if (isLeftChild()) {
            return this->parent->right;
        } else if (isRightChild()) { //与上面相反
            return this->parent->left;
        }
        
        return nullptr;
    }
};

#endif /* TTTreeNode_hpp */
