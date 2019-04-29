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
 * DP // T=O(kn) S=O(kn)->降维O(k) k=2
 * global[i][j]为第i天时最多j次交易的最大利润,是全局最优
 * 第i天卖或不卖?
 * 1. 第i天卖: global[i][j] = local[i][j]
 * 2. 第i天不卖: 第i天没有交易不影响结果 global[i][j] = global[i-1][j]
 * =>递推公式 global[i][j] = max(global[i-1][j], local[i][j])
 * 
 * local[i][j] 为第i天时最多j次交易且第i天卖第j支股票的最大利润,是局部最优
 * 第i天卖的第j支股票利润多少=>何时买的?
 * 1.第i-1天买的:
 *   local[i][j]=global[i-1][j-1]+(prices[i]-prices[j])
 * 2.第i-1天之前买的:不好计算先前哪天买的以及买入价,就用差值法讲买入价抵消
 *   第i天卖的利润 = 若第i-1天卖的利润 + (第i天卖的利润-若第i-1天卖的利润)
 *   local[i][j]=local[i-1][j]+(prices[i]-buy)-(prices[i-1]-buy)
 *              =local[i-1][j]+(prices[i]-prices[i-1])
 * =>递推公式 local[i][j] = max(global[i-1][j-1], local[i-1][j]+prices[i]-prices[i-1])
 *
 * local[i][j] = max(global[i-1][j-1], local[i-1][j]+prices[i]-prices[i-1])
 * global[i][j] = max(global[i-1][j], local[i][j])
 * 
 * S2: DP(比较型 2次遍历),枚举
 * DP  // T=O(2n) S=O(n)
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
    int maxProfit(vector<int> &prices) {
        if (prices.empty()) return 0;
        int n = prices.size(), g[n][3] = {0}, l[n][3] = {0};
        for (int i = 1; i < prices.size(); ++i) {
            int diff = prices[i] - prices[i - 1];
            for (int j = 1; j <= 2; ++j) {
                l[i][j] = max(g[i - 1][j - 1] + max(diff, 0), l[i - 1][j] + diff);
                g[i][j] = max(l[i][j], g[i - 1][j]);
            }
        }
        return g[n - 1][2];
    }

    int maxProfit2(vector<int> &prices) {  // 降维
        if (prices.empty()) return 0;
        int g[3] = {0};
        int l[3] = {0};
        for (int i = 0; i < prices.size() - 1; ++i) {
            int diff = prices[i + 1] - prices[i];
            for (int j = 2; j >= 1; --j) {
                l[j] = max(g[j - 1] + max(diff, 0), l[j] + diff);
                g[j] = max(l[j], g[j]);
            }
        }
        return g[2];
    }

    int maxProfit1(const vector<int> &prices) {
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
