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
 * @Category DP LongestCommonSubsequence DFS+记忆搜索
 * @Idea DP T=O(mn) S=O(mn)
 * S1: dp[i][j]表示使word1前i个字符和word2前j个字符相等的最少删除操作数
 * = 若最后一个字符同(w1[i]==w2[j]) w1[i-1]!=w2[j-1]: min(dp[i-1][j], min(dp[i-1][j-1], dp[i][j-1])) + 1
 * 坑: 当前最后字符不同,删哪个的都行,须求min // 坑:+1!!!
 * 
 * S2: DFS+记忆搜索 T=O(mn) S=O(mn)
 * lintcode运行时更快.why?
 */
class Solution {
public:
    /**
     * @param word1: a string
     * @param word2: a string
     * @return: return a integer
     */
    // S3: DFS+记忆搜索 T=O(n1*n2) S=O(n1*n2) //
    int minDistance(string &w1, string &w2) {
        int n1 = w1.length(), n2 = w2.length();
        vector<vector<int>> memo(n1 + 1, vector<int>(n2 + 1, 0));   // m[p1][p2]=(w1以[p1]开头的后缀)变为(w2以[p2]开头的后缀)所需最小删除次数
        return dfsMemo(w1, w2, 0, 0, memo);                         // p1, p2分别表示w1,w2后缀的起始点
    }
    int dfsMemo(string &w1, string &w2, int p1, int p2, vector<vector<int>> &memo) { // p1=w1后缀起始位,p2=w2后缀起始位
        if (memo[p1][p2] != 0) { return memo[p1][p2]; }             // 记忆已有,直接返回
        if (p1 == w1.length()) { return w2.length() - p2; }         // w1后缀空,w2后缀长度n2-p2 // 坑:返n2-p2不是p2
        if (p2 == w2.length()) { return w1.length() - p1; }         // w2后缀空,w1后缀长度n1-p1 // 坑:返n1-p1不是p1
        if (w1[p1] == w2[p2])  {
            memo[p1][p2] = dfsMemo(w1, w2, p1 + 1, p2 + 1, memo);   // p1开头的后缀比(p1+1)开头的后缀长1,p2开头的后缀比(p2+1)开头的后缀长1
                                                                    // 若长的1位相同,转换p1开头的后缀到p2开头的后缀所需删除次数相同
        }
        else {
            memo[p1][p2] = 1+ min(dfsMemo(w1, w2, p1 + 1, p2, memo),// 若长的1位不同,+1多删除1次,可以删w1[p2+1],也可以删w2[p2+1],取min 
                                  dfsMemo(w1, w2, p1, p2 + 1, memo));
        }
        return memo[p1][p2];                                        // m[p1][p2]=(w1以[p1]开头的后缀)变为(w2以[p2]开头的后缀)所需最小删除次数
    }

    // S1: DP T=O(n1*n2) S=O(n1*n2)
    // dp[i][j]表示w1前i变w2前j最少删除次数
    int minDistance1(string &w1, string &w2) {
        int n1 = w1.length(), n2 = w2.length();
        if (n1 < n2) { return minDistance(w2, w1); }                // 短w放内循环,长w放外循环
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));     // dp[i][j]表示w1前i变w2前j最少删除次数
        for (int i = 0; i <= n1; ++i) { dp[i][0] = i; }
        for (int j = 0; j <= n2; ++j) { dp[0][j] = j; }
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (w1[i - 1] == w2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];                    // 不+1因为不需要删除操作                   
                }
                else {
                    dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]); // +1因为需要1次删除操作
                }
            }
        }
        return dp[n1][n2];
    }
    
    // S2: DP LCS T=O(n1*n2) S=O(n1*n2)
    // dp[i][j]表示w1前i和w2前j最长公共子序列(LCS)
    int minDistance2(string &w1, string &w2) {
        int n1 = w1.length(), n2 = w2.length();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0)); // dp[i][j]表示w1前i和w2前j的LCS
        //dp[i][0]=dp[0][j]=0 
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (w1[i - 1] == w2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];            // +1因为最长公共子序列多了1字符
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // 不+1因为字符不相同 
                }
            }
        }
        return n1 + n2 - 2 * dp[n1][n2];
    }
};
