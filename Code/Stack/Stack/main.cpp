//
//  main.cpp
//  Stack
//
//  Created by Lawrence on 2020/11/2.
//

#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

/*
 1081. 不同字符的最小子序列
 https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters/
 */
string smallestSubsequence(string s) {
    return "";
}

/*
 20. 有效的括号
 解题思路：栈+hash
 https://leetcode-cn.com/problems/valid-parentheses/
 */
bool isValid(string s) {
    if (s.length() <= 1) return false;
    //利用栈的思想保证顺序
    stack<char> stack;
    for (string::iterator it = s.begin(); it != s.end(); it++) {
        //遇到左括号就入栈
        if (*it == '(' || *it == '{' || *it == '[') {
            stack.push(*it);
        } else {
            //如果栈为空，说明不对称
            if (stack.empty()) return false;
            //遇到右括号就出栈
            char c = stack.top();
            stack.pop();
            if (c == '(' && *it != ')') return false;
            if (c == '{' && *it != '}') return false;
            if (c == '[' && *it != ']') return false;
        }
    }
    
    //如果栈为空说明括号有效
    return stack.empty();
}

bool isValid2(string s) {
    if (s.length() <= 1) return false;
    stack<char> stack;
    //左括号为key,右括号为value
    unordered_map<char, char> map = {{'{', '}'}, {'(', ')'}, {'[', ']'}};
    for (string::iterator it = s.begin(); it != s.end(); it++) {
        //遇到左括号就入栈
        if (map.count(*it)) {
            stack.push(*it);
        } else {
            //如果栈为空，说明不对称
            if (stack.empty()) return false;
            //遇到右括号就出栈
            char c = stack.top();
            if (map[c] != *it) return false;
            stack.pop();
        }
    }
    
    //如果栈为空说明括号有效
    return stack.empty();
}

/*
 232. 用栈实现队列
 解题思路：使用两个栈实现，inStack outStack
 https://leetcode-cn.com/problems/implement-queue-using-stacks/
 */
class MyQueue {
private:
    stack<int> inStack;
    stack<int> outStack;
public:
    MyQueue() {

    }
    
    void push(int x) {
        inStack.push(x);
    }
    
    int pop() {
        int item = peek();
        if (!outStack.empty()) {
            outStack.pop();
        }
        
        return item;
    }
    
    int peek() {
        //如果入栈不为空并且出栈为空，则把入栈数据全部出栈到出栈中
        if (!inStack.empty() && outStack.empty()) {
            while (!inStack.empty()) {
                int item = inStack.top();
                outStack.push(item);
                inStack.pop();
            }
        }
        
        if (outStack.empty()) {
            return NULL;
        }
        
        return outStack.top();
    }
    
    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};

int main(int argc, const char * argv[]) {
    smallestSubsequence("abbccddeeffa");
    string str = "{{}}";
    bool res1 = isValid2(str);
    cout << "isValid:" << res1 << endl;
    
    MyQueue queue;
    queue.push(1);
    queue.push(2);
    cout << queue.peek() << endl;
    cout << queue.pop() << endl;
    
    return 0;
}
