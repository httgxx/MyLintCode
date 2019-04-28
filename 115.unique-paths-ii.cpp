/*
 * @lc app=lintcode id=115 lang=cpp
 *
 * [115] Unique Paths II
 *
 * https://www.lintcode.com/problem/unique-paths-ii/description
 *
 * lintcode
 * Easy (31.00%)
 * Total Accepted:    19352
 * Total Submissions: 62403
 * Testcase Example:  '[[0]]'
 *
 * Follow up for "Unique Paths":
 * Now consider if some obstacles are added to the grids. How many unique paths
 * would there be?
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 * 
 * @Category DP(按情况叠加型)
 * @Ideas
 * DP T=O(mn) S=O(mn)
 * dp[j]=从左上角到当前行的第j列有多少种走法
 * dp[j]+=dp[j-1]|当前行[j]!=1 //+=而不是=
 * 初始 dp[0]=0
 * 顺序 上到下i=0->m-1,左到右j=0->n-1 
 * 返回 dp[n-1]
 * 坑: 特例a[0][0]==1则直接返回0
 * 坑: dp[j] += dp[j-1] +=而不是=
 * 坑: 只初始化dp[0]=0而不是1,且之后i和j从0而不是1开始循环
 * 坑: [i][j]!=1时须j>0时才dp[j]+=dp[j-1]即只从第二列才开始累加
 */
class Solution {
public:
    /**
     * @param obstacleGrid: A list of lists of integers
     * @return: An integer
     */
    int uniquePathsWithObstacles(const vector<vector<int>> &obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0].empty() ||
            obstacleGrid[0][0] == 1) return 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<long> dp(n, 0);
        dp[0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) dp[j] = 0;
                else if (j > 0) {
                    dp[j] += dp[j - 1];
                }
            }
        }   
        return dp[n - 1];
    }
};
