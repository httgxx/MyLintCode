/*
 * @lc app=lintcode id=106 lang=cpp
 *
 * [106] Convert Sorted List to Binary Search Tree
 *
 * https://www.lintcode.com/problem/convert-sorted-list-to-binary-search-tree/description
 *
 * lintcode
 * Medium (32.00%)
 * Total Accepted:    15892
 * Total Submissions: 48800
 * Testcase Example:  'null'
 *
 * Given a singly linked list where elements are sorted in ascending order,
 * convert it to a height balanced BST.
 * 
 * Example 1:
 *	Input: array = 1->2->3
 *	Output:
 *		 2  
 *		/ \
 *	   1   3
 *		
 * Example 2:
 *	Input: 2->3->6->7
 *	Output:
 *		 3
 *		/ \
 *	   2   6
 *		    \
 *		     7
 *
 *	Explanation:
 *	There may be multi answers, and you could return any of them.
 */
/**
 * Definition of ListNode
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *         this->val = val;
 *         this->next = NULL;
 *     }
 * }
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
    /*
     * @param head: The first node of linked list.
     * @return: a tree node
     */
    // S1: 快慢指针找中点做根,分治递归 T=O(n) S=O(1)
    TreeNode* sortedListToBST1(ListNode* head) {
        if (!head) { return NULL; }
        return helper(head, NULL);
    }
    TreeNode* helper(ListNode* head, ListNode* tail) {
        if (head == tail) { return NULL; }
        ListNode *slow = head, *fast = head;
        while (fast != tail && fast->next != tail) {// 找中点做根
            slow = slow->next;
            fast = fast->next->next;
        }
        TreeNode *cur = new TreeNode(slow->val);
        cur->left = helper(head, slow);             // 分治递归建左子树
        cur->right = helper(slow->next, tail);      // 分治递归建右子树
        return cur;
    }

    // S1: 快慢指针找中点做根,分治递归 T=O(n) S=O(1)
    TreeNode *sortedListToBST(ListNode* head) {
        if (!head) { return NULL; }
        if (!head->next) { return new TreeNode(head->val); }
        ListNode *slow = head, *fast = head, *last = slow;
        while (fast->next && fast->next->next) {                // 找中点做根
            last = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        last->next = NULL;
        TreeNode *cur = new TreeNode(slow->val);
        if (head != slow) { cur->left = sortedListToBST(head); }// 坑:可能没左子树  
        cur->right = sortedListToBST(fast);
        return cur;
    }
};
