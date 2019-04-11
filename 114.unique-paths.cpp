/*
 * @lc app=lintcode id=114 lang=cpp
 *
 * [114] Unique Paths
 *
 * https://www.lintcode.com/problem/unique-paths/description
 *
 * lintcode
 * Easy (43.00%)
 * Total Accepted:    23429
 * Total Submissions: 53644
 * Testcase Example:  '1\n3'
 *
 * A robot is located at the top-left corner of a *m* x *n* grid.
 * The robot can only move either down or right at any point in time. The robot
 * is trying to reach the bottom-right corner of the grid.
 * 
 * How many possible unique paths are there?
 *
 * @Category DP
 * @Ideas
 * 2维 dp[i][j]=dp[i-1][j]+dp[i][j-1]
 * init dp[i][j]=1
 * return dp[m-1][n-1]
 * 降成1维 一层一层更新 每层从左到右列更新
 * for i=1~m-1
 *    for j=1 j: dp[j]+=dp[j-1]
 * return dp[n-1]
 */
class Solution {
public:
    /**
     * @param m: positive integer (1 <= m <= 100)
     * @param n: positive integer (1 <= n <= 100)
     * @return: An integer
     */
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1); //init all cells in row 0
        for (int i = 1; i < m; ++i) { //start with 1
            for (int j = 1; j < n; ++j) { //start with 1
                dp[j] += dp[j - 1];
            }
        }
		return dp[n-1];
    }
};
