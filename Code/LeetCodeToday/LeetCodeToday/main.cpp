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

/*
 941. 有效的山脉数组
 https://leetcode-cn.com/problems/valid-mountain-array/
 */
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

bool validMountainArray2(vector<int>& A) {
    int size = (int)A.size();
    if (size <= 0) return false;
    int index = 0;
    //先遍历上山，判断是否在递增
    while (index + 1 < size && A[index] < A[index + 1]) {
        index++;
    }
    
    //如果是遍历完成，说明不能下山不能构成山脉，或者是没有上山过
    if (index == 0 || index == size - 1) {
        return false;
    }
    
    //下山，判断是否在递减
    while (index + 1 < size && A[index] > A[index + 1]) {
        index++;
    }
    
    return index == size - 1;
}

/*
 122. 买卖股票的最佳时机 II
 解题思路：动态规划
 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/
 */
int maxProfit(vector<int>& prices) {
    int n = (int)prices.size();
    int dp0 = 0, dp1 = -prices[0];
    for (int i = 1; i < n; ++i) {
        int newDp0 = max(dp0, dp1 + prices[i]);
        int newDp1 = max(dp1, dp0 - prices[i]);
        dp0 = newDp0;
        dp1 = newDp1;
    }
    
    return dp0;
}

/*
 解题思路：直接比较后一个数是否比前一个数大，如果是的话加上他们的差值
 */
int maxProfit2(vector<int>& prices) {
    int res = 0;
    int size = (int)prices.size();
    for(int i = 1; i < size; ++i) {
        if(prices[i] > prices[i-1]) {
            res += prices[i] - prices[i-1];
        }
    }
    
    return res;
}

/************************************* 困难题 *********************************************/
/*
 127. 单词接龙
 解题思路：无，抄答案
 https://leetcode-cn.com/problems/word-ladder/
 */
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordDict(wordList.begin(), wordList.end());
    if (wordDict.find(endWord) == wordDict.end()){
        return 0;//Not FOUND 404
    }
    unordered_set<string> beginSet{beginWord};
    unordered_set<string> endSet{endWord};
    int step = 1;
    for (; !beginSet.empty();){
        unordered_set<string> tempSet;
        ++step;
        for (auto s : beginSet) {
            wordDict.erase(s);
        }
        for (auto s : beginSet) {
            for (int i = 0; i < s.size(); ++i){
                string str = s;
                for (char c = 'a'; c <= 'z'; ++c){
                    str[i] = c;
                    if (wordDict.find(str) == wordDict.end()){
                        continue;
                    }
                    if (endSet.find(str) != endSet.end()){
                        return step;
                    }
                    tempSet.insert(str);
                }
            }
        }
        if (tempSet.size() < endSet.size()){
            beginSet = tempSet;
        } else {
            beginSet = endSet;
            endSet = tempSet;
        }
    }
    
    return 0;
}

/*
 327. 区间和的个数
 解题思路：题意都没看懂...
 https://leetcode-cn.com/problems/count-of-range-sum/
 */
int countRangeSumRecursive(vector<long>& sum, int lower, int upper, int left, int right) {
    if (left == right) {
        return 0;
    } else {
        int mid = (left + right) / 2;
        int n1 = countRangeSumRecursive(sum, lower, upper, left, mid);
        int n2 = countRangeSumRecursive(sum, lower, upper, mid + 1, right);
        int ret = n1 + n2;
        
        // 首先统计下标对的数量
        int i = left;
        int l = mid + 1;
        int r = mid + 1;
        while (i <= mid) {
            while (l <= right && sum[l] - sum[i] < lower) l++;
            while (r <= right && sum[r] - sum[i] <= upper) r++;
            ret += (r - l);
            i++;
        }
        
        // 随后合并两个排序数组
        vector<int> sorted(right - left + 1);
        int p1 = left, p2 = mid + 1;
        int p = 0;
        while (p1 <= mid || p2 <= right) {
            if (p1 > mid) {
                sorted[p++] = sum[p2++];
            } else if (p2 > right) {
                sorted[p++] = sum[p1++];
            } else {
                if (sum[p1] < sum[p2]) {
                    sorted[p++] = sum[p1++];
                } else {
                    sorted[p++] = sum[p2++];
                }
            }
        }
        for (int i = 0; i < sorted.size(); i++) {
            sum[left + i] = sorted[i];
        }
        return ret;
    }
}

int countRangeSum(vector<int>& nums, int lower, int upper) {
    long s = 0;
    vector<long> sum{0};
    for(auto& v: nums) {
        s += v;
        sum.push_back(s);
    }
    
    return countRangeSumRecursive(sum, lower, upper, 0, sum.size() - 1);
}

int main(int argc, const char * argv[]) {
    vector<int> nums1 = {1, 2, 2, 1};
    vector<int> nums2 = {2, 2};
    vector<int> res1 = intersection(nums1, nums2);
    
    vector<int> nums3 = {0, 1, 2, 1, 2};
    bool res2 = validMountainArray(nums3);
    cout << "validMountainArray:" << res2 << endl;
    
    vector<int> nums4 = {-2, 5, -1};
    int res4 = countRangeSum(nums4, -2, 2);
    cout << "validMountainArray:" << res4 << endl;
    
    return 0;
}
