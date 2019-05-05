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
 * Example 1:
 * Input: k = 2, prices = [4, 4, 6, 1, 1, 4, 2 ,5]
 * Output: 6
 * Explanation: Buy at 4 and sell at 6. Then buy at 1 and sell at 5. Your profit is 2 + 4 = 6.
 * Example 2:
 * Input: k = 1, prices = [3, 2, 1]
 * Output: 0
 * Explanation: No transaction.
 *
 * @Category DP(按情况叠加比较型)
 * @Ideas DP // T=O(kn) S=O(kn)->降维O(k)
 * 可以买卖k次的最大获利
 * case1: k>=n/2 => 等同于可以交易无限多次的情况 
 * case2: 
 * local[i][j] = max(global[i-1][j-1], local[i-1][j] + prices[i]-prices[i-1])
 * global[i][j] = max(local[i][j], global[i-1][j])
 * 坑: 千万别忘记case1 k>=n/2的情况!
 * 坑: 若降维则需要倒着j计算,因为计算local[i][j]要用到global[i-1][j-1],需用旧[j-1]算新[j],
 *     而降维后只存当前i的各个j值,所以[j-1]的更新只能在[j]的更新之后,否则是在用新[j-1]算新[j]
 * 
 * 公式推导
 * global[i][j]为第i天时最多j次交易的最大利润,是全局最优
 * 第i天卖或不卖?
 * 1. 第i天卖: global[i][j] = local[i][j]
 * 2. 第i天不卖: 第i天没交易,等价于第i-1天最多j次交易:global[i][j] = global[i-1][j]
 * =>递推公式 global[i][j] = max(local[i][j], global[i-1][j])
 * 
 * local[i][j]为第i天时最多j次交易且第i天卖第j支股票的最大利润,是局部最优
 * 第i天卖的第j支股票利润多少=>何时买的?
 * 1.第i-1天买的:
 *   local[i][j]=global[i-1][j-1]+(prices[i]-prices[j])
 * 2.第i-1天之前买的:不好计算先前哪天买的以及买入价,就用差值法将买入价抵消
 *   第i天卖的利润 = 若第i-1天卖的利润 + (第i天卖的利润-若第i-1天卖的利润)
 *   local[i][j]=local[i-1][j]+(prices[i]-buy)-(prices[i-1]-buy)
 *              =local[i-1][j]+(prices[i]-prices[i-1])
 * =>递推公式 local[i][j] = max(global[i-1][j-1], local[i-1][j])+prices[i]-prices[i-1]
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
        if (k >= prices.size()/2) return solveMaxProfit(prices);  // 坑:特例!!
        int g[k + 1] = {0};  // 坑:降维
        int l[k + 1] = {0};
        for (int i = 0; i < prices.size() - 1; ++i) {
            int diff = prices[i + 1] - prices[i];
            for (int j = k; j >= 1; --j) {  // 坑:降维后须倒着j计算
                l[j] = max(g[j - 1], l[j] + diff);
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
