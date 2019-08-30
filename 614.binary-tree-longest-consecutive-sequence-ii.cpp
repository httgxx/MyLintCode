/*
 * @lc app=lintcode id=614 lang=cpp
 *
 * [614] Binary Tree Longest Consecutive Sequence II
 *
 * https://www.lintcode.com/problem/binary-tree-longest-consecutive-sequence-ii/description
 *
 * lintcode
 * Medium (39.00%)
 * Total Accepted:    5219
 * Total Submissions: 13191
 * Testcase Example:  '{1,2,0,3}\n'
 *
 * Given a binary tree, find the length(number of nodes) of the longest
 * consecutive sequence(Monotonic and adjacent node values differ by 1) path.
 * The path could be start and end at any node in the tree
 * 
 * Example
 * Example 1:
 * Input: {1,2,0,3}
 * Output: 4
 * Explanation:
 *      1
 *     / \
 *    2   0
 *   /
 *  3
 *  0-1-2-3
 * 
 * Example 2:
 * Input: {3,2,2}
 * Output: 2
 * Explanation:
 *    3
 *   / \
 *  2   2
 *  2-3
 * 
 * @Category 二叉树遍历
 * @Question 二叉树最长连续序列(递增或递减),可任意拐弯:上到下(父到子),下到上(子到父),左到右(左根右),右到左(右根左)
 * @Idea
 * 1.经过每个结点的最长连续序列长度=从该结点出发向下的(最长递增路径长度+最长递减路径)+1(该结点本身)
 * 2.分别对左右子递归,最大值=max(经过根的最长连续序列长度,经过左子的最长连续序列长度,经过右子的最长连续序列长度)
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
    // S: 分治 + 回溯 + diff // T=O(n) S=O(n)
    // 1.经过每个结点的最长连续序列长度=从该结点出发向下的(最长递增路径长度+最长递减路径)+1(该结点本身)
    // 2.分别对左右子递归,最大值=max(经过根的最长连续序列长度,经过左子的最长连续序列长度,经过右子的最长连续序列长度)
    int longestConsecutive2(TreeNode * root) {
        if (!root) return 0;
        // 经过1结点的最长连续序列长度=从该结点出发向下的(最长递增路径长度+最长递减路径)+1(该结点本身)
        int res = helper(root, 1) + helper(root, -1) + 1; // 1:从node到其子递增, -1:从node到其子递减
        return max(res, max(longestConsecutive2(root->left), longestConsecutive2(root->right))); // 求3者最大
    }
    int helper(TreeNode* node, int diff) { // 计算经过node的最长连续递增/减序列的长度
        if (!node) return 0;
        int left = 0, right = 0;
        if (node->left && node->val - node->left->val == diff) {  // 递归左子
            left = 1 + helper(node->left, diff);  // 1(node本身) + 经过node左子的最长连续长度 
        }
        if (node->right && node->val - node->right->val == diff) {// 递归右子
            right = 1 + helper(node->right, diff); // 1(node本身) + 经过node右子的最长连续长度
        }
        return max(left, right); // max(经过node的最长连续递增序列长度, 经过node的最长连递减续序列长度)
    }
};
