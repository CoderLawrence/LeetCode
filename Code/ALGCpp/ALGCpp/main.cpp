//
//  main.cpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/2.
//

#include <iostream>

#include "TTStack.hpp"
#include "TTQueue.hpp"
#include "TTCircleQueue.hpp"

#include <stack>
#include <queue>

using namespace std;

int main(int argc, const char * argv[]) {
    
    TTStack<int> stack(22);
    stack.push(33);
    stack.push(44);
    stack.push(55);
    stack.push(66);
    
    cout << stack.isEmpty() << endl;
    cout << stack.top() << endl;
    
    //链表
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
    
    //队列
    TTQueue<int> queue(11);
    queue.en_queue(33);
    queue.en_queue(44);
    
    cout << "front:" << queue.front() << endl;
    
    queue.de_queue();
    cout << "fornt:" << queue.front() << endl;
    
    //循环队列
    TTCircleQueue<int> dqueue;
    dqueue.en_queue_front(10);
    dqueue.en_queue_front(20);
    cout <<"dequeue::front:" << dqueue.front() << endl;
    
    return 0;
}
