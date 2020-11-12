//
//  TTTreeNode.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/11.
//

#ifndef TTTreeNode_hpp
#define TTTreeNode_hpp

template <class T>
class TTTreeNode {
public:
    T data;
    TTTreeNode<T> *left;
    TTTreeNode<T> *right;
    TTTreeNode<T> *parent;
    TTTreeNode():TTTreeNode(NULL, NULL) {}
    TTTreeNode(const T &x, TTTreeNode<T> *parent):
            data(x), left(NULL), right(NULL), parent(parent) {}
};

#endif /* TTTreeNode_hpp */
