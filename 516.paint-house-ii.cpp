/*
 * @lc app=lintcode id=516 lang=cpp
 *
 * [516] Paint House II
 *
 * https://www.lintcode.com/problem/paint-house-ii/description
 *
 * lintcode
 * Hard (31.00%)
 * Total Accepted:    5268
 * Total Submissions: 16722
 * Testcase Example:  '[[14,2,11],[11,14,5],[14,3,10]]\n'
 *
 * There are a row of `n` houses, each house can be painted with one of the `k`
 * colors. The cost of painting each house with a certain color is different.
 * You have to paint all the houses such that no two adjacent houses have the
 * same color.
 * 
 * The cost of painting each house with a certain color is represented by a `n`
 * x `k` cost matrix. For example, `costs[0][0]` is the cost of painting house
 * `0` with color `0`; `costs[1][2]` is the cost of painting house `1` with
 * color `2`, and so on... Find the minimum cost to paint all houses.
 *
 * @Category DP
 * @Idea
 * S1: DP T=O(n) S=O(n)
 * 用min1和min2记录刷到前房子的花费最小和次小时前房子刷的颜色
 * 当前房子颜色=min1则用min2算刷到当前房子的最小花费,反之用min1算
 * 每次用当前行min1,min2新上一行的min1,min2
 * 坑:
 * 
 * S0: DP T=O(nK^2) S=O(nK)
 * dp[i][j]表示刷房子([0]~[i])且房子[i]刷成颜色j的最小花费
 * dp[i][j] = min{dp[i-1][k]}|k!=j + costs[i][j]即把房子[i]刷成颜色j的花费；
 */
class Solution {
public:
    /**
     * @param costs: n x k cost matrix
     * @return: an integer, the minimum cost to paint all houses
     */
    int minCostII(const vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;  // 特例
        int m = costs.size(), n = costs[0].size();
        int min1 = 0, min2 = 0, lastCol = -1;  // 当前总共花费的最小和次小值
        for (int i = 0; i < m; ++i) {  // 刷到房子[i]
            // 看房子[i]刷哪种颜色能使总花费最小,记录最小和次小总花费
            // 没刷一个新房子就单独算最小,所以起始总是INT_MAX
            int mn1 = INT_MAX, mn2 = INT_MAX, mn1Col = -1;
            for (int j = 0; j < n; ++j) {  // 房子[i]刷成颜色j
                int cost = costs[i][j] + (j != lastCol ? min1 : min2);
                if (cost < mn1) {  // 新最小值,更新次小值和最小值对应的颜色
                    mn2 = mn1;
                    mn1 = cost;
                    mn1Col = j;
                } else if (cost < mn2) {  // 新次小值,最小值和对应颜色不变
                    mn2 = cost;
                }
            }
            // 算完一个房子,更新当前总花费的最小和次小,继续刷下一个房子
            min1 = mn1;
            min2 = mn2;
            lastCol = mn1Col;
        }
        return min1;
    }

    int minCostII0(const vector<vector<int>> &costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        int m = costs.size(), n = costs[0].size();

        int lastMin1Col = 0, lastMin2Col = 0;
        vector<vector<int>> dp = costs;  // 初始化dp[i][j]=cost[i][j]
        for (int i = 0; i < m; ++i) {
            int curMin1Col = lastMin1Col, curMin2Col = lastMin2Col;
            for (int j = 0; j < n; ++j) {
                if (i > 0) {  // 从刷第2个房子开始才累加刷前面房子的花费
                    dp[i][j] += j != lastMin1Col
                        ? dp[i - 1][lastMin1Col]   // 累加前房子最小花费
                        : dp[i - 1][lastMin2Col];  // 累加前房子次小花费
                }
                if (dp[i][j] < dp[i][lastMin1Col]) {  // 新最小值
                    curMin2Col = curMin1Col;
                    curMin1Col = j;
                } else if (dp[i][j] < dp[i][lastMin2Col]) {  // 新次小值
                    curMin2Col = j;
                }
            }
            lastMin1Col = curMin1Col, lastMin2Col = curMin2Col;
        }
        return dp.back()[lastMin1Col];
    }
};
