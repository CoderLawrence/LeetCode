//
//  TTRBTree.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/17.
//

#ifndef TTRBTree_hpp
#define TTRBTree_hpp

#include "TTBSTree.hpp"

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
class TTRBTree: public TTBSTree<T> {
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
        color(node, RED);
    }
    
    void afterRemove(TTTreeNode<T> *node) {
        
    }
    
    TTTreeNode<T> *createNode(const T &element, TTTreeNode<T> *parent) {
        return new RBTreeNode<T>(element, parent);
    }
public:
    //调用父类构造函数初始化
    TTRBTree():TTBSTree<T>(nullptr) {}
    ~TTRBTree() {}
};

#endif /* TTRBTree_hpp */
