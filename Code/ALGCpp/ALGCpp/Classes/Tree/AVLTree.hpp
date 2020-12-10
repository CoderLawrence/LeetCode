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
    int m_height = 1;
    AVLTreeNode():TTTreeNode<T>(NULL, NULL) {}
    AVLTreeNode(const T &x, TTTreeNode<T> *parent):TTTreeNode<T>(x, parent){}
    
    int balanceFactor() {
        int left_H = this->left == nullptr ? 0 : ((AVLTreeNode<T> *)this->left)->m_height;
        int right_H = this->right == nullptr ? 0 : ((AVLTreeNode<T> *)this->right)->m_height;
        return left_H - right_H;
    }
    
    void updateHeight() {
        int left_H = this->left == nullptr ? 0 : ((AVLTreeNode<T> *)this->left)->m_height;
        int right_H = this->right == nullptr ? 0 : ((AVLTreeNode<T> *)this->right)->m_height;
        m_height = max(left_H, right_H) + 1;
    }
    
    //获取高度最高的节点
    TTTreeNode<T> *tallerChild() {
        int left_H = this->left == nullptr ? 0 : ((AVLTreeNode<T> *)this->left)->m_height;
        int right_H = this->right == nullptr ? 0 : ((AVLTreeNode<T> *)this->right)->m_height;
        if (left_H > right_H) return this->left;
        if (left_H < right_H) return this->right;
        //如果是高度相当，那么返回跟节点同方向的子节点
        return this->isLeftChild() ? this->left : this->right;
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
        //求绝对值
        return abs(((AVLTreeNode<T> *)node)->balanceFactor()) <= 1;
    }
    
    void updateHeight(TTTreeNode<T> *node) {
        ((AVLTreeNode<T> *)node)->updateHeight();
    }
    
    //恢复平衡，高度最低的不平衡节点
    void rebalanceNode(TTTreeNode<T> *grand) {
        TTTreeNode<T> *parent = ((AVLTreeNode<T> *)grand)->tallerChild();
        TTTreeNode<T> *node = ((AVLTreeNode<T> *)parent)->tallerChild();
        //如果父节点为左子树
        if (parent->isLeftChild()) { //L
            if (node->isLeftChild()) { //LL
                rotateRight(grand);
            } else { //LR
                rotateLeft(parent);
                rotateRight(grand);
            }
        } else { //R
            if (node->isLeftChild()) { //RL
                rotateRight(parent);
                rotateLeft(grand);
            } else { //RR
                rotateLeft(grand);
            }
        }
    }
    
    //左旋转
    void rotateLeft(TTTreeNode<T> *grand) {
        TTTreeNode<T> *parent = grand->right;
        TTTreeNode<T> *child = parent->left;
        //有旋转
        grand->right = parent->left;
        parent->left = grand;
        //更新父节点的子节点的指向
        parent->parent = grand->parent;
        if (grand->isLeftChild()) {
            grand->parent->left = parent;
        } else if (grand->isRightChild()) {
            grand->parent->right = parent;
        } else { //grand是root节点
            TTBSTree<T>::updateRoot(parent);
        }
        
        if (child != nullptr) {
            child->parent = grand;
        }
        
        grand->parent = parent;
        //更新高度
        updateHeight(grand);
        updateHeight(parent);
    }
    
    //右旋转
    void rotateRight(TTTreeNode<T> *grand) {
        TTTreeNode<T> *parent = grand->left;
        TTTreeNode<T> *child = parent->right;
        //有旋转
        grand->left = child;
        parent->right = grand;
        //更新父节点的子节点的指向
        parent->parent = grand->parent;
        if (grand->isLeftChild()) {
            grand->parent->left = parent;
        } else if (grand->isRightChild()) {
            grand->parent->right = parent;
        } else {
            TTBSTree<T>::updateRoot(parent);
        }
        
        if (child != nullptr) {
            child->parent = grand;
        }
        
        grand->parent = parent;
        //更新高度
        updateHeight(grand);
        updateHeight(parent);
    }
    
protected:
    void afterAdd(TTTreeNode<T> *node) {
        while ((node = node->parent) != nullptr) {
            //判断是否平衡
            if (isBalanced(node)) {
                //如果已经是平衡则直接更新节点高度即可
                updateHeight(node);
            } else {
                //再平衡，也就是第一个不平横的节点
                rebalanceNode(node);
                //只要找到第一个不平衡的节点让其恢复平衡，那么整棵树就恢复平衡
                break;
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
