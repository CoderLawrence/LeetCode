//
//  AVLTree.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/30.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include "TTBSTree.hpp"

/*
 AVL树：自平衡二搜索叉树
 自平衡：自平衡就是左子树和右子树的高度相对接近
 */
template<class T>
class AVLTree: public TTBSTree<T> {
protected:
    void afterAdd(TTTreeNode<T> *root) {

    }
public:
    //调用父类构造函数初始化
    AVLTree():TTBSTree<T>(nullptr) {}
    ~AVLTree() {};
};

#endif /* AVLTree_hpp */
