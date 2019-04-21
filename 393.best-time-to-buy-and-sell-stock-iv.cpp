/*
 * @lc app=lintcode id=393 lang=cpp
 *
 * [393] Best Time to Buy and Sell Stock IV
 *
 * https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock-iv/description
 *
 * lintcode
 * Hard (26.00%)
 * Total Accepted:    7279
 * Total Submissions: 27254
 * Testcase Example:  '1\n[1,2]\n'
 *
 * Say you have an array for which the *i*th element is the price of a given
 * stock on day *i*.
 * 
 * Design an algorithm to find the maximum profit. You may complete at most `k`
 * transactions.
 * 
 * @Category DP(按情况叠加比较型)
 * @Ideas
 * 可以买卖k次的最大获利
 * case1: k>=n/2 => 等同于可以交易无限多次的情况 
 * case2: 
 * local[i][j] = max(global[i-1][j-1] + max(diff, 0), local[i - 1][j] + diff)
 * global[i][j] = max(local[i][j], global[i - 1][j])
 */
class Solution {
public:
    /**
     * @param K: An integer
     * @param prices: An integer array
     * @return: Maximum profit
     */
    int maxProfit(int k, vector<int> &prices) {
        if (prices.empty()) return 0;
        if (k >= prices.size()/2) return solveMaxProfit(prices);
        int g[k + 1] = {0};
        int l[k + 1] = {0};
        for (int i = 0; i < prices.size() - 1; ++i) {
            int diff = prices[i + 1] - prices[i];
            for (int j = k; j >= 1; --j) {
                l[j] = max(g[j - 1] + max(diff, 0), l[j] + diff);
                g[j] = max(g[j], l[j]);
            }
        }
        return g[k];
    }
    int solveMaxProfit(vector<int> &prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] - prices[i - 1] > 0) {
                res += prices[i] - prices[i - 1];
            }
        }
        return res;
    }
};
