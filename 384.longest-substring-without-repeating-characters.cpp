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
 * S1: hashtable记录字符最后出现位置, 若右边界上入窗字符已出现在窗内(即上次出现位置>=左边界),
 *     推进左边界到该字符上次出现位置+1,使上次出现的该字符出窗,并更新该字符最后出现位置=右边界
 * T=O(n) S=O(1)
 */
class Solution {
public:
    /**
     * @param s: a string
     * @return: an integer
     */
    // Sliding window
    // T=O(n) S=O(n)
    int lengthOfLongestSubstring(string &s) {
        int res = 0, left = 0;
        unordered_map<char, int> m;                         // 记录字符最后一次出现的位置
        for (int right = 0; right < s.length(); ++right) {
            if (m.count(s[right]) && m[s[right]] >= left) { // 若右边界上入窗字符已出现在窗内(即上次出现位置>=左边界)
                left = m[s[right]] + 1;                     // 推进左边界到该字符上次出现位置+1使上次出现的该字符出窗
            }
            m[s[right]] = right;                            // 更新该字符的最后出现位置
            res = max(res, right - left + 1);               // 更新最大长度
        }
        return res;
    }
};
