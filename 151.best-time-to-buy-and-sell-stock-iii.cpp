/*
 * @lc app=lintcode id=151 lang=cpp
 *
 * [151] Best Time to Buy and Sell Stock III 
 *
 * https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock-iii/description
 *
 * lintcode
 * Medium (29.00%)
 * Total Accepted:    9888
 * Total Submissions: 33591
 * Testcase Example:  '[]\n'
 *
 * Say you have an array for which the _i_th element is the price of a given
 * stock on day _i_.
 * Design an algorithm to find the **maximum** profit. You may complete at most
 * _two_ transactions.
 * 
 * @Category DP(按情况叠加比较型)
 * @Ideas
 * 最多可买卖2次的最大获利
 * DP // T=O(n) S=O(1)
 
 
 * S2: DP(比较型 2次遍历),枚举
 * DP  // T=O(n) S=O(n)
 * 第一次左到右,求只交易1次的话第i天的最大收益 p1[i]=max(p1[i-1],[i]-第1天到前一天为止的最小价格)
 * 第二次右到左,求第i天以后交易1次的最大收益 p2=max(p2,[i]-第i天到最后一天为止的最大价格 + p1[i])
 * 坑:vector要定义大小否则之后[]会index溢出
 * 坑:第一次遍历计算的每天最大值都得存(之后用来计算第2次交易的最大值),第二次遍历只用存当前最大值
 * 坑:左扫右时i=2开始++i,右扫左时i=n-2开始--i
 */
class Solution {
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(const vector<int> &prices) {
        int n = prices.size();
        if (n < 2) { return 0; }  // 特例
        // 第一次左扫到右:计算只交易1次且第i天完成交易的话,第i天能得到的最大收益
        int minPrice1 = prices[0];
        // 计算每天为止只完成1次交易的最大收益,每天都存因为要用其计算第2次交易最大值
        vector<int> profit1 = vector<int>(n, 0);  // 坑:要定义大小之后才能用[]
        for (int i = 1; i < n; ++i) {
            profit1[i] = max(profit1[i - 1], prices[i] - minPrice1);
            minPrice1 = min(minPrice1, prices[i]);  // 当前最小价格
        }
        // 第二次右扫到左:计算第i天完成第1次交易之后再完成第2次交易的最大总收益
        int maxPrice2 = prices[n - 1], profit2 = profit1[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            profit2 = max(profit2, maxPrice2 - prices[i] + profit1[i]);
            maxPrice2 = max(maxPrice2, prices[i]);  // 当前到最后一天的最大价格
        }
        return profit2;
    }
};
