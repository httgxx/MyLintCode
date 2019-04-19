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
            // 每刷1新房子就计算刷完它后当前总花费的最小和次小,起始总是INT_MAX
            int curMin1 = INT_MAX, curMin2 = INT_MAX, curMin1Col = -1;
            for (int j = 0; j < n; ++j) {  // 房子[i]刷成颜色j
                int cost = costs[i][j] + (j != lastCol ? min1 : min2);
                if (cost < curMin1) {  // 新最小值,更新次小值和最小值对应的颜色
                    curMin2 = curMin1;
                    curMin1 = cost;
                    curMin1Col = j;
                } else if (cost < curMin2) {  // 新次小值,最小值和对应颜色不变
                    curMin2 = cost;
                }
            }
            // 确定当前房子刷的颜色后,更新当前总花费的最小和次小,继续刷下个房子
            min1 = curMin1;
            min2 = curMin2;
            lastCol = curMin1Col;
        }
        return min1;
    }

    int minCostII1(const vector<vector<int>> &costs) {
        if (costs.empty() || costs[0].empty()) return 0;  // 特例
        int m = costs.size(), n = costs[0].size();
        int min1Col = 0, min2Col = 0;  // 当前总共花费最小和次小对应的颜色
        vector<vector<int>> dp = costs;  // 初始化dp[i][j]=cost[i][j]
        for (int i = 0; i < m; ++i) {
            // 每刷1新房子就计算刷完它后总花费最小和次小对应的颜色,起始总是-1
            int curMin1Col = -1, curMin2Col = -1;
            for (int j = 0; j < n; ++j) {
                if (i > 0) {  // 从刷第2个房子开始才累加刷前面房子的花费
                    dp[i][j] += j != min1Col
                        ? dp[i - 1][min1Col]   // 累加前房子最小花费
                        : dp[i - 1][min2Col];  // 累加前房子次小花费
                }
                if (dp[i][j] < dp[i][min1Col]) {  // 新最小值
                    curMin2Col = min1Col;
                    curMin1Col = j;
                } else if (dp[i][j] < dp[i][min1Col]) {  // 新次小值
                    curMin2Col = j;
                }
            }
            // 确定当前房子刷的颜色后,更新当前总花费的最小和次小,继续刷下个房子
            min1Col = curMin1Col;
            min2Col = curMin2Col;
        }
        return dp.back()[min1Col];
    }
};
