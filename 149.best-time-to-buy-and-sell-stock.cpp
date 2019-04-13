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
 * 最多买卖1次的最大利润
 * = max(第i天价格//卖出价-第i天为止最低价//买入价)|i=0~n-1
 */
class Solution {
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(const vector<int> &prices) {
        int profit = 0, buy = INT_MAX;
        for (int price : prices) {
            buy = min(buy, price);  // 记录当天为止最低价格作为买入价
            profit = max(profit, price - buy);  // 记录当天卖出能得最高获利
        }
        return profit;
    }
};
