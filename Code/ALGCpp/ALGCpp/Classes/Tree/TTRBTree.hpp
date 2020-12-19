//
//  TTRBTree.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/17.
//

#ifndef TTRBTree_hpp
#define TTRBTree_hpp

#include "TTBBSTree.hpp"

enum RBTNodeColor {
    RED = 0,
    BLACK = 1,
};

template<class T>
class RBTreeNode: public TTTreeNode<T> {
public:
    RBTNodeColor color = RED;
    RBTreeNode():TTTreeNode<T>(nullptr, nullptr) {}
    RBTreeNode(const T &x, TTTreeNode<T> *parent):TTTreeNode<T>(x, parent){}
};

/*
 红黑树
 满足红黑树的五大性质：
 1、
 2、
 3、
 4、
 5
 */
template <class T>
class TTRBTree: public TTBBSTree<T> {
private:
#pragma mark -------------- 节点染色辅助方法 ------------------------
    /// 对节点进行染色
    TTTreeNode<T> *color(TTTreeNode<T> *node, RBTNodeColor color) {
        if (node == nullptr) return node;
        ((RBTreeNode<T> *)node)->color = color;
        return node;
    }
    
    TTTreeNode<T> *red(TTTreeNode<T> *node) {
        return color(node, RED);
    }
    
    TTTreeNode<T> *black(TTTreeNode<T> *node) {
        return color(node, BLACK);
    }
    
    /// 判断节点颜色
    RBTNodeColor colorOf(TTTreeNode<T> *node) {
        return node == nullptr ? BLACK : ((RBTreeNode<T> *)node)->color;
    }
    
    bool isBlack(TTTreeNode<T> *node) {
        return colorOf(node) == BLACK;
    }
    
    bool isRed(TTTreeNode<T> *node) {
        return colorOf(node) == RED;
    }
protected:
    void afterAdd(TTTreeNode<T> *node) {
        TTTreeNode<T> *parent = node->parent;
        //添加的是根节点，直接染成黑色
        if (parent == nullptr) {
            black(node);
            return;
        }
        
        //如果父节点是黑色，不用做额外处理，直接返回
        if (isBlack(parent)) return;
        // uncle节点
        TTTreeNode<T> *uncle = parent->sibling();
        //祖父节点
        TTTreeNode<T> *grand = parent->parent;
        if (isRed(uncle)) { //叔父节点是红色
            black(parent);
            black(uncle);
            //递归调用
            afterAdd(red(grand));
            return;
        }
        
        //叔父节点不是红色
        if (parent->isLeftChild()) { // L
            if (node->isLeftChild()) { // LL
                black(parent);
                red(grand);
                TTBBSTree<T>::rotateRight(grand);
            } else { // LR
                TTBBSTree<T>::rotateLeft(grand);
                TTBBSTree<T>::rotateRight(grand);
            }
        } else { //R
            if (node->isLeftChild()) { //RL
                TTBBSTree<T>::rotateRight(grand);
                TTBBSTree<T>::rotateLeft(grand);
            } else { //RR
                black(parent);
                red(grand);
                TTBBSTree<T>::rotateLeft(grand);
            }
        }
    }
    
    void afterRemove(TTTreeNode<T> *node) {
        
    }
    
    TTTreeNode<T> *createNode(const T &element, TTTreeNode<T> *parent) {
        return new RBTreeNode<T>(element, parent);
    }
public:
    //调用父类构造函数初始化
    TTRBTree():TTBBSTree<T>() {}
    ~TTRBTree() {}
};

#endif /* TTRBTree_hpp */
