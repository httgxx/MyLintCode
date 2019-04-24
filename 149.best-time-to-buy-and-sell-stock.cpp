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
 * @Category DP(比较型),枚举
 * @Ideas
 * 最多可买卖1次的最大获利
 * DP // T=O(n) S=O(1)
 * = max{第i天卖的获利=第i天价格-第i天之前的最低价}|每天
 * 坑: 先处理特例size<=1
 * 坑: i从1而不是0开始,从第2天(i=1)才可以开始卖
 * 坑: 先用旧的最低价算最大收益,再算新的最低价
 */
class Solution {
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(const vector<int> &prices) {
        if (prices.size() < 2) { return 0; }  // 只能第1天之后卖

        int profit = 0, minPrice = prices[0];  // 当前最低价格
        for (int i = 1; i < prices.size(); ++i) {  // 坑:i=1,第2天才可以开始卖
            profit = max(profit, prices[i] - minPrice); // 最大利=当天-之前最低
            minPrice = min(minPrice, prices[i]);  // 时刻保持当前最低价格
        }
        return profit;
    }
};
