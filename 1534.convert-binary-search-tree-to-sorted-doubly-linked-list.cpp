/*
 * @lc app=lintcode id=1534 lang=cpp
 *
 * [1534] Convert Binary Search Tree to Sorted Doubly Linked List
 *
 * https://www.lintcode.com/problem/convert-binary-search-tree-to-sorted-doubly-linked-list/description
 *
 * lintcode
 * Medium (64.00%)
 * Total Accepted:    703
 * Total Submissions: 1082
 * Testcase Example:  '{4,2,5,1,3}'
 *
 * Convert a BST to a sorted circular doubly-linked list in-place. Think of the
 * left and right pointers as synonymous to the previous and next pointers in a
 * doubly-linked list.
 * 
 * Let's take the following BST as an example, it may help you understand the
 * problem better:
 * 
 * ![bstdlloriginalbst]()
 * 
 * We want to transform this BST into a circular doubly linked list. Each node
 * in a doubly linked list has a predecessor and successor. For a circular
 * doubly linked list, the predecessor of the first element is the last
 * element, and the successor of the last element is the first element.
 * 
 * The figure below shows the circular doubly linked list for the BST above.
 * The "head" symbol means the node it points to is the smallest element of the
 * linked list.
 * 
 * ![bstdllreturndll]()
 * 
 * Specifically, we want to do the transformation in place. After the
 * transformation, the left pointer of the tree node should point to its
 * predecessor, and the right pointer should point to its successor. We should
 * return the pointer to the first element of the linked list.
 * 
 * The figure below shows the transformed BST. The solid line indicates the
 * successor relationship, while the dashed line means the predecessor
 * relationship.
 * 
 * Example 1:
 * Input: {4,2,5,1,3}
 *      4
 *     /  \
 *    3   5
 *   / \
 *  1   3
 * Output: "left:1->5->4->3->2  right:1->2->3->4->5"
 * Explanation:
 * Left: reverse output
 * Right: positive sequence output
 * 
 * Example 2:
 * Input: {2,1,3}
 *      2
 *     /  \
 *    1   3
 * Output: "left:1->3->2  right:1->2->3"
 * 
 * @Category BFS In-order
 * @Idea BFS 中序遍历
 * DFS in-order
 * 循环双向链表(head=原先的二叉搜索树中的最左结点即最小值结点,tail=最右结点,head和tail互连
 * pre = head = NULL
 * 递归inorder(cur, pre, head)
 *     if(!cur) return
 *     inorder(cur->left, pre, head)
 *     处理cur: if(!head) head=cur
 *     inorder(cur->left, pre, head)
 * 连首尾 pre->right = head; head->left = pre; 
 * 返回首
 * T=O(n) S=O(1)//extra space
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
     * @param root: root of a tree
     * @return: head node of a doubly linked list
     */
    // DFS in-order
    // T=O(n) S=O(1)//extra space
    TreeNode * treeToDoublyList(TreeNode * root) {
        if (!root) { return NULL; }         // 特例:空串
        TreeNode *pre = NULL, *head = NULL;
        inorder(root, pre, head);           // 递归
        pre->right = head;                  // 尾->首
        head->left = pre;                   // 尾<-首
        return head;
    }
    void inorder(TreeNode* cur, TreeNode*& pre, TreeNode*& head) {
        if (!cur) { return; }               // 递归结束
        inorder(cur->left, pre, head);      // 递归左子树
        if (!head) {                        // 若首node: head==null => pre=head=cur
            pre = cur;
            head = cur;
        }
        else {                              // 若非首node: head!=null
            pre->right = cur;               //   pre->cur
            cur->left = pre;                //   pre<-cur
        }
        pre = cur;                          // 坑: pre前移
        inorder(cur->right, pre, head);     // 递归右子树
    }
};
