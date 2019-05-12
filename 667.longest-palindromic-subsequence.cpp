/*
 * @lc app=lintcode id=667 lang=cpp
 *
 * [667] Longest Palindromic Subsequence
 *
 * https://www.lintcode.com/problem/longest-palindromic-subsequence/description
 *
 * lintcode
 * Medium (46.00%)
 * Total Accepted:    3900
 * Total Submissions: 8334
 * Testcase Example:  '"bbbab"\n'
 *
 * Given a string s, find the longest palindromic subsequence's length in s.
 * You may assume that the maximum length of s is `1000`.
 */
class Solution {
public:
    /**
     * @param s: the maximum length of s is 1000
     * @return: the longest palindromic subsequence's length
     */
    int longestPalindromeSubseq(string &s) {
        int n = s.length();
        if (n == 0) return 0;

        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = n - 1; i >= 0; i--) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;  // 头尾同则头尾同时处理,且回文长度增2字符
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]); // 头尾异则头尾分别处理求最大,且会问长度不变
                }
            }
        }
        return dp[0][n - 1];
    }
};
