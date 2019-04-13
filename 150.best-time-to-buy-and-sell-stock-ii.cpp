/*
 * @lc app=lintcode id=150 lang=cpp
 *
 * [150] Best Time to Buy and Sell Stock II 
 *
 * https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock-ii/description
 *
 * lintcode
 * Medium (51.00%)
 * Total Accepted:    11526
 * Total Submissions: 22206
 * Testcase Example:  '[]\n'
 *
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.Design an algorithm to find the maximum profit. You may
 * complete as many transactions as you like (ie, buy one and sell one share of
 * the stock multiple times). However, you may not engage in multiple
 * transactions at the same time (ie, you must sell the stock before you buy
 * again).
 * 
 * @Category DP,枚举
 * @Ideas
 * DP // T=O(n) S=O(1)
 * 可以买卖任意次的最大获利
 * = 求和(每天只要比前一天股价高就进行买卖)
 * 坑: prices为空的特例
 * 坑: i=1~
 */
class Solution {
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(vector<int> &prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); ++i) {
            res += max(prices[i] - prices[i - 1], 0);
        }
        return res;
    }
};
