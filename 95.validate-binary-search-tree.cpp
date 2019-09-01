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
 * 大坑:!!!
 * 不能只比较left/right和root,而必须保证left/right subtree整个都在(min,root)/(root,max)的范围内
 * 反例: left child 5 < root 10,但是left subtree 含有子孙100>root所以不是valid BST
 *     10
 *     /
 *    5
 *   / \
 *  1  100
 * [错误!!!]
 * bool isValidBST(TreeNode * root) {
 *     if (!root) return true;
 *     if (root->left)
 *          if (root->left->val >= root->val || !isValidBST(root->left)) return false;
 *     if (root->right) {
 *          if (root->right->val <= root->val || !isValidBST(root->right)) return false;
 *     return true;
 * }
 * [纠错] 必须传递[mn, mx]
 * bool isValidBST(TreeNode * root) {
 *     return helper(root, LONG_MIN, LONG_MAX);
 * }
 * bool helper(TreeNode * root, long mn, long mx) { 
 *     if (!root) return true;
 *     if (root->left)
 *          if (root->left->val >= root->val || root->left->val <= mn) ||
 *              !helper(root->left, mn, root->val)) return false;
 *     if (root->right) {
 *          if (root->right->val <= root->val || root->right->val <= mn) ||
 *              !helper(root->right, root->val, mx)) return false;
 *     return true;
 * }
 * [优化1] 把[mn, mx]的validation放入下一层call来做
 * bool helper(TreeNode * root, long mn, long mx) { 
 *     if (!root) return true;
 *     if (root->val <= mn || root->val >= mx) return false; //被提炼出来
 *     if (root->left)
 *          if (!helper(root->left, mn, root->val)) return false;
 *     if (root->right) {
 *          if (!helper(root->right, root->val, mx)) return false;
 *     return true;
 * }
 * [优化2] 因为if(!root)return true,所以不用再判断if(root->left)和if(root->right) 
 * bool helper(TreeNode * root, long mn, long mx) { 
 *     if (!root) return true;
 *     if (root->val <= mn || root->val >= mx) return false;
 *     if (!helper(root->left, mn, root->val)) return false;
 *     if (!helper(root->right, root->val, mx)) return false;
 *     return true;
 * }
 * [优化3] 精简代码
 * bool helper(TreeNode * root, long mn, long mx) { 
 *     if (!root) return true;
 *     return root->val > mn && root->val < mx &&
 *            helper(root->left, mn, root->val)) && helper(root->right, root->val, mx);
 * }
 * 
 * 坑: if (root->val <= mn || root->val >= mx) return false; // 不是&&而是||,不是<,>而是<=,>=
 * 
 * S2: 中序遍历过程中必须一直保持升序 T=O(n) 若过程中检查升序则S=O(1), 若结束后保存结果检查升序则S=O(n)
 * 递归/非递归中序遍历,过程中或最后结果是升序
 * 用pre指针保存前一个结点的值,应该总是<当前访问结点的值
 * 
 * 坑: 千万别忘初始化pre为NULL
 * 坑: 非递归中序遍历 最后千万别忘返回true
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
    // S1: 分治 DFS T=O(n) S=O(n)堆栈空间消耗
    bool isValidBST(TreeNode * root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
    bool helper(TreeNode * root, long mn, long mx) {
        if (!root) return true;
        if (root->val <= mn || root->val >= mx) return false;
        return helper(root->left, mn, root->val) && helper(root->right, root->val, mx);
    }

    // S2: 分治 BFS T=O(n) S=O(n) 若invalid可比DFS更快fail
    bool isValidBST2(TreeNode * root) {
        if (!root) return true;
        long mn = LONG_MIN, mx = LONG_MAX;
        queue<tuple<TreeNode *, long, long>> q{{make_tuple(root, mn, mx)}};
        while (!q.empty()) {
            tie(root, mn, mx) = q.front(); q.pop();
            if (root->val <= mn || root-> val >= mx) return false;
            if (root->left) {
                q.push(make_tuple(root->left, mn, root->val));
            }
            if (root->right) {
                q.push(make_tuple(root->right, root->val, mx));
            }
        }
        return true;  //勿忘!! 
    }

    // S3: 非递归中序遍历 遍历过程中应该保持升序(用pre保存前一个结点来和当前结点比大小)
    // T=O(n) S=O(1)
    bool isValidBST3(TreeNode * root) {
        if (!root) return true;
        stack<TreeNode *> s;
        TreeNode *p = root, *pre = NULL;  // 千万别忘初始化pre为NULL
        while (p || !s.empty()) {
            while (p) {
                s.push(p);
                p = p->left;
            }
            p = s.top(); s.pop();  // top才是当前访问的结点,top与pre比较
            // validate
            if (pre && pre->val >= p->val) return false;
            pre = p;
            p = p->right;
        }
        return true;  // 千万别忘最后返回true!!!
    }

    // S4: 递归中序遍历 遍历结束后对保持的结果检查升序
    bool isValidBST4(TreeNode * root) {
        if (!root) return true;
        vector<int> vals;
        inorder(root, vals);
        for (int i = 0; i < vals.size() - 1; ++i) {
            if (vals[i] >= vals[i + 1]) return false;
        }
        return true;
    }
    void inorder(TreeNode* root, vector<int>& vals) {
        if (!root) return;
        inorder(root->left, vals);
        vals.push_back(root->val);  // 中序遍历
        inorder(root->right, vals);
    }

    // S5: 递归中序遍历 遍历过程中应该保持升序(用pre保存前一个结点来和当前结点比大小)
    bool isValidBST5(TreeNode * root) {
        TreeNode * pre = NULL;  // 别忘=NULL!!! 否则random pointer will cause segment false
        return inorder(root, pre);
    }
    bool inorder(TreeNode * node, TreeNode *& pre) {  // 别忘加& 修改指针的值/所指地址
        if (!node) return true;
        bool res = inorder(node->left, pre);
        if (!res) return false;
        if (pre) {  // 别忘pre可能为空, 如访问root时
            if (node->val <= pre->val) return false;
        }
        pre = node;  // 拷贝指针值/所指地址, 不能直接传node否者原node被改
        return inorder(node->right, pre);
    }
};
