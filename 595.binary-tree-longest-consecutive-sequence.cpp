/*
 * @lc app=lintcode id=595 lang=cpp
 *
 * [595] Binary Tree Longest Consecutive Sequence
 *
 * https://www.lintcode.com/problem/binary-tree-longest-consecutive-sequence/description
 *
 * lintcode
 * Easy (37.00%)
 * Total Accepted:    10421
 * Total Submissions: 28115
 * Testcase Example:  '{1,#,3,2,4,#,#,#,5}\n'
 *
 * Given a binary tree, find the length of the longest consecutive sequence
 * path.
 * 
 * The path refers to any sequence of nodes from some starting node to any node
 * in the tree along the parent-child connections. The longest consecutive path
 * need to be from parent to child (`cannot be the reverse`).
 * 
 * Example 1:
 * Input:
 *    1
 *     \
 *      3
 *     / \
 *    2   4
 *         \
 *          5
 * Output:3
 * Explanation:
 * Longest consecutive sequence path is 3-4-5, so return 3.
 *
 * Example 2:
 * Input:
 *    2
 *     \
 *      3
 *     / 
 *   2    
 *  / 
 * 1
 * Output:2
 * Explanation:
 * Longest consecutive sequence path is 2-3,not 3-2-1, so return 2.
 *  
 * @Category 二叉树遍历
 * @Question 求二叉树最长连续递增序列,路径只能从上到下(父到子)
 * @Idea
 * S1: 先序遍历 DFS 递归 // T=O(n) S=O(n)堆栈空间花费
 *   连续  => 子==父+1
 *   父到子=> 先序遍历(根-左-右),每访问一个结点: if(子==父+1) ++路径长; else 路径长=1; res=max(res,路径长)
 * S2: 分治
 * 
 * 
 * /
/
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
     * @param root: the root of binary tree
     * @return: the length of the longest consecutive sequence path
     */
    // S1: DFS T=O(n) S=O(n)堆栈空间花费
    int longestConsecutive(TreeNode * root) {
        if (!root) { return 0; } // corner case
        int res = 0;
        dfs(root, root->val, 0, res); // Trick!!!pre初始为root->val可因!=root->val+1而初始len=1 
        return res;
    }
    void dfs(TreeNode *root, int pre, int len, int &res) { // res会被更新,传引用
        if (!root) return;                    // 递归到空子节点,递归返回
        if (root->val == pre + 1) { ++len; }  // 1.根: 子==父+1 => 连续 => ++len
        else { len = 1; }                     //          子!=父+1 => 不再连续 => len=1
        res = max(res, len);                  // 更新最长路径值
        dfs(root->left, root->val, len, res); // 2.左支 
        dfs(root->right, root->val, len, res);// 3.右支
    }
};
