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
#include <queue>
#include <stack>
#include <unordered_map>

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
bool isSameTree(TreeNode *s, TreeNode *t) {
    //同时为空，说明树一起到底，两树相同
    if (s== nullptr && t == nullptr) {
        return true;
    }
    //说明有节点不为空，不是相同树
    if (t == nullptr || s == nullptr) {
        return false;
    }
    //如果节点的值不相同，不是相同树
    if (s->val != t->val) {
        return false;
    }
    
    return isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
}

bool isSameTree2(TreeNode *p, TreeNode *q) {
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

/*
 111. 二叉树的最小深度
 https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/
 */
int minDepth(TreeNode* root) {
    //如果根节点不存在，则树无高度
    if(root == nullptr) return 0;
    //如果叶子节点都为空，那么树的高度为1
    if(root->left == nullptr && root->right == nullptr) return 1;
    //获取最小路径值
    return min(minDepth(root->left), minDepth(root->right)) + 1;
}

/*
 572. 另一个树的子树
 https://leetcode-cn.com/problems/subtree-of-another-tree/
 */
bool isSubtree(TreeNode* s, TreeNode* t) {
    if (s == nullptr) return false;
    if (t == nullptr) return true;
    if (s->val == t->val && isSameTree(s, t)) {
        return true;
    }
    
    return isSubtree(s->left, t) || isSubtree(s->right, t);
}

/*
 993. 二叉树的堂兄弟节点
 https://leetcode-cn.com/problems/cousins-in-binary-tree/
 */
bool isCousins(TreeNode* root, int x, int y) {
    if (root == nullptr) return false;
    queue<TreeNode *> q;
    q.push(root);
    int flag = 2;
    while(!q.empty()) {
        int levelSize = (int)q.size();
        for (int i = 0; i < levelSize; i++) {
            TreeNode *node = q.front();
            q.pop();
            //如果是兄弟节点，则不符合
            if ((node->left != nullptr && node->right != nullptr) &&
                ((node->left->val == x && node->right->val == y) ||
                 (node->left->val == y && node->right->val == x))) {
                return false;
            }
            
            if (node->left != nullptr) {
                q.push(node->left);
                if (node->left->val == x || node->left->val == y) flag--;
            }
            
            if (node->right != nullptr) {
                q.push(node->right);
                if (node->right->val == x || node->right->val == y) flag--;
            }
        }
        
        
        //该层自发现一个，说明x,y不在同一层，返回false
        if (flag == 1) return false;
        //x,y在同一层，且前面为亲兄弟节点的情况已经排除，所以是堂兄弟
        if (flag == 0) return true;
    }
    
    return false;
}

bool traversalPathSum(TreeNode *root, int sum, int path) {
    cout << "path" << path << endl;
    if (root == nullptr) {
        return path == sum;
    }
    
    return traversalPathSum(root->left, sum, path + root->val) ||
    traversalPathSum(root->right, sum, path + root->val);
}

bool hasPathSum(TreeNode* root, int sum) {
    if (root == nullptr) return false;
    if (root->val == sum) return false;
    return traversalPathSum(root->left, sum, root->val) ||
    traversalPathSum(root->right, sum, root->val);
}

int main(int argc, const char * argv[]) {
    TreeNode *root = new TreeNode(5);
    TreeNode *node_1 = new TreeNode(4);
    root->left = node_1;
    TreeNode *node_2 = new TreeNode(8);
    root->right = node_2;
    TreeNode *node_3 = new TreeNode(11);
    node_1->left = node_3;
    TreeNode *node_4 = new TreeNode(13);
    node_2->left = node_4;
    TreeNode *node_5 = new TreeNode(4);
    node_2->right = node_5;
    TreeNode *node_6 = new TreeNode(7);
    node_3->left = node_6;
    TreeNode *node_7 = new TreeNode(2);
    node_3->right = node_7;
    TreeNode *node_8 = new TreeNode(1);
    node_5->right = node_8;
    
    cout << hasPathSum(root, 9) << endl;
    
    return 0;
}
