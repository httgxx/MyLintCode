/*
 * @lc app=lintcode id=107 lang=cpp
 *
 * [107] Word Break
 *
 * https://www.lintcode.com/problem/word-break/description
 *
 * lintcode
 * Medium (16.00%)
 * Total Accepted:    22003
 * Total Submissions: 136766
 * Testcase Example:  '"a"\n["a"]\n'
 *
 * Given a string s and a dictionary of words dict, determine if s can be break
 * into a space-separated sequence of one or more dictionary words.
 * 
 * Example 1:
 * Input:  "lintcode", ["lint", "code"]
 * Output:  true
 * 
 * Example 2:
 * Input: "a", ["a"]
 * Output:  true
 * 
 * Example 3:
 * Input: "applepenapple", wordDict = ["apple", "pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
 * Note that you are allowed to reuse a dictionary word.
 * 
 * Example 4:
 * Input: "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 * Output: false
 * 
 * @Category DP or DFS+记忆搜索
 * @Idea
 * S1: DP
 * dp[n+1], dp[i]表示s[0,i)是否可以被拆分,dp[0]=true表示空串可以被拆分
 * 
 */
class Solution {
public:
    /*
     * @param s: A string
     * @param dict: A dictionary of words dict
     * @return: A boolean
     */
    // DP T=O(n^2) S=O(n])
    // 坑: 必须用字典中最长单词长度剪枝,否则TLE!!!
    bool wordBreak(string &s, unordered_set<string> &dict) {
        if (s.empty()) { return true; }                             // 特例:空串
        int maxLen = INT_MIN;                                       // 找到字典中最长单词长度
        unordered_set<string>::iterator it;
        for (it = dict.begin(); it != dict.end(); ++it) {
            maxLen = max(maxLen, (int)(*it).size());                // 坑: 必须加(int)
        }
        int n = s.length();
        bool canSegments[n];
        for (int i = 0; i < n; ++i) {                               // 顺着枚举开头字符
            canSegments[i] = false;                                 // 初始=不能拆分
            for (int j = i; j >= 0 && i - j + 1 <= maxLen; --j) {   // 倒着枚举结尾字符,且[j,i]长度没超过字典中最长单词长度(否则TLE)
                if (j > 0 && canSegments[j - 1] == false) {         // 坑:必须加j>0,且dp[j-1]==true即[0,j-1]可拆分
                    continue;
                }
                if (dict.count(s.substr(j, i - j + 1))) {           // 找到j使[0,j-1]可拆分且[j,i]在字典里则[0,j]可拆分
                    canSegments[i] = true;
                    break;
                }
            }
        }
        return canSegments[n - 1];
    }
};
