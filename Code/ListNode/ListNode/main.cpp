//
//  main.cpp
//  ListNode
//
//  Created by Lawrence on 2020/10/20.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x):val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/***************************** 辅助方法 *****************************/
ListNode *listWithArray(vector<int> &arr) {
    ListNode *list = new ListNode(-1);
    ListNode *curr = list;
    for (int i = 0; i < arr.size(); i++) {
        ListNode *node = new ListNode(arr[i]);
        curr->next = node;
        curr = curr->next;
    }
    
    return list->next;
}


/*
 141.环形链表
 解题思路：快慢指针思想
 https://leetcode-cn.com/problems/linked-list-cycle/
 */
bool hasCycle(ListNode *head) {
    if (head == NULL || head->next == NULL) return false;
    ListNode *slower = head;
    ListNode *faster = head;
    while (faster != NULL && faster->next != NULL) {
        faster = faster->next->next;
        slower = slower->next;
        if (slower == faster)
            return true;
    }
    
    return false;
}

/*
 142.环形链表二（判断是否有环，并且返回对应的环的节点）
 解题思路：快慢指针，判断是否有入环口
 https://leetcode-cn.com/problems/linked-list-cycle-ii/
 */
ListNode *detectCyle(ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    ListNode *faster = head;
    ListNode *slower = head;
    while (faster != NULL && faster->next != NULL) {
        faster= faster->next->next;
        slower = slower->next;
        if (slower == faster) {
            break;
        }
    }
    
    if (faster == NULL || faster->next == NULL) {
        return NULL;
    }
    
    slower = head;
    while (slower != faster) {
        slower = slower->next;
        faster = faster->next;
    }
    
    return slower;
}

/*
 206.链表反转
 解题思路：头插入法
 https://leetcode-cn.com/problems/reverse-linked-list/
 */
ListNode* reverseList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    ListNode *result = nullptr;
    while (head != nullptr) {
        ListNode *temp = head->next;
        head->next = result;
        result = head;
        head = temp;
    }
    
    return result;
}

/*
 1365. 有多少小于当前数字的数字
 https://leetcode-cn.com/problems/how-many-numbers-are-smaller-than-the-current-number/
 */
vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    vector<int> result = vector<int>();
    int size = (int)nums.size();
    if (size == 0) { return result; }
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (nums[j] < nums[i]) {
                count += 1;
            }
        }
        
        result.push_back(count);
    }
    
    return result;
}

/*
 83. 删除排序链表中的重复元素
 https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/
 */
ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return  head;
    }
    
    ListNode *curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->val == curr->next->val) {
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
    
    return head;
}

/*
 82. 删除排序链表中的重复元素 II
 https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/
 */
ListNode* deleteDuplicates2(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    //有序集合，内部使用红黑树实现
    map<int, int> map = {pair<int, int>(head->val, 1)};
    ListNode *p = head->next;
    while (p != nullptr) {
        if (map.count(p->val)) {
            map.erase(p->val);
        }
        
        map.insert(pair<int, int>(p->val, 1));
        p = p->next;
    }
    
    ListNode *result = new ListNode(-1);
    ListNode *curr = result;
    for (auto element = map.begin(); element != map.end(); element++) {
        curr->next = new ListNode(element->first);
        curr = curr->next;
    }
    
    return result->next;
}

/*
 876. 链表的中间结点
 解题思路：快慢指针
 https://leetcode-cn.com/problems/middle-of-the-linked-list/
 */
ListNode* middleNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    ListNode *slower = head;
    ListNode *faster = head;
    while (faster != nullptr && faster->next != nullptr) {
        faster = faster->next->next;
        slower = slower->next;
    }
    
    return slower;
}

/*
 剑指 Offer 22. 链表中倒数第k个节点
 https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/
 */
ListNode* getKthFromEnd(ListNode* head, int k) {
    if (head == nullptr) {return head;}
    int lenght = 0;
    ListNode *curr = head;
    while (curr != nullptr) {
        lenght++;
        curr = curr->next;
    }
    
    while(lenght > k) {
        head = head->next;
        lenght--;
    }
    
    return head;
}

/*
 1207. 独一无二的出现次数
 解题思路：hash map
 https://leetcode-cn.com/problems/unique-number-of-occurrences/
 */
bool uniqueOccurrences(vector<int>& arr) {
    int size = (int)arr.size();
    if (size <= 0) {
        return false;
    }
    
    //提升查找性能，内部使用hash实现快速查找
    unordered_map<int, int> map = {};
    for (int i = 0; i < size; i++) {
        map[arr[i]]++;
    }
    
    //通过set过滤相同的出现的个数
    unordered_set<int> set = {};
    for (auto element = map.begin(); element != map.end(); element++) {
        set.insert(element->second);
    }
    
    //通过判断map的个数是否与set的个数相符，如果不相符则表明有相同出现次数的数字
    return map.size() == set.size();
}

/*
 129. 求根到叶子节点数字之和
 解题思路：DFS+回溯
 https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/
 */
class TreeSumNumbers {
private:
    int result;
    vector<int> vecs;
    
    //数组求和
    int sum(vector<int> &vecs) {
        int sum = 0;
        for (int i = 0; i < vecs.size(); i++) {
            sum = sum * 10 + vecs[i];
        }
        
        return sum;
    }
    
    void traversal(TreeNode* root) {
        //两个节点都为空
        if (!root->left && !root->right) {
            result += sum(vecs);
            cout << "result:" << result << endl;
            return;
        }
        
        //左节点不为空
        if (root->left) {
            vecs.push_back(root->left->val);
            traversal(root->left);
            vecs.pop_back();
        }
        
        //右节点不为空
        if (root->right) {
            vecs.push_back(root->right->val);
            traversal(root->right);
            vecs.pop_back();
        }
    }
    
public:
    int sumNumbers(TreeNode* root) {
        vecs.clear();
        if (root == nullptr) {
            return 0;
        }
        
        vecs.push_back(root->val);
        traversal(root);
        return result;
    }
};

/*
 463. 岛屿的周长
 https://leetcode-cn.com/problems/island-perimeter/
 */
int islandPerimeter(vector<vector<int>>& grid) {
    int landH = (int)grid.size();
    int landW = (int)grid[0].size();
    if (landH <= 0) { return 0; }
    int result = 0;
    for (int i = 0; i < landH; i++) {
        for (int j = 0; j < landW; j++) {
            //判断是否为岛屿格子
            if (grid[i][j] == 1) {
                result += 4;
                //如果下面是岛屿 - 2
                if (i < landH - 1 && grid[i + 1][j] == 1) {
                    result -= 2;
                }
                
                //如果右边是岛屿 - 2
                if (j < landH - 1 && grid[i][j + 1]) {
                    result -= 2;
                }
            }
        }
    }
    
    return result;
}

int islandPerimeter2(vector<vector<int>>& grid) {
    int landH = (int)grid.size();
    int landW = (int)grid[0].size();
    if (landH <= 0) { return 0; }
    int result = 0;
    for (int i = 0; i < landH; i++) {
        for (int j = 0; j < landW; j++) {
            //上边缘
            if (i == 0 && grid[i][j] == 1) { result++; }
            //下边缘
            if (i == landH - 1 && grid[i][j] == 1) { result++; }
            //左边缘
            if (j == 0 && grid[i][j] == 1) { result++; }
            //右边缘
            if (j == landW - 1 && grid[i][j] == 1) { result++; }
            //计算岛不是边界的边缘
            if (grid[i][j] == 1) { //计算岛格的左边和下边是否是湖格
                if (i < landH - 1 && grid[i + 1][j] == 0) result++;
                if (j < landW - 1 && grid[i][j + 1] == 0) result++;
            } else if (grid[i][j] == 0) { //计算湖格的左边和下边是否是岛格
                if (i < landH - 1 && grid[i + 1][j] == 1) result++;
                if (j < landW - 1 && grid[i][j + 1] == 1) result++;
            }
        }
    }
    
    return result;
}

/*************************************精选Top 100**********************************/
vector<int> twoSum(vector<int>& nums, int target) {
    //使用hasmap记录出现数字的索引，避免需要重复遍历
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        auto element = map.find(target - nums[i]);
        if (element != map.end()) {
            return {element->second, i};
        }
        
        map[nums[i]] = i;
    }
    
    return {};
}

/*
 148. 排序链表
 https://leetcode-cn.com/problems/sort-list/
*/
ListNode* sortList(ListNode* head) {
    //复杂度太高，遍历链表为O(n) 链表排序O(n)(具体内部实现不知，粗略计算可能是快排)
    //开辟了额外的内存空间，O(n) 重新生成链表为O(n)，所以总体的复杂度初略估计是O(n)
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    vector<int> vecs;
    while (head != nullptr) {
        vecs.push_back(head->val);
        head = head->next;
    }
    
    sort(vecs.begin(), vecs.end());
    ListNode *result = new ListNode(-1);
    ListNode *curr = result;
    for (int i = 0; i < vecs.size(); i++) {
        curr->next = new ListNode(vecs[i]);
        curr = curr->next;
    }
    
    return result->next;
}

/*
 328. 奇偶链表
 https://leetcode-cn.com/problems/odd-even-linked-list/
 */
ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    int index = 0;
    ListNode *l1 = nullptr;
    ListNode *l2 = nullptr;
    ListNode *curr1 = nullptr;
    ListNode *curr2 = nullptr;
    while (head != nullptr) {
        ListNode *temp = head->next;
        if (index % 2 == 0) {
            head->next = NULL;
            if (l1 == nullptr) {
                l1 = head;
                curr1 = l1;
            } else {
                curr1->next = head;
                curr1 = curr1->next;
            }
        } else {
            head->next = NULL;
            if (l2 == nullptr) {
                l2 = head;
                curr2 = l2;
            } else {
                curr2->next = head;
                curr2 = curr2->next;
            }
        }
        
        head = temp;
        index++;
    }
    
    ListNode *res = new ListNode(-1);
    ListNode *curr = res;
    while (l1 != nullptr || l2 != nullptr) {
        if (l1 != nullptr) {
            curr->next = l1;
            curr = curr->next;
            l1 = l1->next;
        } else {
            curr->next = l2;
            curr = curr->next;
            l2 = l2->next;
        }
    }
    
    return res->next;
}

ListNode* oddEvenList2(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    int index = 0;
    ListNode *even = nullptr;
    ListNode *odd = nullptr;
    ListNode *even_curr = nullptr;
    ListNode *odd_curr = nullptr;
    while (head != nullptr) {
        ListNode *temp = head->next;
        if (index % 2 == 0) {
            head->next = NULL;
            if (even == nullptr) {
                even = head;
                even_curr = even;
            } else {
                even_curr->next = head;
                even_curr = even_curr->next;
            }
        } else {
            head->next = NULL;
            if (odd == nullptr) {
                odd = head;
                odd_curr = odd;
            } else {
                odd_curr->next = head;
                odd_curr = odd_curr->next;
            }
        }
        
        head = temp;
        index++;
    }
    
    even_curr->next = odd;
    return even;
}

/*
 147. 对链表进行插入排序
 https://leetcode-cn.com/problems/insertion-sort-list/
 */
ListNode* insertionSortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    ListNode *p = nullptr;
    ListNode *q = nullptr;
    for (p = head; p != nullptr; p = p->next) {
        for (q = head; q->next != nullptr; q = q->next) {
            if (q->val > q->next->val) {
                int temp = q->val;
                q->val = q->next->val;
                q->next->val = temp;
            }
        }
    }
    
    return head;
}

ListNode* insertionSortList2(ListNode* head) {
    if(head == nullptr || head->next == nullptr) {
        return head;
    }
        
    ListNode *newhead = new ListNode(0);
    newhead->next = head;
    
    ListNode *pre = newhead;    //插入位置的前一个结点
    ListNode *cur = head;       //当前要插入的结点
    ListNode *p = newhead, *q = cur;    //p、q分别表示当前结点cur的前、后结点
    while(cur != nullptr) {
        q = cur->next;
        pre = newhead;
        while(pre->next != nullptr && pre->next->val < cur->val) {   //找到插入位置
            pre = pre->next;
        }
        
        if(pre->next == cur) {
            p = p->next;
        } else {
            cur->next = pre->next;
            pre->next = cur;
            p->next = q;
        }
        
        cur = q;
    }
    
    return newhead->next;
}

/** 判断CPU的大小端 */
union endian {
    char c;
    int i;
}en;

void isBigEndian() {
    //判断是大端模式还是小端模式
    en.i = 1;
    if (en.c == 1) {
        printf("little endian\n");
    } else {
        printf("big endian\n");
    }
}

int main(int argc, const char * argv[]) {
    ListNode *head = new ListNode(1);
    ListNode *node1 = new ListNode(2);
    head->next = node1;
    ListNode *node2 = new ListNode(3);
    node1->next = node2;
    ListNode *node3 = new ListNode(4);
    node2->next = node3;
    node3->next = node1;
    
    ListNode *node = detectCyle(head);
    cout << node->val << endl;
    
    vector<int> arr = {26, 2, 16, 16, 5, 5, 26, 2, 5, 20, 20, 5, 2, 20, 2, 2, 20, 2, 16, 20, 16, 17, 16, 2, 16, 20, 26, 16};
    bool result = uniqueOccurrences(arr);
    cout << "result = " << result << endl;
    
    vector<int> vecs = {1, 1, 1, 2, 3};
    ListNode *list = listWithArray(vecs);
    ListNode *resultList = deleteDuplicates2(list);
    cout << "deleteDuplicates2:" << resultList->val << endl;
    
    TreeNode *root = new TreeNode(4);
    TreeNode *rl = new TreeNode(9);
    TreeNode *rr = new TreeNode(0);
    root->left = rl;
    root->right = rr;
    TreeNode *rl1 = new TreeNode(5);
    TreeNode *rr1 = new TreeNode(1);
    rl->left = rl1;
    rl->right = rr1;
    
    TreeSumNumbers sumNum = TreeSumNumbers();
    int total = sumNum.sumNumbers(root);
    cout << "sumNumber = " << total << endl;
    
    vector<int> vecs2 = {1, 2, 3, 4, 5};
    ListNode *list2 = listWithArray(vecs2);
    ListNode *res1 = oddEvenList(list2);
    
    cout << "insertionSortList" << endl;
    vector<int> vecs3 = {4, 2, 1, 5, 3};
    ListNode *list3 = listWithArray(vecs3);
    ListNode *res2 = insertionSortList2(list3);
    while (res2 != nullptr) {
        cout << res2->val << endl;
        res2 = res2->next;
    }

    return 0;
}
