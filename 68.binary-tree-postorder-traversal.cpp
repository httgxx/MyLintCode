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
    vector<int> postorderTraversal1(TreeNode * root) {
        // write your code here
    }
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {};  // corner case: null tree
        vector<int> res;
        stack<TreeNode*> s{{root}};  // root in stack
        while (!s.empty()) {
            TreeNode *t = s.top(); s.pop();   // 1:root
            res.insert(res.begin(), t->val);  // (1,2,3):(root-right-left)=>reverse=>(left, right, root)
            if (t->left) s.push(t->left);     // (2,3):in stack(left,right)=>out stack(right, left)
            if (t->right) s.push(t->right);   
        }
        return res;
    }
};
