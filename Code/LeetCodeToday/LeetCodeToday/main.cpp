//
//  main.cpp
//  LeetCodeToday
//
//  Created by Lawrence on 2020/11/2.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <stack>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/******************************* 坚持不懈， 每日一题 ***********************************/

/*
 数组反转
 解题思路：前半部分与后半部分交换
 */
vector<int> reverseArrayList(vector<int> &arr) {
    int len = (int)arr.size();
    for (int i = 0; i < len/2; i++) {
        int temp = arr[len - i - 1];
        arr[len - i - 1] = arr[i];
        arr[i] = temp;
    }
    
    return arr;
}

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

/*
 1356. 根据数字二进制下 1 的数目排序
 https://leetcode-cn.com/problems/sort-integers-by-the-number-of-1-bits/
 */
int convertDecimalToBinary(int n) {
    int remainder = 0;
    int count = 0;
    while(n != 0) {
        remainder = n % 2;
        if (remainder == 1) count++;
        n /= 2;
    }
    
    return count;
}

vector<int> sortByBits(vector<int>& arr) {
    map<int, vector<int>> bits = {};
    for (int item: arr) {
        int temp = item;
        int count = convertDecimalToBinary(temp);
        if (bits.find(count) != bits.end()) {
            vector<int> vecs = bits.find(count)->second;
            vecs.push_back(item);
            bits[count] = vecs;
        } else {
            vector<int> vecs;
            vecs.push_back(item);
            bits[count] = vecs;
        }
    }
    
    vector<int> res;
    for (map<int, vector<int>>::iterator it = bits.begin(); it != bits.end(); it++) {
        vector<int> elements = it->second;
        if (elements.size()) {
            sort(elements.begin(), elements.end());
            res.insert(res.end(), elements.begin(), elements.end());
        }
    }
    
    return res;
}

vector<int> sortByBits2(vector<int> &arr) {
    vector<int> bit(10001, 0);
    for (auto item: arr) {
        bit[item] = convertDecimalToBinary(item);
    }
    
    sort(arr.begin(), arr.end(), [&](int x, int y) {
        if (bit[x] < bit[y]) {
            return true;
        }
        
        if (bit[x] > bit[y]) {
            return false;
        }
        
        return x < y;
    });
    
    return arr;
}

/*
 922. 按奇偶排序数组 II
 https://leetcode-cn.com/problems/sort-array-by-parity-ii/
 */
vector<int> sortArrayByParityII(vector<int>& A) {
    int len = (int)A.size();
    vector<int> nums1;
    vector<int> nums2;
    for (int i = 0; i < len; i++) {
        int ele = A[i];
        if (ele % 2 == 0) {
            nums1.push_back(ele);
        } else {
            nums2.push_back(ele);
        }
    }
    
    vector<int> res;
    for (int i = 0; i < len; i++) {
        //偶数索引
        if (i % 2 == 0) {
            res.push_back(nums1.back());
            nums1.pop_back();
        } else {
            res.push_back(nums2.back());
            nums2.pop_back();
        }
    }
    
    return res;
}

vector<int> sortArrayByParityII2(vector<int>& A) {
    int len = (int)A.size();
    vector<int> res(len);
    
    //偶数，把结果放入到res[0] res[2] res[4]...
    int i = 0;
    for (int x: A) {
        if (x % 2 == 0) {
            res[i] = x;
            i += 2;
        }
    }
    
    //奇数，把结果放入到res[1] res[3]...
    i = 1;
    for (int x: A) {
        if (x % 2 == 1) {
            res[i] = x;
            i += 2;
        }
    }
    
    return res;
}

/*
 1122. 数组的相对排序
 https://leetcode-cn.com/problems/relative-sort-array/
 */
vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    map<int, int> map;
    for (int ele: arr1) {
        map[ele]++;
    }
    
    vector<int> res;
    for (int i = 0; i < arr2.size(); i++) {
        if (map.find(arr2[i]) != map.end()) {
            int count = map.find(arr2[i])->second;
            while (count > 0) {
                res.push_back(arr2[i]);
                count--;
            }
            
            map.erase(arr2[i]);
        }
    }
    
    for (auto ele = map.begin(); ele != map.end(); ele++) {
        if (ele->second > 1) {
            int count = ele->second;
            while (count > 0) {
                res.push_back(ele->first);
                count--;
            }
        } else {
            res.push_back(ele->first);
        }
    }
    
    return res;
}

/*
 283. 移动零
 https://leetcode-cn.com/problems/move-zeroes/
 */
void moveZeroes(vector<int>& nums) {
    int size = (int)nums.size();
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i]) {
            nums[count] = nums[i];
            count++;
        }
    }
    
    for (int j = count; j < size; j++) {
        nums[j] = 0;
    }
}

/*
 242. 有效的字母异位词
 解题思路：排序，判断字符是否相等
 https://leetcode-cn.com/problems/valid-anagram/
 */
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    
    return s == t;
}

/************************************* 中等难度 *******************************************/
/*
 973. 最接近原点的 K 个点
 解题思路：直接抄答案
 https://leetcode-cn.com/problems/k-closest-points-to-origin/
 */
vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    nth_element(points.begin(), points.begin() + K, points.end(), [](auto&& l, auto&& r) {
        return l[0] * l[0] + l[1] * l[1] < r[0] * r[0] + r[1] *r[1];
    });
    
    points.resize(K);
    return points;
}

/*
 406. 根据身高重建队列
 https://leetcode-cn.com/problems/queue-reconstruction-by-height/
 */
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    // 身高从低到高排序
    sort(people.begin(), people.end());
    vector<vector<int>> res(people.size());
    // 遍历people
    for(auto & p : people){
        int count = -1; // 计算空位置或高度等于p[0]的位置
        for(int i = 0; i < res.size(); i++){
            // 位置上和我一样高或者如果一个位置是空的
            if(res[i].empty() || res[i][0] == p[0]) {
                count++;
            }
            // 数到第k个位置
            if(count == p[1]){
                res[i] = p;
                break;
            }
        }
    }
    
    return res;
}

vector<vector<int>> reconstructQueue2(vector<vector<int>>& people) {
    //身高降序排列，人数升序排列
    sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
        if(a[0] > b[0])
            return true;
        if(a[0] == b[0] && a[1] <b[1])
            return true;
        return false;
    });
    
    
    vector<vector<int>> res;
    for(int i = 0; i < people.size(); i++) {
        res.insert(res.begin() + people[i][1], people[i]);
    }
    
    return res;
}

/*
 222. 完全二叉树的节点个数
 解题思路：利用队列进行层次遍历
 https://leetcode-cn.com/problems/count-complete-tree-nodes/
 */
int countNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    int count = 0;
    deque<TreeNode *> queue;
    queue.push_back(root);
    while (!queue.empty()) {
        TreeNode *node = queue.front();
        queue.pop_front();
        count++;
        if (node->left != nullptr) {
            queue.push_back(node->left);
        }
        
        if (node->right != nullptr) {
            queue.push_back(node->right);
        }
    }
    
    return count;
}

int countNodes2(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes2(root->left) + countNodes2(root->right);
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
    
    vector<int> nums5 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> res5 = sortByBits(nums4);
    for (auto item: res5) {
        cout << "sortByBits:" << item << endl;
    }
    
    vector<int> nums6 = {4, 2, 5, 7};
    vector<int> res6 = sortArrayByParityII(nums6);
    for (auto item: res6) {
        cout << "sortArrayByParityII:" << item << endl;
    }
    
    vector<int> nums7 = {2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19};
    vector<int> nums8 = {2, 1, 4, 3, 9, 6};
    vector<int> res7 = relativeSortArray(nums7, nums8);
    for (auto item: res7) {
        cout << "relativeSortArray:" << item << endl;
    }
    
    cout << "---- reconstructQueue: ----" << endl;
    vector<vector<int>> nums9 = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5,2}};
    vector<vector<int>> res8 = reconstructQueue2(nums9);
    for (vector<int> item: res8) {
        cout << "["<< item.front() << ", " << item.back() << "]" << endl;
    }
    
    cout << "moveZeroes" << endl;
    vector<int> nums10 = {0, 1, 0, 3, 12};
    moveZeroes(nums10);
    
    return 0;
}
