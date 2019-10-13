/*
 * @lc app=lintcode id=177 lang=cpp
 *
 * [177] Convert Sorted Array to Binary Search Tree With  Minimal Height
 *
 * https://www.lintcode.com/problem/convert-sorted-array-to-binary-search-tree-with-minimal-height/description
 *
 * lintcode
 * Easy (34.00%)
 * Total Accepted:    10737
 * Total Submissions: 31362
 * Testcase Example:  '[]'
 *
 * Given a sorted (increasing order) array, Convert it to create a binary
 * search tree with minimal height.
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
 * 
 * Example 1:
 * Input: []
 * Output:  {}
 * Explanation: The binary search tree is null
 * Example 2:
 * Input: [1,2,3,4,5,6,7]
 * Output:  {4,2,6,1,3,5,7}
 * Explanation:
 * A binary search tree with minimal height.
 * 
 *       4
 *     /   \
 *    2     6
 *   / \    / \
 *  1   3  5   7
 * 
 * @Category BFS
 * @Idea 分治递归 中点做根
 * T=O(n) S=O(n)栈
 * 
 */

class Solution {
public:
    /*
     * @param A: an integer array
     * @return: A tree node
     */
    // S1: 分治递归 中点做根+左右分别递归 T=O(n) S=O(1) + 栈空间
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0 , nums.size() - 1);
    }
    TreeNode* helper(vector<int>& nums, int left, int right) {
        if (left > right) { return NULL; }
        int mid = left + (right - left) / 2;
        TreeNode *cur = new TreeNode(nums[mid]);
        cur->left = helper(nums, left, mid - 1);
        cur->right = helper(nums, mid + 1, right);
        return cur;
    }

    // S2: 分治递归 中点做根+左右分别递归 T=O(n) S=O(n) + 栈空间
    TreeNode* sortedArrayToBST2(vector<int>& nums) {
        if (nums.empty()) { return NULL; }
        int mid = nums.size() / 2;
        TreeNode *cur = new TreeNode(nums[mid]);
        vector<int> left(nums.begin(), nums.begin() + mid), //新建区间
                    right(nums.begin() + mid + 1, nums.end());
        cur->left = sortedArrayToBST(left);
        cur->right = sortedArrayToBST(right);
        return cur;
    }
};
