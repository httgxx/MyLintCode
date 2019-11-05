/*
 * @lc app=lintcode id=105 lang=cpp
 *
 * [105] Copy List with Random Pointer
 *
 * https://www.lintcode.com/problem/copy-list-with-random-pointer/description
 *
 * lintcode
 * Medium (38.00%)
 * Total Accepted:    29281
 * Total Submissions: 76352
 * Testcase Example:  '-1->null, [null]\n'
 *
 * A linked list is given such that each node contains an additional random
 * pointer which could point to any node in the list or null.Return a deep copy
 * of the list.
 * 
 * @Category LinkedList
 * @Idea 链表
 * S1: 递归 + map[node]=copy_node
 * 建表保存每个node都 map[node]=copy, node->random => map[node->random]‘
 * T=O(n) S=O(n)
 * 
 * S2: 
 */
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    /**
     * @param head: The head of linked list with a random pointer.
     * @return: A new head of a deep copy of the list.
     */
    // S1: 递归+map[node]=copy_node
    // 建表保存每个node都 map[node]=copy, node->random => map[node->random]
    // T=O(n) S=O(n)
    RandomListNode* copyRandomList(RandomListNode* head) {
        unordered_map<RandomListNode*, RandomListNode*> m;
        return helper(head, m);
    }
    RandomListNode* helper(
        RandomListNode* node,
        unordered_map<RandomListNode*, RandomListNode*>& m) {       // 在map中找原node对应的copy_node
            if (!node) { return nullptr; }                          // 递归返回
            if (m.count(node)) { return m[node]; }                 // 找到copy则返回
            RandomListNode *res = new RandomListNode(node->label); // 没找copy则新建加入
            m[node] = res;
            res->next = helper(node->next, m);                     // 新建copy node时random和next都可以递归
            res->random = helper(node->random, m);
            return res;
    }
};
