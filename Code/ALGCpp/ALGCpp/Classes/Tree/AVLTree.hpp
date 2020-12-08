//
//  AVLTree.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/30.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <math.h>
#include "TTBSTree.hpp"

template<class T>
class AVLTreeNode: public TTTreeNode<T> {
public:
    int m_height = 0;
    AVLTreeNode():TTTreeNode<T>(NULL, NULL) {}
    AVLTreeNode(const T &x, TTTreeNode<T> *parent):TTTreeNode<T>(x, parent){}
    
    int balanceFactor() {
        int left_H = this->left == nullptr ? 0 : ((AVLTreeNode<T> *)this->left)->m_height;
        int right_H = this->right == nullptr ? 0 : ((AVLTreeNode<T> *)this->right)->m_height;
        return left_H - right_H;
    }
};

/*
 AVL树：自平衡二搜索叉树
 自平衡：自平衡就是左子树和右子树的高度相对接近
 */
template<class T>
class AVLTree: public TTBSTree<T> {
private:
    bool isBalanced(TTTreeNode<T> *node) {
        return abs(((AVLTreeNode<T> *)node)->balanceFactor()) <= 1;
    }
protected:
    void afterAdd(TTTreeNode<T> *node) {
        while ((node = node->parent) != nullptr) {
            //判断是否平衡
            if (isBalanced(node)) {
                
            } else {
                
            }
        }
    }
    
    TTTreeNode<T> *createNode(const T &element, TTTreeNode<T> *parent) {
        return new AVLTreeNode<T>(element, parent);
    }
public:
    //调用父类构造函数初始化
    AVLTree():TTBSTree<T>(nullptr) {}
    ~AVLTree() {};
};

#endif /* AVLTree_hpp */
