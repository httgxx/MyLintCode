/*
 * @lc app=leetcode id=456 lang=cpp
 *
 * [456] 132 Pattern
 *
 * https://leetcode.com/problems/132-pattern/description/
 *
 * algorithms
 * Medium (27.96%)
 * Total Accepted:    38.5K
 * Total Submissions: 137.5K
 * Testcase Example:  '[1,2,3,4]'
 *
 * 
 * Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a
 * subsequence ai, aj, ak such
 * that i < j < k and ai < ak < aj. Design an algorithm that takes a list of n
 * numbers as input and checks whether there is a 132 pattern in the list.
 * 
 * Note: n will be less than 15,000.
 * 
 * Example 1:
 * 
 * Input: [1, 2, 3, 4]
 * 
 * Output: False
 * 
 * Explanation: There is no 132 pattern in the sequence.
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: [3, 1, 4, 2]
 * 
 * Output: True
 * 
 * Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
 * 
 * 
 * 
 * Example 3:
 * 
 * Input: [-1, 3, 2, 0]
 * 
 * Output: True
 * 
 * Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1,
 * 3, 0] and [-1, 2, 0].
 * 
 * @Category 单调栈
 * @Idea 单调栈 T=O(n) S=O(n)
 */
class Solution {
public:
    // 单调栈
    // T=O(n) S=O(n)
    bool find132pattern(vector<int>& nums) {
        int third = INT_MIN;
        stack<int> st;
        for (int i = nums.size() - 1; i >= 0; --i) {    // 倒扫
            if (nums[i] < third) { return true; }       // 若新前数<3rd,已找到132模式,返回true
            while (!st.empty() && nums[i] > st.top()) { // 若新前数>单调栈顶
                third = st.top(); st.pop();             //   更新3rd=栈顶
            }
            st.push(nums[i]);                           // 所有>=third的数入栈
        }
        return false;                                   // 没找到132模式,返回false
    }
};
