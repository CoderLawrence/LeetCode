//
//  main.cpp
//  Tree
//
//  Created by Lawrence on 2020/11/25.
//

#include <iostream>
#include <deque>
#include <vector>

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

int main(int argc, const char * argv[]) {
    return 0;
}
