/*
 * @lc app=leetcode id=979 lang=cpp
 *
 * [979] Distribute Coins in Binary Tree
 *
 * https://leetcode.com/problems/distribute-coins-in-binary-tree/description/
 *
 * algorithms
 * Medium (67.86%)
 * Total Accepted:    23.3K
 * Total Submissions: 34.4K
 * Testcase Example:  '[3,0,0]'
 *
 * Given the root of a binary tree with N nodes, each node in the tree has node.val coins, and there are N coins total.
 * In one move, we may choose two adjacent nodes and move one coin from one node to another.  
 * (The move may be from parent to child, or from child to parent.)
 * Return the number of moves required to make every node have exactly one coin.
 * 
 * Example 1:
 * Input: [3,0,0]
 * Output: 2
 * Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.
 * 
 * Example 2:
 * Input: [0,3,0]
 * Output: 3
 * Explanation: From the left child of the root, we move two coins to the root [taking two moves].
 * Then, we move one coin from the root of the tree to the right child.
 * 
 * Example 3:
 * Input: [1,0,2]
 * Output: 2
 * 
 * Example 4:
 * Input: [1,0,0,null,3]
 * Output: 4
 * 
 * Note:
 * 1<= N <= 100
 * 0 <= node.val <= N
 * 
 * @Category BT  Divide & Conquer
 * @Idea 二叉树 分治递归
 * 递归分支计算根所在子树的
 *   金币balance=左子树金币balance+右子树金币balance+根value-1 //根需留一个金币
 *   使金币balance=0的最小moves=使左子树金币balance=0的最少moves+使右子树金币balance=0的最少moves
 *                            =|左子树金币balance|+|右子树金币balance|
 * 如此递归到叶节点:叶节点的金币balance=结点value-1(总共1个结点只须1个金币,其他都是多余)
 * 再bottom-up返回到root层递归,得到累加的所有moves
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
   /* 递归分支计算根所在子树的
    *   金币balance=左子树金币balance+右子树金币balance+根value-1 //根需留一个金币
    *   使金币balance=0的最小moves=使左子树金币balance=0的最少moves+使右子树金币balance=0的最少moves
    *                          =|左子树金币balance|+|右子树金币balance|
    * 如此递归到叶节点:叶节点的金币balance=结点value-1(总共1个结点只须1个金币,其他都是多余)
    * 再bottom-up返回到root层递归,得到累加的所有moves
    */
    int distributeCoins(TreeNode* root) {
        int moves = 0;
        balance(root, moves);                               // 递归
        return moves;
    }
    int balance(TreeNode *root, int & moves) {              // 分治递归
        if (root == NULL) { return 0; }                     // 递归到叶节点的左右null子树
        int leftBalance = balance(root->left, moves);       // 计算左子树金币balance,累加左子树达到金币balance=0所需最少moves
        int rightBalance = balance(root->right, moves);     // 计算右子树金币balance,累加右子树达到金币balance=0所需最少moves
        moves += abs(leftBalance) + abs(rightBalance);      // 累加根所在子树达到金币balance=0所需最少moves
        return leftBalance + rightBalance + root->val - 1;  // 返回根所在子树的金币balance=左子数balance+右子树balance+root值-1
                                                            // 根为叶子时金币balance=0+0+叶值-1(总共1个结点只须1个金币,其他都是多余)
    }
};
