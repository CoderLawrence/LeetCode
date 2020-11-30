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
#include <map>
#include <deque>
#include <unordered_map>

using namespace std;

class TTQueue {
private:
    int m_size;
    stack<int> inStack;
    stack<int> outStack;
    void copyEleToOutStack() {
        
    }
public:
    TTQueue() {}
    ~TTQueue() {}
    int size() {
        return m_size;
    }
    
    void push(int element) {
        inStack.push(element);
        m_size++;
    }
    
    int pop() {
        int ele = top();
        if (!empty()) {
            outStack.pop();
            m_size--;
        }
        
        return ele;
    }
    
    int top() {
        copyEleToOutStack();
        if (empty()) return -1;
        return outStack.top();
    }
    
    bool empty() {
        return m_size == 0;
    }
};

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

/*
 155. 最小栈
 https://leetcode-cn.com/problems/min-stack/
 */
class MinStack {
private:
    vector<int> stack;
    map<int, int> map;
public:
    MinStack() {
        
    }
    
    void push(int x) {
        stack.push_back(x);
        map[x]++;
    }
    
    void pop() {
        int ele = top();
        stack.pop_back();
        if (map.find(ele) != map.begin()) {
            int count = map[ele];
            if (count == 1) {
                map.erase(ele);
            } else {
                map[ele]--;
            }
        }
    }
    
    int top() {
        int ele = stack.back();
        return ele;
    }
    
    int getMin() {
        auto min = map.begin();
        return min->first;
    }
};

/*
 496. 下一个更大元素 I
 https://leetcode-cn.com/problems/next-greater-element-i/
 */
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    vector<int> res;
    unordered_map<int, int> mymap;
    stack<int> s;
    //大区间的所有元素先入栈，并且找出最大元素，当元素大于栈顶元素时元素出栈，并且把元素存入hash表中
    for (int i = 0; i < nums2.size(); ++i) {
        while (!s.empty() && nums2[i] > s.top()) {
            mymap[s.top()] = nums2[i];
            s.pop();
        }
        
        s.push(nums2[i]);
    }
    
    //判断栈是否为空，如果找不到栈顶的元素那么全部置为-1
    while (!s.empty()) {
        mymap[s.top()] = -1;
        s.pop();
    }
    
    for (int i = 0; i < nums1.size(); ++i) {
        res.push_back(mymap[nums1[i]]);
    }
    
    return res;
}

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
    
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};
    vector<int> res = nextGreaterElement(nums1, nums2);
    for (int item : res) {
        cout << "nextGreaterElement::" << item << endl;
    }
    
    return 0;
}
