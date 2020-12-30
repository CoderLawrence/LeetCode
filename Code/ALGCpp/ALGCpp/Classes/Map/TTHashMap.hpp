//
//  TTHashMap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/26.
//

#ifndef TTHashMap_hpp
#define TTHashMap_hpp

#include <queue>

#include "TTMap.hpp"
#include "Eums.h"

using namespace std;

template <class K, class V>
class TTHashMapNode {
public:
    int hash = 0;
    K key;
    V value;
    TTNodeColor color = RED;
    TTHashMapNode<K, V> *left;
    TTHashMapNode<K, V> *right;
    TTHashMapNode<K, V> *parent;
    
    TTHashMapNode():TTHashMapNode(NULL, NULL, NULL) {}
    TTHashMapNode(const K &k, const V &v, TTHashMapNode<K, V> *parent):
        key(k), value(v), left(NULL), right(NULL), parent(parent) {
        std::hash<K> hash_key;
        hash = (int)hash_key(key);
    }
    
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
    TTHashMapNode<K, V> *sibling() {
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
class TTHashMap: public TTMap<K, V> {
private:
    int m_size;
    int m_capacity;
    static const int DEFUALT_CAPACITY = 1 << 4;
    TTHashMapNode<K, V> *m_table[DEFUALT_CAPACITY];
public:
    TTHashMap() {
        m_size = 0;
        m_capacity = DEFUALT_CAPACITY;
        memset(m_table, 0, sizeof(m_table));
    }
    
    ~TTHashMap() {
        clear();
    }
    
    int size() const {
        return m_size;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void clear() {
        //释放内存
        for (int i = 0; i < m_capacity; i++) {
            free(m_table[i]);
        }
        
        m_size = 0;
        m_capacity = DEFUALT_CAPACITY;
    }
    
    V put(const K &key, const V &value) {
        int index = getIndex(key);
        TTHashMapNode<K, V> *root = m_table[index];
        if (root == nullptr) {
            TTHashMapNode<K, V> *node = new TTHashMapNode<K, V>(key, value, nullptr);
            m_table[index] = node;
            m_size++;
            return NULL;
        }
        
        // 添加新的节点到红黑树上面
        TTHashMapNode<K, V> *parent = root;
        TTHashMapNode<K, V> *node = root;
        int cmp = 0;
        K k1 = key;
        std::hash<K> hash_key;
        int h1 = (int)hash_key(k1);
        TTHashMapNode<K, V> *result = nullptr;
        bool searched = false; // 是否已经搜索过这个key
        do {
            parent = node;
            K k2 = node->key;
            int h2 = node->hash;
            /* 最优写法只是目前c++水平不够，后续需要实现
            if (h1 > h2) {
                cmp = 1;
            } else if (h1 < h2) {
                cmp = -1;
            } else if (Objects.equals(k1, k2)) {
                cmp = 0;
            } else if (k1 != null && k2 != null
                       && k1 instanceof Comparable
                       && k1.getClass() == k2.getClass()
                       && (cmp = ((Comparable)k1).compareTo(k2)) != 0) {
            } else if (searched) { // 已经扫描了
                cmp = System.identityHashCode(k1) - System.identityHashCode(k2);
            } else { // searched == false; 还没有扫描，然后再根据内存地址大小决定左右
                if ((node.left != null && (result = node(node.left, k1)) != null)
                    || (node.right != null && (result = node(node.right, k1)) != null)) {
                    // 已经存在这个key
                    node = result;
                    cmp = 0;
                } else { // 不存在这个key
                    searched = true;
                    cmp = System.identityHashCode(k1) - System.identityHashCode(k2);
                }
            }*/
            
            if (h1 > h2) {
                cmp = 1;
            } else if (h1 < h2) {
                cmp = -1;
            } else if (k1 == k2) {
                cmp = 0;
            } else if (searched) { // 已经扫描了
                cmp = 1; //没有找到往右边查找
            } else { // searched == false; 还没有扫描，然后再根据内存地址大小决定左右
                if ((node->left != nullptr && (result = getNode(node->left, k1)) != nullptr)
                    || (node->right != nullptr && (result = getNode(node->right, k1)) != nullptr)) {
                    // 已经存在这个key
                    node = result;
                    cmp = 0;
                } else { // 不存在这个key
                    searched = true;
                    cmp = 1;
                }
            }
                
            if (cmp > 0) {
                node = node->right;
            } else if (cmp < 0) {
                node = node->left;
            } else { // 相等
                V oldValue = node->value;
                node->key = key;
                node->value = value;
                node->hash = h1;
                return oldValue;
            }
        } while (node != nullptr);
        
        // 看看插入到父节点的哪个位置
        TTHashMapNode<K, V> *newNode = new TTHashMapNode<K, V>(key, value, parent);
        if (cmp > 0) {
            parent->right = newNode;
        } else {
            parent->left = newNode;
        }
        
        m_size++;
        
        // 新添加节点之后的处理
       // fixAfterPut(newNode);
        return NULL;
    }
    
    V get(const K &key) {
        TTHashMapNode<K, V> *node = getNode(key);
        return node != nullptr ? node->value : NULL;
    }
    
    V remove(const K &key) {
        TTHashMapNode<K, V> *node = getNode(key);
        if (node != nullptr) {
            V value = node->value;
            remove(node);
            return value;
        }
        
        return NULL;
    }
    
    bool containsKey(const K &key) {
        return getNode(key) != nullptr;
    }
    
    bool containsValue(const V &value) {
        if (m_size == 0) return false;
        queue<TTHashMapNode<K, V> *> q;
        for (int i = 0; i < m_capacity; i++) {
            if (m_table[i] == nullptr) continue;
            q.push(m_table[i]);
            while (!q.empty()) {
                int len = (int)q.size();
                for (int i = 0; i < len; i++) {
                    TTHashMapNode<K, V> *node = q.front();
                    q.pop();
                    if (node->value == value) return true;
                    if (node->left != nullptr) {
                        q.push(node->left);
                    }
                    
                    if (node->right != nullptr) {
                        q.push(node->right);
                    }
                }
            }
        }
        
        return false;
    }
    
    void traversal() {
        if (m_size == 0) return;
        queue<TTHashMapNode<K, V> *> q;
        for (int i = 0; i < m_capacity; i++) {
            if (m_table[i] == nullptr) continue;
            q.push(m_table[i]);
            while (!q.empty()) {
                int len = (int)q.size();
                for (int i = 0; i < len; i++) {
                    TTHashMapNode<K, V> *node = q.front();
                    q.pop();
                    //暂时先遍历打印
                    cout << node->value << endl;
                    if (node->left != nullptr) {
                        q.push(node->left);
                    }
                    
                    if (node->right != nullptr) {
                        q.push(node->right);
                    }
                }
            }
        }
    }
    
private:
    //计算hash值获取索引
    int getIndex(const K &key) {
        std::hash<K> hash_key;
        int hash = (int)hash_key(key);
        return (hash ^(hash >> 16)) & (m_capacity - 1);
    }
    
    //获取节点hash值
    int getIndex(TTHashMapNode<K, V> *node) {
        return (node->hash ^(node->hash >> 16)) & (m_capacity - 1);
    }
    
    V remove(TTHashMapNode<K, V> *node) {
        if (node == nullptr) return node->value;
        m_size--;
        V oldValue = node->value;
        if (node->left != nullptr && node->right != nullptr) { //度为2的节点
            //找到后继节点
            TTHashMapNode<K, V> *s = successor(node);
            //用后继节点的值覆盖度为2的节点的值
            node->key = s->key;
            node->value = s->value;
            //删除后继节点
            node = s;
        }
        
        //删除node节点（node的度必然是1或0）
        TTHashMapNode<K, V> *replacement = node->left != nullptr ? node->left : node->right;
        int index = getIndex(node);
        if (replacement != nullptr) { //node是度为1的节点
            //更改parent
            replacement->parent = node->parent;
            //更改parent的left、right的指向
            if (node->parent == nullptr) { //node是度为1的节点并且是根节点
                m_table[index] = replacement;
            } else if (node == node->parent->left) {
                node->parent->left = replacement;
            } else { //被删除的节点是删除节点的右节点
                node->parent->right = replacement;
            }
            
            //恢复平衡
            afterRemove(replacement);
        } else if (node->parent == nullptr) { //node是叶子节点并且是根节点
            m_table[index] = NULL;
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
    
    void afterPut(TTHashMapNode<K, V> *node) {
        TTHashMapNode<K, V> *parent = node->parent;
        //添加的是根节点，直接染成黑色
        if (parent == nullptr) {
            black(node);
            return;
        }
        
        //如果父节点是黑色，不用做额外处理，直接返回
        if (isBlack(parent)) return;
        // uncle节点
        TTHashMapNode<K, V> *uncle = parent->sibling();
        //祖父节点
        TTHashMapNode<K, V> *grand = parent->parent;
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
    
    void afterRemove(TTHashMapNode<K, V> *node) {
        //如果删除的节点是红色
        //或者用以删除节点的子节点是红色
        if (isRed(node)) {
            black(node);
            return;
        }
        
        TTHashMapNode<K, V> *parent = node->parent;
        //删除的是根节点
        if (parent == nullptr) return;
        //删除的是黑色叶子节点【下益】
        //判断被删除的node是左还是右
        bool left = parent->left == nullptr || node->isLeftChild();
        TTHashMapNode<K, V> *sibling = left ? parent->right : parent->left;
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
    bool valEquals(V &v1, V &v2) {
        return v1 == NULL ? v2 == NULL : v1 == v2;
    }
#pragma mark -------------- 节点查找逻辑 --------------------------
    TTHashMapNode<K, V> *getNode(const K &key) {
        TTHashMapNode<K, V> *root = m_table[getIndex(key)];
        return root == nullptr ? nullptr : getNode(root, key);
    }
    /// 获取节点
    TTHashMapNode<K, V> *getNode(TTHashMapNode<K, V> *node, const K &k1) {
        std::hash<K> hash_key;
        int h1 = (int)hash_key(k1);
        TTHashMapNode<K, V> *result = nullptr;
//        int cmp = 0;
        do {
            K k2 = node->key;
            int h2 = node->hash;
           //性能比价好的版本
           /*
            // 先比较哈希值
            if (h1 > h2) {
                node = node.right;
            } else if (h1 < h2) {
                node = node.left;
            } else if (Objects.equals(k1, k2)) {
                return node;
            } else if (k1 != null && k2 != null
                       && k1.getClass() == k2.getClass()
                       && k1 instanceof Comparable
                       && (cmp = ((Comparable) k1).compareTo(k2)) != 0) {
                node = cmp > 0 ? node.right : node.left;
            } else if (node.right != null && (result = node(node.right, k1)) != null) {
                return result;
            } else { // 只能往左边找
                node = node.left;
            }*/
            
            //暂时如此处理，后续补充c++知识再完善比较逻辑
            // 先比较哈希值
            if (h1 > h2) {
                node = node->right;
            } else if (h1 < h2) {
                node = node->left;
            } else if (k1 == k2) {
                return node;
            } else if (node->right != nullptr && (result = getNode(node->right, k1)) != nullptr) {
                return result;
            } else { //只能往左边找
                node = node->left;
            }
        } while (node != nullptr);
        
        return nullptr;
    }
    
    /*
     查找某一个节点的前驱节点
     遍历方式：使用中序遍历方式的树
     前驱节点：中序遍历时的前一个节点
     如果是二叉搜索树，前驱节点就是钱一个比它小的节点，这里使用中序遍历方式
     */
    TTHashMapNode<K, V> *predecessor(TTHashMapNode<K, V> *node) {
        if (node == nullptr) return nullptr;
        //前驱节点在左子树当中(left->right->right....)
        TTHashMapNode<K, V> *p = node->left;
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
    TTHashMapNode<K, V> *successor(TTHashMapNode<K, V> *node) {
        //如果节点为空那么没有后继节点
        if (node == nullptr) return nullptr;
        //往右边找一直知道节点的左子节点知道节点的左子节点为空为止
        TTHashMapNode<K, V> *p = node->right;
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
    void rotateLeft(TTHashMapNode<K, V> *grand) {
        TTHashMapNode<K, V> *parent = grand->right;
        TTHashMapNode<K, V> *child = parent->left;
        //有旋转
        grand->right = parent->left;
        parent->left = grand;
        //更新节点的父节点和高度
        afterRotate(grand, parent, child);
    }
    
    //右旋转
    void rotateRight(TTHashMapNode<K, V> *grand) {
        TTHashMapNode<K, V> *parent = grand->left;
        TTHashMapNode<K, V> *child = parent->right;
        //有旋转
        grand->left = child;
        parent->right = grand;
        //更新节点的父节点和高度
        afterRotate(grand, parent, child);
    }
    
    virtual void afterRotate(TTHashMapNode<K, V> *grand, TTHashMapNode<K, V> *parent, TTHashMapNode<K, V> *child) {
        //更新父节点的子节点的指向
        parent->parent = grand->parent;
        if (grand->isLeftChild()) {
            grand->parent->left = parent;
        } else if (grand->isRightChild()) {
            grand->parent->right = parent;
        } else {
            m_table[getIndex(grand->key)] = parent;
        }
        
        if (child != nullptr) {
            child->parent = grand;
        }
        
        grand->parent = parent;
    }
#pragma mark -------------- 节点染色辅助方法 ------------------------
    /// 对节点进行染色
    TTHashMapNode<K, V> *color(TTHashMapNode<K, V> *node, TTNodeColor color) {
        if (node == nullptr) return node;
        node->color = color;
        return node;
    }
    
    TTHashMapNode<K, V> *red(TTHashMapNode<K, V> *node) {
        return color(node, RED);
    }
    
    TTHashMapNode<K, V> *black(TTHashMapNode<K, V> *node) {
        return color(node, BLACK);
    }
    
    /// 判断节点颜色
    TTNodeColor colorOf(TTHashMapNode<K, V> *node) {
        return node == nullptr ? BLACK : node->color;
    }
    
    bool isBlack(TTHashMapNode<K, V> *node) {
        return colorOf(node) == BLACK;
    }
    
    bool isRed(TTHashMapNode<K, V> *node) {
        return colorOf(node) == RED;
    }
};

#endif /* TTHashMap_hpp */
