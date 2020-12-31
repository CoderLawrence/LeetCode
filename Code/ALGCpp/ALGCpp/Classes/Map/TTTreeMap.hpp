//
//  TTTreeMap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/23.
//

#ifndef TTTreeMap_hpp
#define TTTreeMap_hpp

#include <iostream>
#include <queue>
#include <optional>

#include "TTMap.hpp"
#include "Eums.h"

///比较器
template <class K>
class TTMapComparator {
public:
    ///纯虚函数，子类重写
    virtual int compare(const K &e1, const K &e2) = 0;
};

template<class K, class V>
class TTMapNode {
public:
    K key = NULL;
    V value = NULL;
    TTNodeColor color = RED;
    TTMapNode<K, V> *left;
    TTMapNode<K, V> *right;
    TTMapNode<K, V> *parent;
    TTMapNode():TTMapNode(NULL, NULL, NULL) {}
    TTMapNode(const K &k, const V &v, TTMapNode<K, V> *parent):
        key(k), value(v), left(NULL), right(NULL), parent(parent) {}
   
    
    ///是否存在左右子节点
    bool hasTwoChildren() {
        return this->left != nullptr && this->left != nullptr;
    }
    /// 是否为叶子节点
    bool isLeaf() {
        return this->left == nullptr && this->right == nullptr;
    }
    
    ///是否为左子节点
    bool isLeftChild() {
        return this->parent != nullptr && this == this->parent->left;
    }
    
    ///是否为右子节点
    bool isRightChild() {
        return this->parent != nullptr && this == this->parent->right;
    }
    
    /// 获得兄弟节点
    TTMapNode<K, V> *sibling() {
        //如果是父节点的左子节点，那么兄弟节点为父节点的右节点
        if (isLeftChild()) {
            return this->parent->right;
        } else if (isRightChild()) { //与上面相反
            return this->parent->left;
        }
        
        return nullptr;
    }
};

template <class K, class V>
class TTTreeMap: public TTMap<K, V> {
private:
    int m_size;
    TTMapNode<K, V> *m_root;
    TTMapComparator<K> *m_comparator;
public:
    TTTreeMap():TTTreeMap(nullptr) {}
    TTTreeMap(TTMapComparator<K> *cmp):m_comparator(cmp) {
        m_root = nullptr;
        m_size = 0;
    }
    
    ~TTTreeMap() {
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
        queue<TTMapNode<K, V> *> q;
        q.push(m_root);
        while (!q.empty()) {
            int levelSize = (int)q.size();
            for (int i = 0; i < levelSize; i++) {
                TTMapNode<K, V> *node = q.front();
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
    
    V put(const K &key, const V &value = NULL) {
        keyNotNullCheck(key);
        //根节点为空
        if (m_root == nullptr) {
            m_root = new TTMapNode<K, V>(key, value, nullptr);
            m_size++;
            //新添加之后的处理
            afterPut(m_root);
            return value;
        }
        
        //添加的不是第一个节点
        int cmp = 0;
        TTMapNode<K, V> *parent = nullptr;
        TTMapNode<K, V> *node = m_root;
        //查找合适节点
        while (node != nullptr) {
            cmp = compare(key, node->key);
            parent = node;
            if (cmp > 0) {
                node = node->right;
            } else if (cmp < 0) {
                node = node->left;
            } else {
                //如果是两个值相等则更新为最新的值
                node->key = key;
                node->value = value;
                return value;
            }
        }
        
        //根据比较的值插入叶子节点
        TTMapNode<K, V> *newNode = new TTMapNode<K, V>(key, value, parent);
        cmp > 0 ? parent->right = newNode : parent->left = newNode;
        m_size++;
        //新添加之后的处理
        afterPut(newNode);
        return value;
    }
    
    V get(const K &key) {
        TTMapNode<K, V> *node = getNode(key);
        return node != nullptr ? node->value : NULL;
    }
    
    V remove(const K &key) {
        TTMapNode<K, V> *node = getNode(key);
        return remove(node);
    }
    
    bool containsKey(const K &key) {
        return getNode(key) != nullptr;
    }
    
    bool containsValue(const V &value) {
        if (m_root == nullptr) return false;
        queue<TTMapNode<K, V> *> q;
        q.push(m_root);
        while (!q.empty()) {
            int levelSize = (int)q.size();
            for (int i = 0; i < levelSize; i++) {
                TTMapNode<K, V> *node = q.front();
                if (valEquals(node->value, value)) {
                    return true;
                }
                
                q.pop();
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
        }
        
        return false;
    }
    
    void traversal() {
        traversal(m_root);
    }
private:
    void traversal(TTMapNode<K, V> *node) {
        if (node == nullptr) return;
        traversal(node->left);
        traversal(node->right);
    }
    
    V remove(TTMapNode<K, V> *node) {
        if (node == nullptr) return node->value;
        m_size--;
        V oldValue = node->value;
        if (node->left != nullptr && node->right != nullptr) { //度为2的节点
            //找到后继节点
            TTMapNode<K, V> *s = successor(node);
            //用后继节点的值覆盖度为2的节点的值
            node->key = s->key;
            node->value = s->value;
            //删除后继节点
            node = s;
        }
        
        //删除node节点（node的度必然是1或0）
        TTMapNode<K, V> *replacement = node->left != nullptr ? node->left : node->right;
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
        return oldValue;
    }
    
    void afterPut(TTMapNode<K, V> *node) {
        TTMapNode<K, V> *parent = node->parent;
        //添加的是根节点，直接染成黑色
        if (parent == nullptr) {
            black(node);
            return;
        }
        
        //如果父节点是黑色，不用做额外处理，直接返回
        if (isBlack(parent)) return;
        // uncle节点
        TTMapNode<K, V> *uncle = parent->sibling();
        //祖父节点
        TTMapNode<K, V> *grand = parent->parent;
        if (isRed(uncle)) { //叔父节点是红色【B树节点上益】
            black(parent);
            black(uncle);
            //递归调用
            afterPut(red(grand));
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
                rotateLeft(parent);
            }
            //祖父节点右旋
            rotateRight(grand);
        } else { //R
            red(grand);
            if (node->isLeftChild()) { //RL
                black(node);
                rotateRight(parent);
            } else { //RR
                black(parent);
                //有旋转祖父节点，放到下面统一处理
            }
            //祖父节点左旋
            rotateLeft(grand);
        }
    }
    
    void afterRemove(TTMapNode<K, V> *node) {
        //如果删除的节点是红色
        //或者用以删除节点的子节点是红色
        if (isRed(node)) {
            black(node);
            return;
        }
        
        TTMapNode<K, V> *parent = node->parent;
        //删除的是根节点
        if (parent == nullptr) return;
        //删除的是黑色叶子节点【下益】
        //判断被删除的node是左还是右
        bool left = parent->left == nullptr || node->isLeftChild();
        TTMapNode<K, V> *sibling = left ? parent->right : parent->left;
        if (left) { //被删除的节点再左边，兄弟节点在右边
            if (isRed(sibling)) {
                black(sibling);
                red(parent);
                rotateLeft(parent);
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
                    rotateRight(sibling);
                    sibling = parent->right;
                }
                
                color(sibling, colorOf(parent));
                black(sibling->right);
                black(parent);
                rotateLeft(sibling);
            }
        } else { //被删除的节点在右边，兄弟节点在左边
            if (isRed(sibling)) { //兄弟节点是红色
                black(sibling);
                red(parent);
                rotateRight(parent);
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
                    rotateLeft(sibling);
                    sibling = parent->left;
                }
                
                color(sibling, colorOf(parent));
                black(sibling->left);
                black(parent);
                rotateRight(parent);
            }
        }
    }
#pragma mark ----------  辅助方法 -----------------------------
    bool valEquals(const V &v1, const V &v2) {
        optional<V> rhs = make_optional<K>(v1);
        optional<V> lhs = make_optional<K>(v2);
        return rhs == lhs;
    }
    
    void keyNotNullCheck(const K &key) {
        optional<K> op = make_optional<K>(key);
        if (!op.has_value()) {
            throw invalid_argument("TTTreeMap::getNode() key can't be null");
        }
    }
#pragma mark ------------- 比较器 -------------------------------
    /// 比价节点的值：e1 = e2 返回0，e1 > e2 放回1， e1 < e2 返回 -1
    /// @param e1 节点的值
    /// @param e2 节点的值
    int compare(const K &e1, const K &e2) const {
        if (m_comparator != nullptr) {
            return m_comparator->compare(e1, e2);
        }
        
        return e1 - e2;
    }
#pragma mark -------------- 节点查找逻辑 --------------------------
    /// 获取节点
    TTMapNode<K, V> *getNode(const K &key) {
        keyNotNullCheck(key);
        TTMapNode<K, V> *node = m_root;
        while (node != nullptr) {
            int cmp = compare(key, node->key);
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
    
    /*
     查找某一个节点的前驱节点
     遍历方式：使用中序遍历方式的树
     前驱节点：中序遍历时的前一个节点
     如果是二叉搜索树，前驱节点就是钱一个比它小的节点，这里使用中序遍历方式
     */
    TTMapNode<K, V> *predecessor(TTMapNode<K, V> *node) {
        if (node == nullptr) return nullptr;
        //前驱节点在左子树当中(left->right->right....)
        TTMapNode<K, V> *p = node->left;
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
    TTMapNode<K, V> *successor(TTMapNode<K, V> *node) {
        //如果节点为空那么没有后继节点
        if (node == nullptr) return nullptr;
        //往右边找一直知道节点的左子节点知道节点的左子节点为空为止
        TTMapNode<K, V> *p = node->right;
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
#pragma mark -------------- 平衡逻辑 ------------------------------
    //左旋转
    void rotateLeft(TTMapNode<K, V> *grand) {
        TTMapNode<K, V> *parent = grand->right;
        TTMapNode<K, V> *child = parent->left;
        //有旋转
        grand->right = parent->left;
        parent->left = grand;
        //更新节点的父节点和高度
        afterRotate(grand, parent, child);
    }
    
    //右旋转
    void rotateRight(TTMapNode<K, V> *grand) {
        TTMapNode<K, V> *parent = grand->left;
        TTMapNode<K, V> *child = parent->right;
        //有旋转
        grand->left = child;
        parent->right = grand;
        //更新节点的父节点和高度
        afterRotate(grand, parent, child);
    }
    
    virtual void afterRotate(TTMapNode<K, V> *grand, TTMapNode<K, V> *parent, TTMapNode<K, V> *child) {
        //更新父节点的子节点的指向
        parent->parent = grand->parent;
        if (grand->isLeftChild()) {
            grand->parent->left = parent;
        } else if (grand->isRightChild()) {
            grand->parent->right = parent;
        } else {
            m_root = parent;
        }
        
        if (child != nullptr) {
            child->parent = grand;
        }
        
        grand->parent = parent;
    }
#pragma mark -------------- 节点染色辅助方法 ------------------------
    /// 对节点进行染色
    TTMapNode<K, V> *color(TTMapNode<K, V> *node, TTNodeColor color) {
        if (node == nullptr) return node;
        node->color = color;
        return node;
    }
    
    TTMapNode<K, V> *red(TTMapNode<K, V> *node) {
        return color(node, RED);
    }
    
    TTMapNode<K, V> *black(TTMapNode<K, V> *node) {
        return color(node, BLACK);
    }
    
    /// 判断节点颜色
    TTNodeColor colorOf(TTMapNode<K, V> *node) {
        return node == nullptr ? BLACK : node->color;
    }
    
    bool isBlack(TTMapNode<K, V> *node) {
        return colorOf(node) == BLACK;
    }
    
    bool isRed(TTMapNode<K, V> *node) {
        return colorOf(node) == RED;
    }
};

#endif /* TTTreeMap_hpp */
