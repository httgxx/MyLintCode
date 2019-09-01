/*
 * @lc app=lintcode id=95 lang=cpp
 *
 * [95] Validate Binary Search Tree
 *
 * https://www.lintcode.com/problem/validate-binary-search-tree/description
 *
 * lintcode
 * Medium (25.00%)
 * Total Accepted:    40909
 * Total Submissions: 160018
 * Testcase Example:  '{-1}\n'
 *
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 * 
 * Assume a BST is defined as follows:
 * 
 * - The left subtree of a node contains only nodes with keys **less than** the
 * node's key.
 * - The right subtree of a node contains only nodes with keys **greater than**
 * the node's key.
 * - Both the left and right subtrees must also be binary search trees.
 * - A single node tree is a BST
 *
 * Example 1:
 * Input:  {-1}
 * Output：true
 * Explanation：
 * For the following binary tree（only one node）:
 * 	      -1
 * This is a binary search tree.
 *
 * Example 2:
 * Input:  {2,1,4,#,#,3,5}
 * Output: true
 * For the following binary tree:
 * 	  2
 * 	 / \
 * 	1   4
 * 	   / \
 * 	  3   5
 * This is a binary search tree.
 * 
 * @Category BST遍历
 * @Idea
 * S1: 分治法 递归
 * valid(root) = !root || (min<root<right && valid(root->left) && vald(root->right))
 * valid(root->left) = !(root->left) ||
 *  (min<root->left && root<root->right) && valid(root->left->left) && valid(root->left->right)
 * valid(root->right) = !(root->right) ||
 *  (root<root->right && root->right<max) && valid(root->right->left) && valid(root->right->right)
 * => 总结归纳出递归函数
 *  helper(root, min, max) = !root ||
 *  (min<root<max && helper(root->left, root->val, max) && helper(root, root->val, max)
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
     * @param root: The root of binary tree.
     * @return: True if the binary tree is BST, or false
     */
    // S1: 分治 递归 T=O(n) S=O(n)堆栈空间消耗
    bool isValidBST(TreeNode * root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
    bool helper(TreeNode * root, long mn, long mx) {
        if (!root) return true;
        if (root->val <= mn || root->val >= mx) return false;
        return helper(root->left, mn, root->val) && helper(root->right, root->val, mx);
    }
};
