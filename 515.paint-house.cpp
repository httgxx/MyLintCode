/*
 * @lc app=lintcode id=515 lang=cpp
 *
 * [515] Paint House
 *
 * https://www.lintcode.com/problem/paint-house/description
 *
 * lintcode
 * Medium (40.00%)
 * Total Accepted:    5924
 * Total Submissions: 14532
 * Testcase Example:  '[[14,2,11],[11,14,5],[14,3,10]]\n'
 *
 * There are a row of `n` houses, each house can be painted with one of the
 * three colors: red, blue or green. The cost of painting each house with a
 * certain color is different. You have to paint all the houses such that **no
 * two adjacent houses have the same color,** and you need to cost the least.
 * Return the minimum cost. 
 * 
 * The cost of painting each house with a certain color is represented by a `n`
 * x `3` cost matrix. For example, `costs[0][0]` is the cost of painting house
 * `0` with color red; `costs[1][2]` is the cost of painting house `1` with
 * color green, and so on... Find the minimum cost to paint all houses.
 *
 * @Category DP(叠加比较型)
 * @Idea
 * 当前房子刷红色的最小花费=当前房子刷红色的钱 + min(刷到上个房子用绿色的最小花费,刷到上一个房子用蓝色的最小花费)
 * dp[i][j]表示刷房子([0]~[i])且房子[i]刷成颜色j的最小花费
 * dp[i][j] = min(dp[i-1][(j+1)%3],dp[i-1][(j+2)%3]) + costs[i][j]即房子[i]刷成颜色j的花费；
 */
class Solution {
public:
    /**
     * @param costs: n x 3 cost matrix
     * @return: An integer, the minimum cost to paint all houses
     */
    int minCost(vector<vector<int>> &costs) {
        if (costs.empty() || costs[0].empty()) { return 0; }
        vector<vector<int>> dp = costs;  // dp[i][j]初始化为costs[i][j]
        for (int i = 1; i < dp.size(); ++i) {  // i=1~n-1
            for (int j = 0; j < 3; ++j) {
                dp[i][j] += min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
            }
        }
        return min(min(dp.back()[0], dp.back()[1]), dp.back()[2]);
    }
};
