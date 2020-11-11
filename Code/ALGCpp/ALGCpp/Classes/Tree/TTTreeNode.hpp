//
//  TTTreeNode.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/11.
//

#ifndef TTTreeNode_hpp
#define TTTreeNode_hpp

template <T>
class TTTreeNode {
public:
    T data;
    TTTreeNode<T> *left;
    TTTreeNode<T> *right;
    TTTreeNode(const T &x): data(T),
                            left(NULL),
                            right(NULL) {}
};

#endif /* TTTreeNode_hpp */
