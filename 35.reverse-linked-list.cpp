/*
 * @lc app=lintcode id=35 lang=cpp
 *
 * [35] Reverse Linked List
 *
 * https://www.lintcode.com/problem/reverse-linked-list/description
 *
 * lintcode
 * Easy (43.00%)
 * Total Accepted:    41795
 * Total Submissions: 95694
 * Testcase Example:  '0->1->2->3->null'
 *
 * Reverse a linked list.
 * 
 * Example 1:
 * Input: 1->2->3->null
 * Output: 3->2->1->null
 * 
 * Example 2:
 * Input: 1->2->3->4->null
 * Output: 4->3->2->1->null
 * 
 * Challenge: Reverse it in-place and in one-pass
 * 
 * @Category linkedlist
 * pre=null
 * while(cur)
 *   next = cur->next  // 标记未来(好之后回来继续)
 *   cur->next = pre   // 调转朝向未来的船头,指向过去
 *   pre = cur         // 从过去进入现在
 *   cur = next        // 从现在进入未来
 * return pre          // 最后现在消失时,过去成了新的起点
 */
/**
 * Definition of singly-linked-list:
 *
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *        this->val = val;
 *        this->next = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param head: n
     * @return: The new head of reversed linked list.
     */
    // Iterative T=O(n) S=(1)
    ListNode * reverse(ListNode * head) {
        ListNode *pre = NULL, *cur = head, *next = NULL;
        while (cur) {
            next = cur->next;   // 标记未来(好之后回来继续)
            cur->next = pre;    // 调转朝向未来的船头,指向过去
            pre = cur;          // 从过去进入现在
            cur = next;         // 从现在进入未来
        }
        return pre;             // 最后现在消失时,过去成了新的起点
    }
};
