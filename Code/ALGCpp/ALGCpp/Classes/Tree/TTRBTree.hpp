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
        if (isRed(uncle)) { //叔父节点是红色【B树节点上益】
            black(parent);
            black(uncle);
            //递归调用
            afterAdd(red(grand));
            return;
        }
        
        //叔父节点不是红色
        if (parent->isLeftChild()) { // L
            red(grand);
            if (node->isLeftChild()) { // LL
                black(parent);
                //有旋转祖父节点，放到下面统一处理
            } else { // LR
                //自己染成黑色，父节点染成红色
                black(node);
                TTBBSTree<T>::rotateLeft(parent);
            }
            //祖父节点右旋
            TTBBSTree<T>::rotateRight(grand);
        } else { //R
            red(grand);
            if (node->isLeftChild()) { //RL
                black(node);
                TTBBSTree<T>::rotateRight(parent);
                
            } else { //RR
                black(parent);
                //有旋转祖父节点，放到下面统一处理
            }
            //祖父节点左旋
            TTBBSTree<T>::rotateLeft(grand);
        }
    }
    
    void afterRemove(TTTreeNode<T> *node) {
        //如果删除的节点是红色
        //或者用以删除节点的子节点是红色
        if (isRed(node)) {
            black(node);
            return;
        }
        
        TTTreeNode<T> *parent = node->parent;
        //删除的是根节点
        if (parent == nullptr) return;
        //删除的是黑色叶子节点【下益】
        //判断被删除的node是左还是右
        bool left = parent->left == nullptr || node->isLeftChild();
        TTTreeNode<T> *sibling = left ? parent->right : parent->left;
        if (left) { //被删除的节点再左边，兄弟节点在右边
            if (isRed(sibling)) {
                black(sibling);
                red(parent);
                TTBBSTree<T>::rotateLeft(parent);
                //更换兄弟
                sibling = parent->right;
            }
            
            //兄弟节点必然是黑色
            if (isBlack(sibling->left) && isBlack(sibling->right)) {
                //兄弟节点没有1个红色节点，父节点要向下跟兄弟节点合并
                bool parentBlack = isBlack(parent);
                black(parent);
                red(sibling);
                if (parentBlack) {
                    afterRemove(parent);
                }
            } else { //兄弟节点至少有1个红色节点，向兄弟节点借元素
                //兄弟节点的左边是黑色，兄弟要先旋转
                if (isBlack(sibling->right)) {
                    TTBBSTree<T>::rotateRight(sibling);
                    sibling = parent->right;
                }
                
                color(sibling, colorOf(parent));
                black(sibling->right);
                black(parent);
                TTBBSTree<T>::rotateLeft(sibling);
            }
        } else { //被删除的节点在右边，兄弟节点在左边
            if (isRed(sibling)) { //兄弟节点是红色
                black(sibling);
                red(parent);
                TTBBSTree<T>::rotateRight(parent);
                //更换兄弟
                sibling = parent->left;
            }
            
            //兄弟节点必然是黑色
            if (isBlack(sibling->left) && isBlack(sibling->right)) {
                //兄弟节点没有1个红色节点，父节点要向下跟兄弟节点合并
                bool parentBlack = isBlack(parent);
                black(parent);
                red(sibling);
                if (parentBlack) {
                    afterRemove(parent);
                }
            } else { //兄弟节点至少有一个红色子节点，向兄弟节点借元素
                //兄弟节点的左边是黑色，兄弟要先旋转
                if (isBlack(sibling->left)) {
                    TTBBSTree<T>::rotateLeft(sibling);
                    sibling = parent->left;
                }
                
                color(sibling, colorOf(parent));
                black(sibling->left);
                black(parent);
                TTBBSTree<T>::rotateRight(parent);
            }
        }
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
