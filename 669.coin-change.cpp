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
 */
class Solution {
public:
    /**
     * @param coins: a list of integer
     * @param amount: a total amount of money amount
     * @return: the fewest number of coins that you need to make up
     */
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < coins.size(); ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];
    }
};
