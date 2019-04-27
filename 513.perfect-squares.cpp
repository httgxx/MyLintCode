/*
 * @lc app=lintcode id=513 lang=cpp
 *
 * [513] Perfect Squares
 *
 * https://www.lintcode.com/problem/perfect-squares/description
 *
 * lintcode
 * Medium (38.00%)
 * Total Accepted:    8921
 * Total Submissions: 23406
 * Testcase Example:  '12\n'
 *
 * Given a positive integer `n`, find the least number of perfect square
 * numbers (for example, `1, 4, 9, 16, ...`) which sum to n.
 * Example 1:
 *   Input: 12
 *   Output: 3
 *   Explanation: 4 + 4 + 4
 * Example 2:
 *   Input: 13
 *   Output: 2
 *   Explanation: 4 + 9
 * 
 * @Category DP(划分型)
 * @Ideas
 * DP T=O(n*sqrt(n)) S=O(n)
 * dp[i]表示i可以分成的完全平方数的最少个数
 * dp[i]=min{dp[i-j^2]+1}|1<=j^2<=i
 * 初始化 dp[0]=0  (所有数字>0,则和为0不可能)
 * 
 */
class Solution {
public:
    /**
     * @param n: a positive integer
     * @return: An integer
     */
    int numSquares1(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <=n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i - j * j] + 1, dp[i]);    
            }
        }
        return dp.back();  // dp[n]
    }

    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 1; i + j * j <= n; ++j) {
                dp[i + j * j] = min(dp[i + j * j], dp[i] + 1);
            }
        }
        return dp.back();
    }
};
