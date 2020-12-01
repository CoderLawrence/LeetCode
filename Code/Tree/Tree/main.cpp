//
//  main.cpp
//  Tree
//
//  Created by Lawrence on 2020/11/25.
//

#include <iostream>
#include <deque>
#include <vector>
#include <deque>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
 104. 二叉树的最大深度
 题解：题目的本意是每一个节点的左节点与有节点交换
 https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/
 */
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int height = 0;
    int levelSize = 1;
    deque<TreeNode *> queue;
    queue.push_back(root);
    while (!queue.empty()) {
        TreeNode *node = queue.front();
        queue.pop_front();
        levelSize--;
        if (node->left != nullptr) {
            queue.push_back(node->left);
        }
        
        if (node->right != nullptr) {
            queue.push_back(node->right);
        }
        
        if (levelSize == 0) {
            levelSize = (int)queue.size();
            height++;
        }
    }
    
    return height;
}

/*
 226. 翻转二叉树
 https://leetcode-cn.com/problems/invert-binary-tree/
 */
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) return root;
    deque<TreeNode *> queue;
    queue.push_back(root);
    while (!queue.empty()) {
        TreeNode *node = queue.front();
        queue.pop_front();
        TreeNode *temp_node = node->left;
        node->left = node->right;
        node->right = temp_node;
        
        if (node->left != nullptr) {
            queue.push_back(node->left);
        }
        
        if (node->right != nullptr) {
            queue.push_back(node->right);
        }
    }
    
    return root;
}

TreeNode* invertTree1(TreeNode* root) {
    //前序遍历
    if (root == nullptr) return root;
    TreeNode *temp_node = root->left;
    root->left = root->right;
    root->left = temp_node;
    invertTree1(root->left);
    invertTree1(root->right);
    
    return root;
}

TreeNode* invertTree2(TreeNode* root) {
    //后序遍历
    if (root == nullptr) return root;
    invertTree2(root->left);
    invertTree2(root->right);
    TreeNode *temp_node = root->left;
    root->left = root->right;
    root->left = temp_node;
    return root;
}

TreeNode* invertTree3(TreeNode* root) {
    //中序遍历
    if (root == nullptr) return root;
    invertTree3(root->left);
    TreeNode *temp_node = root->left;
    root->left = root->right;
    root->left = temp_node;
    //交换后的left就是之前的right
    invertTree3(root->left);
    return root;
}

/*
 94. 二叉树的中序遍历
 https://leetcode-cn.com/problems/binary-tree-inorder-traversal/
 */
void inorderTraversalNode(TreeNode* node, vector<int> vec) {
    if (node == nullptr) return;
    inorderTraversalNode(node->left, vec);
    vec.push_back(node->val);
    inorderTraversalNode(node->right, vec);
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> vec;
    inorderTraversalNode(root, vec);
    return vec;
}

/*
 102. 二叉树的层序遍历
 解题思路：层次遍历，然后记录每一层的元素，遍历完一层后把数据那一层数据清除
 https://leetcode-cn.com/problems/binary-tree-level-order-traversal/
 */
vector<vector<int>> levelOrder(TreeNode* root) {
    if (root == nullptr) return {};
    int level = 1;
    vector<vector<int>> res;
    deque<TreeNode *> queue;
    queue.push_back(root);
    vector<int> levelVecs;
    while (!queue.empty()) {
        TreeNode *node = queue.front();
        levelVecs.push_back(node->val);
        queue.pop_front();
        level--;
        if (node->left != nullptr) {
            queue.push_back(node->left);
        }
        
        if (node->right != nullptr) {
            queue.push_back(node->right);
        }
        
        if (level == 0) {
            res.push_back(levelVecs);
            levelVecs.clear();
        }
    }
    
    return res;
}

/*
 100. 相同的树
 https://leetcode-cn.com/problems/same-tree/
 */
bool isSameTree(TreeNode *p, TreeNode *q) {
    if (p == nullptr && q == nullptr) return true;
    if (p == nullptr || q == nullptr) return false;
    deque<TreeNode *> queue;
    queue.push_back(p);
    queue.push_back(q);
    while (!queue.empty()) {
        TreeNode *node_p = queue.front();
        queue.pop_front();
        TreeNode *node_q = queue.front();
        queue.pop_front();
        //如果两个节点为空，退出本次循环
        if (node_p == nullptr && node_q == nullptr) continue;
        //如果其中某一个节点为空，则两颗树不相同
        if (node_p != nullptr && node_p == nullptr) return false;
        if (node_p == nullptr && node_q != nullptr) return false;
        //如果某一个节点的值不相等，则两颗树不相同
        if (node_p->val != node_q->val) {
            return false;
        } else {
            queue.push_back(node_p->left);
            queue.push_back(node_q->left);
            queue.push_back(node_p->right);
            queue.push_back(node_q->right);
        }
    }
    
    return true;
}

/*
 114. 二叉树展开为链表
 解题思路：利用栈前序迭代遍历二叉树，然后清空左子节点
 https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/
 */
void flatten(TreeNode* root) {
    if (root == nullptr) return;
    TreeNode *last = nullptr;
    stack<TreeNode *> st;
    st.push(root);
    while(!st.empty()) {
        TreeNode *node = st.top();
        st.pop();
        
        if(node->right != nullptr) {
            st.push(node->right);
        }
        
        if(node->left != nullptr) {
            st.push(node->left);
        }
        
        if (last == nullptr) {
            last = root;
        } else {
            last->left = nullptr;
            last->right = node;
            last = node;
        }
    }
}

int main(int argc, const char * argv[]) {
    return 0;
}
