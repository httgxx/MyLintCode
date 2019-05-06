/*
 * @lc app=lintcode id=395 lang=cpp
 *
 * [395] Coins in a Line II
 *
 * https://www.lintcode.com/problem/coins-in-a-line-ii/description
 *
 * lintcode
 * Medium (35.00%)
 * Total Accepted:    11196
 * Total Submissions: 31487
 * Testcase Example:  '[1,2,2]\n'
 *
 * There are n coins with different value in a line. Two players take turns to
 * take one or two coins from **left side** until there are no more coins left.
 * The player who take the coins with the most value wins.
 * 
 * Could you please decide the **first** player will win or lose?
 * 
 * If the first player wins, return `true`, otherwise return `false`.
 * 
 * Example 1:
 * Input: [1, 2, 2]
 * Output: true
 * Explanation: The first player takes 2 coins.
 * 
 * Example 2:
 * Input: [1, 2, 4]
 * Output: false
 * Explanation: Whether the first player takes 1 coin or 2, the second player will gain more value.
 * Related Problems
 * 
 * 与Coins in a Line I 的区别：
 * 每个硬币值不同
 * 最后取得硬币总值大的选手获胜
 *
 * @Category DP(输赢比较型)
 * @Idea
 * DP // T=O(n) S=O(n)=>降维O(1)
 * dp[i]表示面对第i个硬币的选手从[i]到最后能取得最大硬币总值
 * 面对第i个硬币的当前选手可取1个或2个：
 *   若当前选手只取1个即[i],则对手可取1个或取2个
 *     若对手只取1个即[i+1], 当前选手将面对[i+2](能取最大值为dp[i+2])
 *     若对手取2个即[i+1]+[i+2], 当前选手将面对[i+3](能取最大值为dp[i+3])
 *     由于对手一定会让当前选手得较小值, 所以当前选手只能拿dp[i+2]和dp[i+3]中较小的一个
 *   =>当前选手面对[i]时能取最大值= a[i] + min(dp[i+2], dp[i+3])
 *   若当前选手取2个即[i]+[i+1],则对手可取1个或取2个
 *     若对手只取1个即[i+2], 当前选手将面对[i+3](能取最大值为dp[i+3])
 *     若对手取2个即[i+2]+[i+3], 当前选手将面对[i+4](能取最大值为dp[i+4])
 *     由于对手一定会让当前选手得到较小值, 所以当前选手只能拿dp[i+3]和dp[i+4]中较小的一个
 *   =>当前选手面对[i]时能取最大值= a[i] + a[i+1] + min(dp[i+3], dp[i+4])
 * 当前选手会按两种情况中得到值较大的方案取,即
 * dp[i] = max(a[i]+min(dp[i+2], dp[i+3]), a[i]+a[i+1]+ min(dp[i+3], dp[i+4]))
 *
 * 初始 dp[n-1]=a[n-1], dp[n-2]=a[n-2]+a[n-1], dp[n-3]=a[n-3]+a[n-2]
 * 返回 if dp[0] > sum-dp[0]
 * 坑   最后需计算sum-dp[0]并检查是否dp[0]>sum-dp[0]
 */
class Solution {
public:
    /**
     * @param values: a vector of integers
     * @return: a boolean which equals to true if the first player will win
     */
    bool firstWillWin(vector<int> &values) {
        if (values.size() <= 2) return true;

        int n = values.size();
        vector<int> dp(n, 0);
        dp[n - 1] = values[n - 1];
        dp[n - 2] = values[n - 2] + values[n - 1];
        dp[n - 3] = values[n - 3] + values[n - 2];
            
        for (int i = n - 4; i >= 0; --i) {
            dp[i] = max(values[i] + min(dp[i + 2], dp[i + 3]), 
                        values[i] + values[i + 1] + min(dp[i + 3], dp[i + 4]));
        }

        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += values[i];
        }

        return dp[0] > (sum - dp[0]);
    }
};
