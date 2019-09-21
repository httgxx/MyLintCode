/*
 * @lc app=lintcode id=1156 lang=cpp
 *
 * [1156] Delete Operation for Two Strings
 *
 * https://www.lintcode.com/problem/delete-operation-for-two-strings/description
 *
 * lintcode
 * Medium (64.00%)
 * Total Accepted:    491
 * Total Submissions: 752
 * Testcase Example:  '"sea"\n"eat"'
 *
 * Given two words word1 and word2, find the minimum number of steps required
 * to make word1 and word2 the same, where in each step you can delete one
 * character in either string.
 * 
 * Example 1:
 * Input: "sea", "eat"
 * Output: 2
 * Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
 * 
 * Example 2:
 * Input: "horse", "ros"
 * Output: 4
 * Explanation: You need three steps to make "horse" to "os" and another step to make "ros" to "os".
 * 
 * @Category DP LongestCommonSubsequence
 * @Idea DP T=O(mn) S=O(mn)
 * dp[i][j]表示使word1前i个字符和word2前j个字符相等的最少删除操作数
 * = 若最后一个字符同(w1[i]==w2[j]) w1[i-1]!=w2[j-1]: min(dp[i-1][j], min(dp[i-1][j-1], dp[i][j-1])) + 1
 * 坑: 当前最后字符不同,删哪个的都行,须求min // 坑:+1!!!
 */
class Solution {
public:
    /**
     * @param word1: a string
     * @param word2: a string
     * @return: return a integer
     */
    // DP T=O(n1*n2) S=O(n1*n2)
    int minDistance(string &w1, string &w2) {
        int n1 = w1.length(), n2 = w2.length();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0)); // 须初始化
        for (int i = 0; i <= n1; ++i) dp[i][0] = i;             // 非空word变空需要len(word)次删除操作
        for (int j = 0; j <= n2; ++j) dp[0][j] = j;             // 非空word变空需要len(word)次删除操作
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (w1[i - 1] == w2[j - 1]) {                   // 坑:不是dp[i-1]而是w1[i-1]
                    dp[i][j] = dp[i - 1][j - 1];                // 当前最后字符相同,不用删除,故最少删除操作数不变
                }                
                else {
                    dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j]); // 当前最后字符不同,删哪个的都行,须求min // 坑:+1!!!
                }
            }
        }
        return dp[n1][n2];                                      // w1[1~n1]变成w2[1~n2]的最小删除操作总数
    }
};
