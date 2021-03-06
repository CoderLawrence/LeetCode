//
//  main.cpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/2.
//

#include <iostream>
#include <string>

#include "TTStack.hpp"
#include "TTQueue.hpp"
#include "TTCircleQueue.hpp"

#include "TTBSTree.hpp"
#include "AVLTree.hpp"
#include "TTRBTree.hpp"

#include "TTListSet.hpp"
#include "TTTreeSet.hpp"

#include "TTMap.hpp"
#include "TTTreeMap.hpp"
#include "TTHashMap.hpp"
#include "TTLinkedHashMap.hpp"

#include "TTBinaryHeap.hpp"

#include "TTLRUCache.hpp"

using namespace std;

void stack_test() {
    cout << "--------- TTStack ------------------ " << endl;
    //使用数组实现栈
    TTStack<int> stack(22);
    stack.push(33);
    stack.push(44);
    stack.push(55);
    stack.push(66);
    
    cout << stack.isEmpty() << endl;
    cout << stack.top() << endl;
}

void linkedList_test() {
    cout << "--------- TTLinkedList ------------------ " << endl;
    //双向链表
    TTLinkedList<int> linkedList;
    linkedList.add(11);
    linkedList.add(22);
    linkedList.add(1, 33);
    linkedList.set(0, 55);
    cout << "indexOf:" << linkedList.indexOf(22) << endl;
    cout << "size:" << linkedList.size() << endl;
    cout << "indexOf:" << linkedList.indexOf(55) << endl;
    cout << "element:" << linkedList.remove(0) << endl;
    linkedList.clear();
}

void queue_test() {
    cout << "--------- TTQueue ------------------ " << endl;
    //基于双向链表实现的队列
    TTQueue<int> queue(11);
    queue.en_queue(33);
    queue.en_queue(44);
    
    cout << "front:" << queue.front() << endl;
    
    queue.de_queue();
    cout << "fornt:" << queue.front() << endl;
    
    cout << "--------- TTCircleQueue ------------------ " << endl;
    //循环队列
    TTCircleQueue<int> dqueue;
    for (int i = 0; i < 15; i++) {
        dqueue.en_queue_front(i + 1);
        dqueue.en_queue_rear(100 + i + 1);
    }
    
    while (!dqueue.isEmpty()) {
        cout <<"dequeue::de_queue_rear():" << dqueue.de_queue_rear() << endl;
    }
}

void BSTTree_test() {
    cout << "--------- TTBSTree ------------------ " << endl;
    //二叉搜索树
    TTBSTree<int> BSTree;
    BSTree.add(4);
    BSTree.add(5);
    BSTree.add(8);
    BSTree.add(6);
    BSTree.add(1);
    BSTree.add(12);
    BSTree.add(13);
    BSTree.add(16);
    //前序遍历
    cout << "BSTree::preorderTraversal()" << endl;
    BSTree.preorderTraversal();
    //中序遍历
    cout << "BSTree::inorderTraversal()" << endl;
    BSTree.inorderTraversal();
    //后序遍历
    cout << "BSTree::postorderTraversal()" << endl;
    BSTree.postorderTraversal();
    //层次遍历
    cout << "BSTree::levelOrderTraversal()" << endl;
    BSTree.levelOrderTraversal();
    //获取树的大小
    cout << BSTree.size() << endl;
    //获取树的高度
    cout << "BSTree::height()" << BSTree.height() << endl;
    //判断树是否为完全二叉树
    cout << "BSTree::isComplete()" << BSTree.isComplete() << endl;
    
}

void AVLTree_test() {
    cout << "---------------------- AVLTree -------------------" << endl;
    AVLTree<int> AVLTree;
    AVLTree.add(4);
    AVLTree.add(5);
    AVLTree.add(8);
    AVLTree.add(6);
    AVLTree.add(1);
    AVLTree.add(12);
    AVLTree.add(13);
    AVLTree.add(16);
    //前序遍历
    cout << "AVLTree::preorderTraversal()" << endl;
    AVLTree.preorderTraversal();
    //中序遍历
    cout << "BSTree::inorderTraversal()" << endl;
    AVLTree.inorderTraversal();
    //后序遍历
    cout << "AVLTree::postorderTraversal()" << endl;
    AVLTree.postorderTraversal();
    //层次遍历
    cout << "AVLTree::levelOrderTraversal()" << endl;
    AVLTree.levelOrderTraversal();
    //获取树的大小
    cout << AVLTree.size() << endl;
    //获取树的高度
    cout << "AVLTree::height()" << AVLTree.height() << endl;
    //判断树是否为完全二叉树
    cout << "AVLTree::isComplete()" << AVLTree.isComplete() << endl;
    //删除节点
    cout << "AVLTree::remove(5)" << endl;
    AVLTree.remove(5);
    //层次遍历
    cout << "AVLTree::levelOrderTraversal()" << endl;
    AVLTree.levelOrderTraversal();
}

void RBTree_test() {
    cout << "---------------- RBTree ------------------------" << endl;
    TTRBTree<int> RBTree;
    RBTree.add(4);
    RBTree.add(5);
    RBTree.add(8);
    RBTree.add(6);
    RBTree.add(1);
    RBTree.add(12);
    RBTree.add(13);
    RBTree.add(16);
    //前序遍历
    cout << "RBTree::inorderTraversal()" << endl;
    RBTree.preorderTraversal();
    //中序遍历
    cout << "RBTree::inorderTraversal()" << endl;
    RBTree.inorderTraversal();
    //后序遍历
    cout << "RBTree::postorderTraversal()" << endl;
    RBTree.postorderTraversal();
    //层次遍历
    cout << "RBTree::levelOrderTraversal()" << endl;
    RBTree.levelOrderTraversal();
    //获取树的大小
    cout << RBTree.size() << endl;
    //获取树的高度
    cout << "RBTree::height()" << RBTree.height() << endl;
    //判断树是否为完全二叉树
    cout << "RBTree::isComplete()" << RBTree.isComplete() << endl;
    //删除节点
    cout << "RBTree::remove(5)" << endl;
    RBTree.remove(5);
    //层次遍历
    cout << "RBTree::levelOrderTraversal()" << endl;
    RBTree.levelOrderTraversal();
}

void set_test() {
    cout << "--------------- TTListSet -------------------" << endl;
    TTListSet<int> listSet;
    listSet.add(1);
    listSet.add(1);
    listSet.add(2);
    listSet.add(3);
    listSet.add(3);
    listSet.add(4);
    listSet.traversal();
    
    cout << "--------------- TreeSet --------------------" << endl;
    TTTreeSet<int> treeSet;
    treeSet.add(7);
    treeSet.add(9);
    treeSet.add(12);
    treeSet.add(1);
    treeSet.add(1);
    treeSet.add(2);
    treeSet.add(3);
    treeSet.add(3);
    treeSet.add(4);
    treeSet.traversal();
    treeSet.remove(4);
    treeSet.traversal();
}

void map_test() {
    cout << "--------------- TTMap -------------------" << endl;
    TTTreeMap<int, int> map;
    map.put(1, 1);
    map.put(2, 1);
    cout << map.containsKey(1) << endl;
    cout << map.containsKey(2) << endl;
    cout << map.containsValue(4) << endl;
    
    cout << "--------------- TTHashMap -------------------" << endl;
    TTHashMap<string, string> hashMap;
    hashMap.put("Jack", "Jack");
    hashMap.put("Jack", "Rose");
    hashMap.put("Rose", "Jack");
    cout << hashMap.get("Jack") << endl;
    cout << hashMap.get("Rose") << endl;
    cout << hashMap.containsKey("Jack") << endl;
    cout << hashMap.containsValue("Jack") << endl;
    
    for (int i = 0; i < 100; i++) {
        hashMap.put(to_string(i), "Jack");
    }
    
    hashMap.traversal();
    cout << hashMap.size() << endl;
    hashMap.remove("Jack");
    hashMap.remove("99");
    cout << "-----" << hashMap.size() << endl;
    hashMap.traversal();
    
    cout << "--------------- TTLinkedHashMap -------------------" << endl;
    TTLinkedHashMap<string, string> linkedHashMap;
    linkedHashMap.put("Jack", "Rose");
    linkedHashMap.traversal();
}

void heap_test() {
    cout << "--------------- TTBinaryHeap -------------------" << endl;
    TTBinaryHeap<int> binaryHeap;
    binaryHeap.add(90);
    binaryHeap.add(50);
    binaryHeap.add(68);
    binaryHeap.add(43);
    binaryHeap.add(100);
    cout << "binaryHeap::get()" << binaryHeap.get() << endl;
    cout << "binaryHeap::print()" << binaryHeap.get() << endl;
    binaryHeap.print();
    binaryHeap.remove();
    cout << "binaryHeap::print()" << binaryHeap.get() << endl;
    binaryHeap.print();
    
    cout << "--------------- TTBinaryHeap init elements -------------------" << endl;
    vector<int> elements = {1, 5, 50 ,20, 30, 11, 3, 20};
    TTBinaryHeap<int> heap(elements, true);
    cout << "binaryHeap::get()" << heap.get() << endl;
    cout << "binaryHeap::print()" << heap.get() << endl;
    heap.print();
    heap.remove();
    cout << "binaryHeap::print()" << heap.get() << endl;
    heap.print();
}

void LRU_test() {
    cout << "--------------- LRUCache -------------------" << endl;
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);
    cache.put(3, 3);
    cache.get(2);
    cache.put(4, 4);
    cache.get(1);
    cache.get(3);
    cache.get(4);
}

int main(int argc, const char * argv[]) {
    stack_test();
    linkedList_test();
    queue_test();
    BSTTree_test();
    AVLTree_test();
    BSTTree_test();
    RBTree_test();
    set_test();
    map_test();
    heap_test();
    LRU_test();
    
    return 0;
}
