/*
 * @lc app=lintcode id=386 lang=cpp
 *
 * [386] Longest Substring with At Most K Distinct Characters
 *
 * https://www.lintcode.com/problem/longest-substring-with-at-most-k-distinct-characters/description
 *
 * lintcode
 * Medium (28.00%)
 * Total Accepted:    14619
 * Total Submissions: 52156
 * Testcase Example:  '"eceba"\n3'
 *
 * Given a string *S*, find the length of the longest substring *T* that
 * contains at most k distinct characters.
 * 
 * Example 1:
 * Input: S = "eceba" and k = 3
 * Output: 4
 * Explanation: T = "eceb"
 * 
 * Example 2:
 * Input: S = "WORLD" and k = 4
 * Output: 4
 * Explanation: T = "WORL" or "ORLD"
 * Challenge: O(n) time
 * 
 * @Category HashTable + Sliding Window / two pointers
 * @Idea
 * S1: hashtable记字母频率 + 滑动窗口保证最多K个不同字符
 * 
 * 
 */
class Solution {
public:
    /**
     * @param s: A string
     * @param k: An integer
     * @return: An integer
     */
    // S1: hashtable记字母频率 + 滑动窗口保证最多K个不同字符
    // 窗口内满足条件hashtable.size()<=2, 先右边界+1再左边界
    // T= O(n) S=O(1)
    int lengthOfLongestSubstringKDistinct(string &s, int k) {
        int res = 0, left = 0;                                  // 坑: ,而不是;
        unordered_map<char, int> m;
        for (int right = 0; right < s.size(); ++right) {        // 右边界+1扩大窗口
            ++m[s[right]];                                      // 频率+1, 若m不含则新建s[i]
            while (m.size() > k) {                              // 左边界不断+1缩小窗口直到满足条件
                if (--m[s[left]] == 0) { m.erase(s[left]); }    // 频率-1, 若频率0则删除s[i]
                ++left;
            }
            res = max(res, right - left + 1);                   // 更新最大窗口大小 // 坑:勿忘+1!!!
        }
        return res;
    }

    // S2: hashtable记字母最后出现位置 + 滑动窗口保证最多K个不同字符
    // T= O(n) S=O(1)
    //int lengthOfLongestSubstringKDistinct(string &s, int k) {
    
    //}
};
