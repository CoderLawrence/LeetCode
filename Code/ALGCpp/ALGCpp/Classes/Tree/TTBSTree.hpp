//
//  TTBSTree.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/12.
//

#ifndef TTBSTree_hpp
#define TTBSTree_hpp

#include "TTTreeNode.hpp"

template <class T>
class TTBSTComparator {
public:
    ///纯虚函数，子类重写
    virtual int compare(const T &e1, const T &e2) = 0;
};

template <class T>
class TTBSTComparable {
public:
    virtual int compareTo(const T &e) = 0;
};

class TTBSTDefaultComparator: public TTBSTComparator<int> {
public:
    int compare(const int &e1, const int &e2) {
        return e1 - e2;
    }
};

/// 二叉搜索树，目前使用基本数类型作为实例
/// 如果其他数据类型需要进行比较必须要重载运算符
/// 二叉搜索树的特点：
/// 1、任意一个节点的值都大于其左子树所有节点的值
/// 2、任意一个节点的值都小于其右子树所有节点的值
/// 3、它的左右子树也是一颗二叉搜索树
/// 4、二叉搜索树存储的元素必须具备可比较性
template <class T>
class TTBSTree {
private:
    int m_size;
    TTTreeNode<T> *m_root;
    /// 比较器，支持自定义
    TTBSTComparator<T> *m_comparator;
    
    void elementNotNullCheck(const T &element) {
        //代码执行没有问题，目前所学c++知识还不能理解这样处理是否正确，后续优化
        if (element == is_null_pointer<T>()) {
            throw invalid_argument("TTBSTree::add() element can't be null");
        }
    }
    
    /// 比价节点的值：e1 = e2 返回0，e1 > e2 放回1， e1 < e2 返回 -1
    /// @param e1 节点的值
    /// @param e2 节点的值
    int compare(const T &e1, const T &e2) const {
        if (m_comparator != nullptr) {
            return m_comparator->compare(e1, e2);
        }
        
        return e1 - e2;
    }
    
    /// 前序遍历，遍历根节点，然后接着先访问左子树访问完成后再访问右子树
    /// @param node 开始遍历子树的节点
    void preorderTraversal(TTTreeNode<T> *node) {
        if (node == nullptr) return;
        cout << node->element << endl;
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
    
    void inorderTraversal(TTTreeNode<T> *node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->element << endl;
        inorderTraversal(node->right);
    }
    
    void postorderTraversal(TTTreeNode<T> *node) {
        if (node == nullptr) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->element << endl;
    }
public:
    TTBSTree(TTBSTComparator<T> *x):
        m_comparator(x), m_root(nullptr), m_size(0) {}
    
    TTBSTree():TTBSTree(nullptr) {}
    
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
        if (m_root == nullptr) {
            m_root = new TTTreeNode<T>(element, nullptr);
            m_size++;
            return;
        }
        
        //添加的不是第一个节点
        int cmp = 0;
        TTTreeNode<T> *parent = nullptr;
        TTTreeNode<T> *node = m_root;
        //查找合适节点
        while (node != nullptr) {
            cmp = compare(element, node->element);
            parent = node;
            if (cmp > 0) {
                node = node->right;
            } else if (cmp < 0) {
                node = node->left;
            } else {
                //如果是两个值相等则更新为最新的值
                node->element = element;
                return;
            }
        }
        
        //根据比较的值插入叶子节点
        if (cmp > 0) {
            parent->right = new TTTreeNode<T>(element, parent);
        } else {
            parent->left = new TTTreeNode<T>(element, parent);
        }
        
        m_size++;
    }
    
    void remove(const T &element) {
        
    }
    
    bool contains(const T &element) {
        
    }
    
    /// 前序遍历，先访问左子树访问完成后再访问右子树
    void preorderTraversal() {
        preorderTraversal(m_root);
    }
    
    ///中序遍历，先访问左子树，再访问根节点，然后再访问右子树
    void inorderTraversal() {
        inorderTraversal(m_root);
    }
    
    ///中序遍历，先访问左子树，再访问右子树，然后再访问根节点
    void postorderTraversal() {
        postorderTraversal(m_root);
    }
};

#endif /* TTBSTree_hpp */
