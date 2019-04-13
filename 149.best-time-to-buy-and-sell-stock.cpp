/*
 * @lc app=lintcode id=149 lang=cpp
 *
 * [149] Best Time to Buy and Sell Stock
 *
 * https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock/description
 *
 * lintcode
 * Medium (44.00%)
 * Total Accepted:    17616
 * Total Submissions: 40015
 * Testcase Example:  '[3, 2, 3, 1, 2]'
 *
 * Say you have an array for which the *i*th element is the price of a given
 * stock on day *i*.
 * 
 * If you were only permitted to complete at most one transaction (ie, buy one
 * and sell one share of the stock), design an algorithm to find the maximum
 * profit.
 * 
 * @Category DP,枚举
 * @Ideas
 * DP // T=O(n) S=O(1)
 * 最多买卖1次的最大获利
 * = max{第i天卖的获利=第i天价格-第i天之前的最低价}|每天
 */
class Solution {
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(const vector<int> &prices) {
        if (prices.empty()) { return 0; }  // 特例
        int profit = 0, buy = prices[0];
        for (int i = 1; i < prices.size(); ++i) {  // 从第2天开始可以选一天卖了
            profit = max(profit, prices[i] - buy);  // 当天卖获利=当天-之前最低
            buy = min(buy, prices[i]);  // 更新目前位置最低价
        }
        return profit;
    }
};
