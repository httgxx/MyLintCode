/*
 * @lc app=lintcode id=384 lang=cpp
 *
 * [384] Longest Substring Without Repeating Characters
 *
 * https://www.lintcode.com/problem/longest-substring-without-repeating-characters/description
 *
 * lintcode
 * Medium (32.00%)
 * Total Accepted:    21067
 * Total Submissions: 64171
 * Testcase Example:  '"abcabcbb"'
 *
 * Given a string, find the length of the longest substring without repeating
 * characters.
 * 
 * Example 1:
 * Input: "abcabcbb"
 * Output: 3
 * Explanation: The longest substring is "abc".
 * 
 * Example 2:
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The longest substring is "b".
 * 
 * Challenge:
 * time complexity O(n)
 * 
 * @Category Sliding Window
 * @Idea hashtable + sliding window
 * S1: hashtable记录字符最后出现位置, 若右边界上字符已经在窗口内出现过(即该字符前一次出现的位置>左边界),推进左边界到右边界
 * T=O(n) S=O(1)
 */
class Solution {
public:
    /**
     * @param s: a string
     * @return: an integer
     */
    int lengthOfLongestSubstring(string &s) {
        int res = 0, left = 0;
        unordered_map<char, int> m;
        for (int right = 0; right < s.length(); ++right) {
            if (m.count(s[right]) && m[s[right]] >= left) { 
                left = m[s[right]] + 1;
            }
            m[s[right]] = right;
            res = max(res, right - left + 1);
        }
        return res;
    }
};
