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
 * 坑:min,旧min1,min2的初始值是0而不是INT_MAX
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
    int minCostII0(const vector<vector<int>> &costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        vector<vector<int>> dp = costs;  // 初始化dp[i][j]=cost[i][j]
        int min1 = -1, min2 = -1;
        for (int i = 0; i < dp.size(); ++i) {
            int last1 = min1, last2 = min2;
            min1 = -1; min2 = -1;
            for (int j = 0; j < dp[i].size(); ++j) {
                if (j != last1) {
                    dp[i][j] += last1 < 0 ? 0 : dp[i - 1][last1];
                } else {
                    dp[i][j] += last2 < 0 ? 0 : dp[i - 1][last2];
                }
                if (min1 < 0 || dp[i][j] < dp[i][min1]) {
                    min2 = min1; min1 = j;
                } else if (min2 < 0 || dp[i][j] < dp[i][min2]) {
                    min2 = j;
                }
            }
        }
        return dp.back()[min1];
    }

    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        int lastMin1 = 0, lastMin2 = 0, lastCol = -1;  // 坑:0而不是INT_MAX
        for (int i = 0; i < costs.size(); ++i) {  // 房子[i]
            int curMin1 = INT_MAX, curMin2 = curMin1, curCol = -1;
            for (int j = 0; j < costs[i].size(); ++j) {  // 颜色[j]
                int cost = costs[i][j] + (j == lastCol ? lastMin2 : lastMin1);
                if (cost < curMin1) {
                    curMin2 = curMin1;
                    curMin1 = cost;
                    curCol = j;
                } else if (cost < curMin2) {
                    curMin2 = cost;
                }
            }
            lastMin1 = curMin1;
            lastMin2 = curMin2;
            lastCol = curCol;
        }
        return lastMin1;
    }
};
