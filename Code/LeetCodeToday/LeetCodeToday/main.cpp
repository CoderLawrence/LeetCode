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
#include <string>
#include <sstream>

/*
 坚持不懈， 每日一题，加油！！！
 */

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//MARK: - ------------- 简单题 ------------------------
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

/*
 1370. 上升下降字符串
 解题思路：桶排序
 https://leetcode-cn.com/problems/increasing-decreasing-string/
 */
string sortString(string s) {
    //记录字符出现的次数，26个字母
    vector<int> sVec(26);
    for (char &c: s) {
        sVec[c - 'a']++;
    }
    
    string res;
    while (res.length() < s.length()) {
        //步骤1，2，3
        for (int i = 0; i < 26; i++) {
            if (sVec[i]) {
                res.push_back(i + 'a');
                sVec[i]--;
            }
        }
        //步骤五
        for (int i = 25; i >= 0; i--) {
            if (sVec[i]) {
                res.push_back(i + 'a');
                sVec[i]--;
            }
        }
    }
    
    return res;
}

string sortString2(string s) {
    sort(s.begin(), s.end());
    string res;
    while (s.length()) {
        //1，2，3步骤
        for ( string::iterator it = s.begin(); it < s.end(); it++) {
            char last_c = res[res.length() - 1];
            if (*it > last_c  || res.length() == 0) {
                res += *it;
                s.erase(it);
                it--;
            }
        }
        
        //步骤4
        //排序后的字符串，最后一个就是最大值
        res += s[s.length() - 1];
        s.pop_back();
        //倒序遍历
        for (string::iterator it = s.end() - 1; it > s.begin(); it--) {
            char last_c = res[res.length() - 1];
            if (*it < last_c) {
                res += *it;
                s.erase(it);
                it--;
            }
        }
        
        //又是一轮从小到大，先提取第一个最小字符
        if (s.length()) {
            res += s[0];
            s.erase(s.begin());
        }
    }
    
    return res;
}

/*
 976. 三角形的最大周长
 https://leetcode-cn.com/problems/largest-perimeter-triangle/
 */
int largestPerimeter(vector<int>& A) {
    int size = (int)A.size();
    if (size < 3) return 0;
    sort(A.begin(), A.end());
    for (int i = size - 1; i >= 2; i--) {
        if (A[i - 1] + A[i - 2] > A[i])
            return  A[i] + A[i - 1] + A[i - 2];
    }
    
    return 0;
}

/*
 剑指 Offer 03. 数组中重复的数字
 https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/
 */
int findRepeatNumber(vector<int>& nums) {
    unordered_map<int, int> map;
    for (auto ele: nums) {
        if (map.find(ele) != map.end()) {
            return ele;
        }
        
        map[ele]++;
    }
    
    return -1;
}

/*
 860. 柠檬水找零
 https://leetcode-cn.com/problems/lemonade-change/
 */
bool lemonadeChange(vector<int>& bills) {
    unordered_map<int, int> cash;
    for (auto pay: bills) {
        if (pay == 5) {
            cash[pay]++;
        } else {
            if (pay == 10) {
                if (cash[5] >= 1) {
                    cash[5]--;
                    cash[pay]++;
                } else {
                    return false;
                }
            } else if (pay == 20) {
                if (cash[5] >= 1 && cash[10] >= 1) {
                    cash[5]--;
                    cash[10]--;
                    cash[pay]++;
                } else if (cash[5] >= 3) {
                    cash[5] -= 3;
                    cash[pay]++;
                } else {
                    return false;
                }
            }
        }
    }
    
    return true;
}

bool lemonadeChange2(vector<int>& bills) {
    int five_num = 0;
    int ten_num = 0;
    for (auto pay: bills) {
        if (pay == 5) {
            five_num++;
        } else {
            if (pay == 10) {
                if (five_num >= 1) {
                    five_num--;
                    ten_num++;
                } else {
                    return false;
                }
            } else if (pay == 20) {
                if (five_num >= 1 && ten_num >= 1) {
                    five_num--;
                    ten_num--;
                } else if (five_num >= 3) {
                    five_num -= 3;
                } else {
                    return false;
                }
            }
        }
    }
    
    return true;
}

/*
 290. 单词规律
 https://leetcode-cn.com/problems/word-pattern/
 */
vector<string> getWords(string s) {
    vector<string> words;
    istringstream iss(s);
    string token;
    while(getline(iss, token, ' ')) {
        words.push_back(token);
    }
    
    return words;
}

bool wordPattern(string pattern, string s) {
    vector<string> words = getWords(s);
    int p_len = (int)pattern.length();
    int s_len = (int)words.size();
    if (p_len != s_len) {
        return false;
    }
    
    unordered_map<char, string> map;
    for (int i = 0; i < p_len; i++) {
        map[pattern[i]] = words[i];
    }
    
    for (int i = 0; i < p_len; i++) {
        if (map.find(pattern[i])->second != words[i]) {
            return false;
        } else {
            continue;
        }
    }
    
    return true;
}

//MARK: - ------------ 中等难度 ---------------------
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

/*
 98. 验证二叉搜索树
 解题思路：二叉搜索树的中序遍历是升序的，
        所以利用升序的性质判断后一个节点的值是否大于前一个节点的值
 题目陷阱：不能单纯比较节点的左节点和有节点的值的大小，同时还需注意节点的值与根节点的值的比较
 二叉搜索树的性质：右子树的值必须大于根节点的的值，左子树的值必须小于根节点的值
 */
bool isValidBST(TreeNode* root) {
    stack<TreeNode*> stack;
    long long inorder = (long long)INT_MIN - 1;
    while (!stack.empty() || root != nullptr) {
        while (root != nullptr) {
            stack.push(root);
            root = root -> left;
        }
        root = stack.top();
        stack.pop();
        // 如果中序遍历得到的节点的值小于等于前一个 inorder，说明不是二叉搜索树
        if (root -> val <= inorder) {
            return false;
        }
        inorder = root -> val;
        root = root -> right;
    }
    return true;
}

//使用中旬遍历+二叉树搜索树中序遍历是升序的特性
class TTisValidBST {
private:
    vector<int> vec;
    void traversal(TreeNode* root) {
        if (root == NULL) return;
        traversal(root->left);
        vec.push_back(root->val); // 将二叉搜索树转换为有序数组
        traversal(root->right);
    }
public:
    bool isValidBST(TreeNode* root) {
        vec.clear(); // 不加这句在leetcode上也可以过，但最好加上
        traversal(root);
        for (int i = 1; i < vec.size(); i++) {
            // 注意要小于等于，搜索树里不能有相同元素
            if (vec[i] <= vec[i - 1]) return false;
        }
        return true;
    }
};

/*
 34. 在排序数组中查找元素的第一个和最后一个位置
 https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 */
class TTSearchRange {
private:
    int binarySearch(vector<int> & nums, int target, bool flag) {
        int res = -1;
        int low = 0;
        int high = (int)nums.size() - 1;
        while (low <= high) {
            int mid = (low + (high - low) / 2);
            if (nums[mid] == target) {
                res = mid;
                if (flag) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else if (nums[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return res;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int size = (int)nums.size();
        if (size == 0) return {-1, -1};
        if (size == 1 && nums[0] == target) return {0, 0};
        vector<int> res = {-1, -1};
        res[0] = binarySearch(nums, target, true);
        res[1] = binarySearch(nums, target, false);
        return res;
    }
};

/*
 49. 字母异位词分组
 https://leetcode-cn.com/problems/group-anagrams/
 */
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> map;
    for (string str: strs) {
        string ele = str;
        sort(ele.begin(), ele.end());
        if (map.count(ele)) {
            vector<string> vecs = map[ele];
            vecs.push_back(str);
            map[ele] = vecs;
        } else {
            vector<string> vecs = {str};
            map[ele] = vecs;
        }
    }
    
    vector<vector<string>> res_strs;
    for (auto ele = map.begin(); ele != map.end(); ele++) {
        res_strs.push_back(ele->second);
    }
    
    return res_strs;
}

/*
 738. 单调递增的数字
 https://leetcode-cn.com/problems/monotone-increasing-digits/
 */
int monotoneIncreasingDigits(int N) {
    string strN = to_string(N);
    int len = (int)strN.length();
    int flag = len;
    for (int i = len - 1; i > 0; i--) {
        if (strN[i - 1] > strN[i]) {
            strN[i - 1]--;
            flag = i;
        }
    }
    
    for (int i = flag; i < len; i++) {
        strN[i] = '9';
    }
    
    return stoi(strN);
}

//MARK: - --------------- 困难题 -----------------

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

/*
 164. 最大间距
 https://leetcode-cn.com/problems/maximum-gap/
 */
int maximumGap(vector<int>& nums) {
    int size = (int)nums.size();
    if (size < 2) return 0;
    sort(nums.begin(), nums.end());
    int result = 0;
    for (int i = 0; i < size - 1; i++) {
        int num = nums[i + 1] - nums[i];
        if (num > result) {
            result = num;
        }
    }
    
    return result;
}

/*
 454. 四数相加 II
 https://leetcode-cn.com/problems/4sum-ii/
 */
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    //求出A与B的所有情况，把a跟b的和出现的情况记录到map中，复杂度为O(n2)
    unordered_map<int, int> map;
    for (auto a: A) {
        for (auto b: B) {
            map[a + b]++;
        }
    }
    
    int count = 0;
    for (auto c: C) {
        for (auto d: D) {
            // 判断c跟d的和的负值是否存在于sumMap中，存在的话则计数增加
            int sum = c + d;
            if (map[-sum]) {
                count += map[-sum];
            }
        }
    }
    
    return count;
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
    
    cout << sortString2("spo") << endl;
    
    vector<int> nums11 = {1, 3, 6, 9};
    cout << "maximumGap:" << maximumGap(nums11) << endl;
    
    cout << "searchRange" << endl;
    vector<int> nums12 = {1, 1, 2};
    TTSearchRange searchRange;
    searchRange.searchRange(nums12, 1);
    
    cout << "groupAnagrams" << endl;
    vector<string> nums13 = {"eat","tea","tan","ate","nat","bat"};
    groupAnagrams(nums13);
    
    cout << "wordPattern" << endl;
    wordPattern("abba", "dog cat cat dog");
    
    return 0;
}
