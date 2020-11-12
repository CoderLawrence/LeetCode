//
//  TTBSTree.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/12.
//

#ifndef TTBSTree_hpp
#define TTBSTree_hpp

#include "TTTreeNode.hpp"

/// 二叉搜索树，目前使用基本数类型作为实例
/// 如果其他数据类型需要进行比较必须要重载运算符
/// 二叉搜索树的特点：
/// 1、任意一个节点的值都大于器左子树所有节点的值
/// 2、任意一个节点的值都小于其右子树所有节点的值
/// 3、它的左右子树也是一颗二叉搜索树
/// 4、二叉搜索树存储的元素必须具备可比较性
template <class T>
class TTBSTree {
private:
    int m_size;
    TTTreeNode<T> *m_root;
    void elementNotNullCheck(const T &element) {
        if (element == NULL) {
            throw "element was masut not null";
        }
    }
public:
    TTBSTree() {
        
    }
    
    ~TTBSTree() {
        
    }
    
    int size() const {
        return m_size;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void clear() {
        
    }
    
    void add(const T &element) {
        elementNotNullCheck(element);
        //根节点为空
        if (m_root == NULL) {
            m_root = new TTTreeNode<T>(element, NULL);
            m_size++;
            return;
        }
        
        //添加的不是第一个节点
    }
    
    void remove(const T &element) {
        
    }
    
    bool contains(const T &element) {
        
    }
};

#endif /* TTBSTree_hpp */
