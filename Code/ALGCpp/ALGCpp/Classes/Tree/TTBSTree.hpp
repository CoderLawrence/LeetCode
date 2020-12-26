//
//  TTBSTree.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/12.
//

#ifndef TTBSTree_hpp
#define TTBSTree_hpp

#include "TTTreeNode.hpp"

#include <iostream>
#include <deque>
#include <queue>

using namespace std;

///比较器
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

/*
 目前存在的问题：
 树开始遍历就不能停止，需要重构为写入访问器的方式，
 目前还不掌握怎么写后续补上，持续学习C++知识
 */

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
        //有问题如果是对象类型的话会奔溃
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
    
    /// 获取节点
    TTTreeNode<T> *getNode(const T element) {
        elementNotNullCheck(element);
        TTTreeNode<T> *node = m_root;
        while (node != nullptr) {
            int cmp = compare(element, node->element);
            if (cmp == 0) {
                return node;
            } else if (cmp > 0) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        
        return node;
    }
    
    //MARK: - 树的遍历
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
    
    /*
     层次遍历
     基本思路：
     1、先把节点入栈
     2、然后取出节点，判断是否有左子树，如果有入栈
     3、然后判断是否有友子树，如果有入栈
     4、一直循环直到栈为空
     */
    void levelOrderTraversal(TTTreeNode<T> *node) {
        if (node == nullptr) return;
        deque<TTTreeNode<T> *> node_queue;
        node_queue.push_front(node);
        while (!node_queue.empty()) {
            TTTreeNode<T> *ele = node_queue.front();
            cout << ele->element << endl;
            node_queue.pop_front();
            if (ele->left != nullptr) {
                node_queue.push_back(ele->left);
            }

            if (ele->right != nullptr) {
                node_queue.push_back(ele->right);
            }
        }
    }
    
//MARK: - 前驱节点&&后驱节点
    /*
     查找某一个节点的前驱节点
     遍历方式：使用中序遍历方式的树
     前驱节点：中序遍历时的前一个节点
     如果是二叉搜索树，前驱节点就是钱一个比它小的节点，这里使用中序遍历方式
     */
    TTTreeNode<T> *predecessor(TTTreeNode<T> *node) {
        if (node == nullptr) return nullptr;
        //前驱节点在左子树当中(left->right->right....)
        TTTreeNode<T> *p = node->left;
        if (p != nullptr) {
            while (p->right != nullptr) {
                p = p->right;
            }
            
            return p;
        }
        
        //从父节点、祖父节点中查找前驱节点
        while (node->parent != nullptr && node != node->parent->left) {
            node = node->parent;
        }
        
        return node->parent;
    }
    
    /*
     查找某一个节点的后继节点
     */
    TTTreeNode<T> *successor(TTTreeNode<T> *node) {
        //如果节点为空那么没有后继节点
        if (node == nullptr) return nullptr;
        //往右边找一直知道节点的左子节点知道节点的左子节点为空为止
        TTTreeNode<T> *p = node->right;
        if (p != nullptr) {
            while (p->left != nullptr) {
                p = p->left;
            }
            
            return p;
        }
        
        //如果不存在左子节点，那么往上找
        while (node->parent != nullptr && node != node->parent->right) {
            node = node->parent;
        }
        
        return node->parent;
    }
    
    void removeNode(TTTreeNode<T> *node) {
        if (node == nullptr) return;
        m_size--;
        if (node->left != nullptr && node->right != nullptr) { //度为2的节点
            //找到后继节点
            TTTreeNode<T> *s = successor(node);
            //用后继节点的值覆盖度为2的节点的值
            node->element = s->element;
            //删除后继节点
            node = s;
        }
        
        //删除node节点（node的度必然是1或0）
        TTTreeNode<T> *replacement = node->left != nullptr ? node->left : node->right;
        if (replacement != nullptr) { //node是度为1的节点
            //更改parent
            replacement->parent = node->parent;
            //更改parent的left、right的指向
            if (node->parent == nullptr) { //node是度为1的节点并且是根节点
                m_root = replacement;
            } else if (node == node->parent->left) {
                node->parent->left = replacement;
            } else { //被删除的节点是删除节点的右节点
                node->parent->right = replacement;
            }
            
            //恢复平衡
            afterRemove(replacement);
        } else if (node->parent == nullptr) { //node是叶子节点并且是根节点
            delete m_root;
            m_root = nullptr;
        } else { //node是叶子节点，但不是根节点
            if (node == node->parent->right) {
                node->parent->right = nullptr;
            } else {
                node->parent->left = nullptr;
            }
            
            //恢复平衡
            afterRemove(node);
        }
        
        //最后一步回收内存
        delete node;
    }
public:
    TTBSTree(TTBSTComparator<T> *x):
        m_comparator(x), m_root(nullptr), m_size(0) {}
    
    TTBSTree():TTBSTree(nullptr) {}
    
    ~TTBSTree() {
        clear();
    }
    
    int size() const {
        return m_size;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void clear() {
        if (m_root == nullptr) return;
        queue<TTTreeNode<T> *> q;
        q.push(m_root);
        while (!q.empty()) {
            int levelSize = (int)q.size();
            for (int i = 0; i < levelSize; i++) {
                TTTreeNode<T> *node = q.front();
                q.pop();
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                
                if (node->right != nullptr) {
                    q.push(node->right);
                }
                
                delete node;
            }
        }
        
        m_root = nullptr;
        m_size = 0;
    }
    
    void add(const T &element) {
        elementNotNullCheck(element);
        //根节点为空
        if (m_root == nullptr) {
            m_root = createNode(element, nullptr);
            m_size++;
            //新添加之后的处理
            afterAdd(m_root);
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
        TTTreeNode<T> *newNode = createNode(element, parent);
        cmp > 0 ? parent->right = newNode : parent->left = newNode;
        m_size++;
        //新添加之后的处理
        afterAdd(newNode);
    }
    
    void remove(const T &element) {
        //找到要删除的节点
        TTTreeNode<T> *node = getNode(element);
        removeNode(node);
    }
    
    bool contains(const T &element) {
        return getNode(element) != nullptr;
    }
    
    //MARK: ------------- 二叉搜索树树的遍历 ------------------------------------
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
    
    /*
     层次遍历
     基本思路：
     1、先把节点入栈
     2、然后取出节点，判断是否有左子树，如果有入栈
     3、然后判断是否有友子树，如果有入栈
     4、一直循环直到栈为空
     */
    void levelOrderTraversal() {
        levelOrderTraversal(m_root);
    }
    
    /*
     获取树的高度，使用层次遍历
     */
    int height() {
        if (m_root == nullptr) return 0;
        deque<TTTreeNode<T> *> queue;
        queue.push_back(m_root);
        
        int height = 0;
        int levelSize = 1;
        while (!queue.empty()) {
            TTTreeNode<T> *node = queue.front();
            queue.pop_front();
            levelSize--;
            if (node->left != nullptr) {
                queue.push_back(node->left);
            }
            
            if (node->right != nullptr) {
                queue.push_back(node->right);
            }
            
            //如果levelSize为零，那么说明这一层已经遍历完成
            if (levelSize == 0) {
                levelSize = (int)queue.size();
                height++;
            }
        }
        
        return height;
    }
    
    /// 判断是否为完全二叉树
    bool isComplete() {
        //1、完全二叉树，如果左子节点为空，右子节点不为空，那么不是完全二叉树，
        //因为在完全二叉树中，如果只有一个叶子节点，那么必须为左子节点
        //2、如果一个节点它的节点的度不为2那么接下来的所有子节点都是叶子节点
        if (m_root == nullptr) return false;
        deque<TTTreeNode<T> *> queue;
        queue.push_back(m_root);
        bool isLeaf = false;
        while (!queue.empty()) {
            TTTreeNode<T> *node = queue.front();
            queue.pop_front();
            //如果是叶子节点，那么只存在一个子节点，而且必须是左子节点
            if (isLeaf && !(node->left == nullptr && node->right != nullptr)) {
                return false;
            }
            
            //判断是否只有左子节点
            if (node->left != nullptr) {
                queue.push_back(node->left);
            } else if (node->right != nullptr) {
                return false;
            }
            
            if (node->right){
                queue.push_back(node->right);
            } else {
                //说明往下开始后面的子节点都是叶子节点
                // node->right == null
                // node->left != null && node->right == null
                isLeaf = true;
            }
        }
        
        return true;
    }
protected:
    //虚继承，添加节点后再平衡二叉树
    virtual void afterAdd(TTTreeNode<T> *node) {}
    //虚继承，删除节点后调整平衡
    virtual void afterRemove(TTTreeNode<T> *node) {}
    virtual TTTreeNode<T> *createNode(const T &element, TTTreeNode<T> *parent) {
        return new TTTreeNode<T>(element, parent);
    }
    
    void updateRoot(TTTreeNode<T> *node) {
        m_root = node;
    }
};

#endif /* TTBSTree_hpp */
