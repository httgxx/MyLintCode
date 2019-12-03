/*
 * @lc app=lintcode id=649 lang=cpp
 *
 * [649] Binary Tree Upside Down
 *
 * https://www.lintcode.com/problem/binary-tree-upside-down/description
 *
 * lintcode
 * Medium (54.00%)
 * Total Accepted:    3946
 * Total Submissions: 7190
 * Testcase Example:  '{1,2,3,4,5}\n'
 *
 * Given a binary tree where all the right nodes are either leaf nodes with a
 * sibling (a left node that shares the same parent node) or empty, flip it
 * upside down and turn it into a tree where the original right nodes turned
 * into left leaf nodes. Return the new root.
 * 
 * Example1
 * Input: {1,2,3,4,5}
 * Output: {4,5,2,#,#,3,1}
 * Explanation:
 * The input is
 *     1
 *    / \
 *   2   3
 *  / \
 * 4   5
 * and the output is
 *     4
 *    / \
 *   5   2
 *      / \
 *     3   1
 * 
 * Example2
 * Input: {1,2,3,4}
 * Output: {4,#,2,3,1}
 * Explanation:
 * The input is
 *     1
 *    / \
 *   2   3
 *  /
 * 4
 * and the output is
 * 4
 *  \
 *   2
 *  / \
 * 3   1
 * 
 * @Category BinaryTree Rotate clockwise
 * @Idea 二叉树 顺时针90翻转
 * 先判断根是否存在且其有没有左子,若否直接返回
 * 不停的对左子递归直到最左子开始翻转:左子->根,右子->左子,根->右子
 * 翻好后回到上一层左子继续翻转,直至翻转完整棵树
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
     * @param root: the root of binary tree
     * @return: new root
     */
    // S1: 递归 T=O(n) S=O(logn)栈空间
    // 先判断根是否存在且其有没有左子,若否直接返回
    // 不停的对左子递归直到最左子开始翻转:左子->根,右子->左子,根->右子
    // 翻好后回到上一层左子继续翻转,直至翻转完整棵树
    TreeNode * upsideDownBinaryTree1(TreeNode * root) {
        if (!root || !root->left) { return root; }  // 特例:无根或无左子则立返
        TreeNode *l = root->left, *r = root->right; 
        TreeNode *res = upsideDownBinaryTree(l);    // 递归到最左叶子res 
        l->left = r;                                // 旧右子->新左子
        l->right = root;                            // 旧根->新右子
        root->left = NULL;                          // 旧根左右子清空
        root->right = NULL;                         
        return res;                                 // 返回新根(旧左子)
    }

    // S2: 迭代 T=O(n) S=O(1)
    // 从上往下开始翻转，直至翻转到最左子节点
    TreeNode * upsideDownBinaryTree(TreeNode * root) {
        TreeNode *cur = root, *pre = NULL, *next = NULL, *tmp = NULL;
        while (cur) {
            next = cur->left;   // traverse当前左子
            cur->left = tmp;    // 旧右子->新左子
            tmp = cur->right;   // track当前右子成为下层旧右子
            cur->right = pre;   // 旧根->新右子
            pre = cur;          // track当前根成为下层旧根
            cur = next;         // 进到下层左子
        }
        return pre;
    }
};
