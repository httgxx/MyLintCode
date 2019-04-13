/*
 * @lc app=lintcode id=669 lang=cpp
 *
 * [669] Coin Change
 *
 * https://www.lintcode.com/problem/coin-change/description
 *
 * lintcode
 * Medium (36.00%)
 * Total Accepted:    3620
 * Total Submissions: 9870
 * Testcase Example:  '[1,2,5]\n11\n'
 *
 * You are given coins of different denominations and a total amount of money
 * amount. Write a function to compute the fewest number of coins that you need
 * to make up that amount. If that amount of money cannot be made up by any
 * combination of the coins, return `-1`.
 *
 * @Category DP,DFS+Memo
 * @Ideas
 * S1: DP //T=O(n) S=O(n)
 * dp[i]表示够成钱数i所需的最少硬币数目
 * 对钱数i,用每种面值小于i的硬币去更新所需最小硬币总数
 * dp[i]=min{dp[i], dp[i-coins[j]]+1}|coins[j]<i
 * 初始 dp[0]=0 dp[i>0]=amount+1(表示不能正好凑成)
 * 顺序 由0到amount
 * 返回 dp[amount]
 * 坑: 用amount+1代表INT_MAX因为有dp[x]+1的操作可能溢出
 * 坑: 最后要检查是否=amount+1来返回-1,因为有可能无法正好凑成amount
 * 
 * S2: DFS+剪枝 (amount太大会超时) T=? S=?
 * 硬币按面值由大到小排序,每次先用尽可能多个当前最大面值的硬币去凑
 * 正好凑足则更新res,但任然会依次减少最大面值硬币的数量,再用剩下的硬币面值去试
 * 直到所有面值都被用过才返回
 * // 问题:在没有试过所有面试硬币的情况下amount==0时就不去更新res么???
 */
class Solution {
public:
    /**
     * @param coins: a list of integer
     * @param amount: a total amount of money amount
     * @return: the fewest number of coins that you need to make up
     */
    // S1: DP T=O(amount*n) S=O(amount)
    int coinChange(const vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);  // 坑: 用INT_MAX之后+1会溢出
                                                 // 故用不可能的值amount+1同效
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int k = 0; k < coins.size(); ++k) {
                if (coins[k] <= i) {  
                    dp[i] = min(dp[i], dp[i - coins[k]] + 1);  // 用INT_MAX溢出
                }
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];  // 坑:有可能没法凑成
    }

    // S2: DFS+剪枝 amount太大会超时
    int coinChange2(vector<int>& coins, int amount) {
        sort(coins.rbegin(), coins.rend());  // 排序从大面值开始更快找到最小数目
        int res = INT_MAX;  // 或者res初始化成amount+1
        dfs(coins, 0, amount, 0, res);
        return (res == INT_MAX) ? -1 : res;  // 坑:有可能无法正好凑成amount
    }
    void dfs(const vector<int>& coins,
             int start, int amount, int count, int& res) {
        // 检查是否dfs已到底
        if (start == coins.size()) {
            // [问题]在没有试过所有面试硬币的情况下amount==0时我们不去更新res么???
            if (amount == 0) {  // 只有正好凑成amount才更新res
                res = min(res, count);
            }
            return;
        }
        // 剪枝: 新数目>res时停止dfs
        if (count >= res) {
            return;
        }
        // 有大到小枚举coin数目进行dfs. 特例:0面值的coin跳过否则引起除以0溢出
        for (int k = coins[start] ? amount / coins[start] : 0;
             k >= 0; --k) {
            dfs(coins, start + 1, amount - k * coins[start], count + k, res);
        }
    }
};
