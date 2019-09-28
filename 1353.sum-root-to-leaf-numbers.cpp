/*
 * @lc app=lintcode id=1353 lang=cpp
 *
 * [1353] Sum Root to Leaf Numbers
 *
 * https://www.lintcode.com/problem/sum-root-to-leaf-numbers/description
 *
 * lintcode
 * Medium (69.00%)
 * Total Accepted:    1101
 * Total Submissions: 1573
 * Testcase Example:  '{1,2,3}'
 *
 * Given a binary tree containing digits from `0-9` only, each root-to-leaf
 * path could represent a number.
 * 
 * An example is the root-to-leaf path `1->2->3` which represents the number
 * `123`.
 * 
 * Find the total sum of all root-to-leaf numbers.
 * 
 * Example:
 * Input: {1,2,3}
 *     1
 *    / \
 *   2   3
 * Output: 25
 * Explanation:
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 * Therefore, sum = 12 + 13 = 25.
 * 
 * Example 2:
 * Input: {4,9,0,5,1}
 *     4
 *    / \
 *   9   0
 *  / \
 * 5   1
 * Output: 1026
 * Explanation:
 * The root-to-leaf path 4->9->5 represents the number 495.
 * The root-to-leaf path 4->9->1 represents the number 491.
 * The root-to-leaf path 4->0 represents the number 40.
 * Therefore, sum = 495 + 491 + 40 = 1026.
 * 
 * @Category Tree - Divide & Conquer
 * @Idea
 * S1: DFS
 * return dfs(root,0)
 * dfs(root, sum)
 *    if(!root) return sum 
 *    sum = sum * 10 + root
 *    if(!left && !right) return sum
 *    return dfs(left, sum) + dfs(right, sum)
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
     * @param root: the root of the tree
     * @return: the total sum of all root-to-leaf numbers
     */
    int sumNumbers(TreeNode* root) {
        return sumNumbersDFS(root, 0);
    }
    int sumNumbersDFS(TreeNode* root, int sum) {
        if (!root) { return 0; }                            // dfs到底开始返回                            
        sum = sum * 10 + root->val;                         // 访问根
        if (!root->left && !root->right) { return sum; }    // 叶子结点            
        return sumNumbersDFS(root->left, sum) +             // 访问左子+访问右子 divid & conquer
            sumNumbersDFS(root->right, sum);
    }
};
