//
//  main.cpp
//  LeetCodeToday
//
//  Created by Lawrence on 2020/11/2.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <stack>

using namespace std;

/******************************* 坚持不懈， 每日一题 ***********************************/

/*
 349. 两个数组的交集
 解题思路：使用hash方法去重
 https://leetcode-cn.com/problems/intersection-of-two-arrays/
 */
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() == 0 || nums2.size() == 0) {
        return {};
    }
    
    //去重
    unordered_set<int> parentSet = unordered_set<int>(nums1.begin(), nums1.end());
    unordered_set<int> childSet;
    //判断区间是否重合
    for (int i = 0; i < nums2.size(); i++) {
        if (parentSet.find(nums2[i]) != parentSet.end()) {
            childSet.insert(nums2[i]);
        }
    }
    
    vector<int> res = vector<int>(childSet.begin(), childSet.end());
    return res;
}

bool validMountainArray(vector<int>& A) {
    if (A.size() <= 1) return false;
    stack<int> left;
    stack<int> right;
    left.push(A.front());
    for (int i = 1; i < A.size(); i++) {
        if (A[i] > left.top()) {
            left.push(A[i]);
        } else {
            if (right.empty()) {
                right.push(A[i]);
            } else if (A[i] < right.top()) {
                right.push(A[i]);
            } else {
                return false;
            }
            
            if (right.top() >= left.top()) {
                return false;
            }
        }
    }
    
    return  left.size() != 1 && right.size() >= 1;
}

int main(int argc, const char * argv[]) {
    vector<int> nums1 = {1, 2, 2, 1};
    vector<int> nums2 = {2, 2};
    vector<int> res1 = intersection(nums1, nums2);
    
    vector<int> nums3 = {0, 1, 2, 1, 2};
    bool res2 = validMountainArray(nums3);
    return 0;
}
