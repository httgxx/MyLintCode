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
 * @Category DP
 * @Ideas
 * dp[i]表示到[i][j]位置的最小路径和
 * 
 * 
 * 
 * 
 * 
        // if i==0(第一行) j>0(第一列以后) 上一步只能是左边一格, dp[0][j]=dp[0][j-1] + grid[0][j]
        // else if j==0(第一列) i>0(第一行以后) 上一步只能是上边一格, dp[i][0]=dp[i-1][0] + grid[i][0]
        // else if(i>0 && j>0) dp[i][[j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j]
        // => 通式 dp[i][j] = if(i==0 && j>1) dp[i][j-1] + grid[i][j]
        //                    else if(j==0 && i>1) dp[i-1][j] + grid[i][j]
        //                    else if(i>0 && j>0) min(dp[i][j-1],dp[i-1][j]) + grid[i][j]

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
