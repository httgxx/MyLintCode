/*
 * @lc app=lintcode id=1506 lang=cpp
 *
 * [1506] All Nodes Distance K in Binary Tree
 *
 * https://www.lintcode.com/problem/all-nodes-distance-k-in-binary-tree/description
 *
 * lintcode
 * Medium (61.00%)
 * Total Accepted:    158
 * Total Submissions: 252
 * Testcase Example:  '{3,5,1,6,2,0,8,#,#,7,4}\n5\n2'
 *
 * We are given a binary tree (with root node `root`), a `target` node, and an
 * integer value `K`.
 * 
 * Return a list of the values of all nodes that have a distance `K` from the
 * `target` node.  The answer can be returned in any order.
 * 
 * Example 1:
 * Input:{3,5,1,6,2,0,8,#,#,7,4} 5 2
 * Output: [7,4,1]
 * Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1
 *     3
 *    / \
 *   5   1
 *  /|   |\  
 * 6 2   0 8
 *   |\
 *   7 4
 * Example 2
 * Input: {1,2,3,4} 2 1
 * Output: [1,4]
 * Explanation: The binary tree is like this:
 *     1
 *    / \
 *   2   3
 *  /   
 * 4   
 * The node 1 and 4 is 1 away from 2.
 * 
 * @Category BT遍历
 * @Idea 找BT中和点t相距k的所有点
 * 难点:如何找和t相距k的t的祖先 => 建立子到父的反向连接
 * 
 * 
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
     * @param root: the root of the tree
     * @param target: the target
     * @param K: the given K
     * @return: All Nodes Distance K in Binary Tree
     */
    // Parent links + DFS 
    // T=O(n) S=O(n)
    vector<int> distanceK(TreeNode * root, TreeNode * target, int K) {
        if (!root) return {};                                               // 特例空树
        vector<int> res;
        unordered_map<TreeNode*, TreeNode*> parent;
        unordered_set<TreeNode*> visited;                                   // 记录访问过的结点, 防重剪枝
        findParent(root, parent);                                           // 遍历树建立每个结点的父链接
        helper(target, K, parent, visited, res);                            // 在子孙和祖先两个方向DFS找距离K的点
        return res;
    }
    void findParent(TreeNode* node, unordered_map<TreeNode*, TreeNode*>& parent) {
        if (!node) return;
        if (node->left) parent[node->left] = node;
        if (node->right) parent[node->right] = node;
        findParent(node->left, parent);                                     // 递归建立每个结点的父链接
        findParent(node->right, parent);
    }
    void helper(TreeNode* node, int K, unordered_map<TreeNode*, TreeNode*>& parent, 
                unordered_set<TreeNode*>& visited, vector<int>& res) {
        if (visited.count(node)) { return; }                                // 访问过则返回上层递归
        visited.insert(node);                                               // 没访问过则标记为访问过
        if (K == 0) {                                                       // 找到距离为K的点,加入结果集并返回
            res.push_back(node->val);
            return;
        }
        if (node->left) helper(node->left, K - 1, parent, visited, res);    // 左子树递归找距离K的点
        if (node->right) helper(node->right, K - 1, parent, visited, res);  // 右子树递归找距离K的点
        if (parent[node]) helper(parent[node], K - 1, parent, visited, res);// 父链接递归找距离K的点
    }
};
