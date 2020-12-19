//
//  TTBBSTree.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/19.
//

#ifndef TTBBSTree_hpp
#define TTBBSTree_hpp

#include "TTBSTree.hpp"
/*
 平衡二叉搜索树，具备旋转功能抽取相同功能
 */
template <class T>
class TTBBSTree: public TTBSTree<T> {
protected:
    //左旋转
    void rotateLeft(TTTreeNode<T> *grand) {
        TTTreeNode<T> *parent = grand->right;
        TTTreeNode<T> *child = parent->left;
        //有旋转
        grand->right = parent->left;
        parent->left = grand;
        //更新节点的父节点和高度
        afterRotate(grand, parent, child);
    }
    
    //右旋转
    void rotateRight(TTTreeNode<T> *grand) {
        TTTreeNode<T> *parent = grand->left;
        TTTreeNode<T> *child = parent->right;
        //有旋转
        grand->left = child;
        parent->right = grand;
        //更新节点的父节点和高度
        afterRotate(grand, parent, child);
    }
    
    virtual void afterRotate(TTTreeNode<T> *grand, TTTreeNode<T> *parent, TTTreeNode<T> *child) {
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
    }
    
public:
    //调用父类构造函数初始化
    TTBBSTree():TTBSTree<T>(nullptr) {}
    ~TTBBSTree() {}
};

#endif /* TTBBSTree_hpp */
