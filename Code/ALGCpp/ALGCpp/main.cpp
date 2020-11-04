//
//  main.cpp
//  ALGCpp
//
//  Created by Lawrence on 2020/11/2.
//

#include <iostream>

#include "TTStack.hpp"
#include "TTQueue.hpp"

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
    
    TTQueue<int> queue(11);
    queue.en_queue(33);
    queue.clear();
    
    return 0;
}
