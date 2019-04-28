/*
 * @lc app=lintcode id=110 lang=cpp
 *
 * [110] Minimum Path Sum
 *
 * https://www.lintcode.com/problem/minimum-path-sum/description
 *
 * lintcode
 * Easy (38.00%)
 * Total Accepted:    19668
 * Total Submissions: 51741
 * Testcase Example:  '[[1,3,1],[1,5,1],[4,2,1]]'
 *
 * Given a m x n grid filled with non-negative numbers, find a path from top
 * left to bottom right which minimizes the sum of all numbers along its path.
 * 
 * @Category DP(按情况叠加比较型)
 * @Ideas
 * DP T=O(mn) S=O(mn)
 * dp[i][j]表示(0,0)到(i,j)位置的最小路径和
 * = grid[i][j] +
 * 第一列//j==0 && i>1: 左格值 dp[i-1][0]
 * 第一行//i==0 && j>1: 上格值 dp[0][j-1]
 * 中间行和中间列//rest: 左格和上格的较小值 min(dp[i-1][j],dp[i][j-1])
 */
class Solution {
public:
    /**
     * @param grid: a list of lists of integers
     * @return: An integer, minimizes the sum of all numbers along its path
     */
    int minPathSum(const vector<vector<int>> &grid) {
        int m = grid.size();
        if (m == 0) { return 0; }
        int n = grid[0].size();
        if (n == 0) { return 0; }

        vector<vector<int> > dp = grid;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
               if (i == 0 && j > 0) {
                   dp[i][j] += dp[i][j - 1];
               } else if (j == 0 && i > 0) {
                   dp[i][j] += dp[i - 1][j];
               } else if (i > 0 && j > 0) {  // 坑: 须i>0 &&j>0
                   dp[i][j] += min(dp[i - 1][j], dp[i][j - 1]);
               }
            }
        }
        return dp[m - 1][n - 1];
    }
};
