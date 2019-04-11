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
 */
class Solution {
public:
    /**
     * @param costs: n x 3 cost matrix
     * @return: An integer, the minimum cost to paint all houses
     */
    int minCost(vector<vector<int>> &costs) {
        if (costs.empty() || costs[0].empty()) { return 0; }
        vector<vector<int>> dp = costs;
        for (int i = 1; i < dp.size(); ++i) {
            for (int j = 0; j < 3; ++j) {
                dp[i][j] += min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
            }
        }
        return min(min(dp.back()[0], dp.back()[1]), dp.back()[2]);
    }
};
