/*
 * @lc app=lintcode id=68 lang=cpp
 *
 * [68] Binary Tree Postorder Traversal
 *
 * https://www.lintcode.com/problem/binary-tree-postorder-traversal/description
 *
 * lintcode
 * Easy (47.00%)
 * Total Accepted:    31637
 * Total Submissions: 66028
 * Testcase Example:  '{1,2,3}\n'
 *
 * Given a binary tree, return the postorder traversal of its nodes' values.
 * 
 * Followup: 若无需返回结果只需打印遍历结果,能否除stack外不花费额外空间?
 * 
 * S1: 
 * S2: 根->右->左 + 反序(从头插入result)
 * 
 */
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param root: A Tree
     * @return: Postorder in ArrayList which contains node values.
     */
    // S1: stack + pre
    // 入栈顺序=根->右1->左1, 出栈顺序=左支路->右支路->根, 出栈时加入结果集
    // T=O(n) S=O(n)
    vector<int> postorderTraversal1(TreeNode * root) {
        if (!root) return {};  // corner case: null tree
        vector<int> res;
        stack<TreeNode*> s{{root}};             // 入1:根
        TreeNode *pre = root;                   // 记录最后被访问的结点(初始=根)
        while (!s.empty()) {
            TreeNode *t = s.top();
            if ((!t->left && !t->right) ||      // 出栈case1:访问到左/右叶子结点
                t->left == pre ||               // 出栈case2:访问完左子后回到根(因为无右子)
                t->right == pre) {              // 出栈case3:访问完右子后回到根(因为左右子都访问完)
                s.pop();                        // 出栈顺序:左支路-右支路-根
                res.push_back(t->val);          // 出栈时加入结果集
                pre = t;                        // 更新最后被访问的结点
            } else {
                if (t->right) s.push(t->right); // 入2:右1
                if (t->left) s.push(t->left);   // 入3:左1
            }
        }
        return res;
    }

    // S2: stack + 反序(出栈时:根-右-左 => 输出时:左-右-根) 
    // 入栈顺序=根->左1->右1, 出栈顺序=根->右支路->左1, 出栈时倒序加入结果集(输出时自动反序)
    // T=O(n) S=O(n)
    vector<int> postorderTraversal2(TreeNode* root) {
        if (!root) return {};  // corner case: null tree
        vector<int> res;
        stack<TreeNode*> s{{root}}; // 入1:根
        while (!s.empty()) {
            TreeNode *t = s.top(); s.pop();   // 出栈顺序:根-右支路-左1
            res.insert(res.begin(), t->val);  // 出栈时倒序加入结果集(输出时自动反序)
            if (t->left) s.push(t->left);     // 入2:左1
            if (t->right) s.push(t->right);   // 入3:右1
        }
        return res;
    }

    // S3: stack + 反序(入栈时:根-右-左 => 输出时:左-右-根) 
    // 入栈顺序=根->右支路->左1, 入栈时倒序加入结果集(输出时自动反序)
    // T=O(n) S=O(n)
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode *p = root; // 入1:根
        while (!s.empty() || p) {
            while (p) {
                s.push(p);                        // 入栈顺序:根-右支路-左1
                res.insert(res.begin(), p->val);  // 入栈时倒序加入结果集(输出时自动反序)
                p = p->right;                     // 入2:右支路
            }
            p = s.top()->left; s.pop();           // 入3.左1
        }
        return res;
    }
};
