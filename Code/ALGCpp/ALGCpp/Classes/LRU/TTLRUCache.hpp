//
//  TTLRUCache.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/24.
//

#ifndef TTLRUCache_hpp
#define TTLRUCache_hpp

#include <unordered_map>

class Node {
public:
    int key;
    int value;
    Node *pre;
    Node *next;
    Node():Node(0, 0) {}
    Node(int key, int value):
        key(key), value(value), pre(nullptr), next(nullptr) {}
   ~Node() {}
};

class LinkedList {
private:
    int m_size;
    Node *head;
    Node *tail;
public:
    LinkedList(){
        m_size = 0;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->pre = head;
    }

    ~LinkedList() {
        clear();
    }

    void clear() {
        Node *curr = head;
        while(curr != nullptr) {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }

    void remove(Node *node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
        m_size--;
    }

    Node *removeFirst() {
        if (head->next == tail) return nullptr;
        Node *first = head->next;
        remove(first);
        return first;
    }

    void addLast(Node *node) {
        node->pre = tail->pre;
        node->next = tail;
        tail->pre->next = node;
        tail->pre = node;
        m_size++;
    }

    int size() const {
        return m_size;
    }
};

/*
 最近最少被使用缓存机制
 思路：
 1、使用双向链表来缓存key和value，map保存key和node(节点)，便于进行O(1)复杂度的添加和删除操作
 2、使用淘汰机制，当添加的节点已经超出设定的容量是淘汰链表的头结点，因为头结点是最近最少使用的
 3、新添加的节点都放到链表末尾，频繁获取的value对应的节点移动到链表的末尾，使得最近经常使用的不被淘汰
 */
class LRUCache {
private:
    int cap;
    LinkedList cache;
    unordered_map<int, Node *> map;
    
    void makeRecently(int key) {
        // 将节点添加到末尾，使得最近访问的节点为最近使用过的节点
        Node *node = map[key];
        cache.remove(node);
        cache.addLast(node);
    }

    void addRecently(int key, int value) {
        // 添加节点到链表末尾
        Node *node = new Node(key, value);
        cache.addLast(node);
        map[key] = node;
    }

    void deleteKey(int key) {
        Node *node = map[key];
        cache.remove(node);
        map.erase(key);
    }

    void removeLeastRecnetly() {
        Node *deletedNode = cache.removeFirst();
        int deleteKey = deletedNode->key;
        map.erase(deleteKey);
    }
public:
    LRUCache(int capacity) {
       cap = capacity;
    }

    ~LRUCache() {}
    
    int get(int key) {
        if (map.count(key)) {
            Node *node = map[key];
            makeRecently(key);
            return node->value;
        }

        return -1;
    }
    
    void put(int key, int value) {
        if (map.count(key)) {
            deleteKey(key);
            addRecently(key, value);
            return;
        }
        
        if (cache.size() >= cap) {
            removeLeastRecnetly();
        }

        addRecently(key, value);
    }
};

#endif /* TTLRUCache_hpp */
