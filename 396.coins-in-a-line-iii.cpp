/*
 * @lc app=lintcode id=396 lang=cpp
 *
 * [396] Coins in a Line III
 *
 * https://www.lintcode.com/problem/coins-in-a-line-iii/description
 *
 * lintcode
 * Hard (39.00%)
 * Total Accepted:    6724
 * Total Submissions: 16958
 * Testcase Example:  '[3,2,2]'
 *
 * There are `n` coins in a line, and value of `i-th` coin is `values[i]`. 
 * 
 * Two players take turns to take a coin from one of the ends of the line until
 * there are no more coins left. The player with the larger amount of money
 * wins.
 * 
 * Could you please decide **the first player** will win or lose?
 * 
 * Example 1:
 * Input: [3, 2, 2]
 * Output: true
 * Explanation: The first player takes 3 at first. Then they both take 2.
 * 
 * Example 2:
 * Input: [1, 20, 4]
 * Output: false
 * Explanation: The second player will take 20 whether the first player take 1 or 4.
 * 
 * 与Coins in a Line II 的区别
 * 只能拿1个硬币但是每次可以从最左边或最右边取
 * 
 * @Category DP(输赢比较型)
 * dp[i,j]: 面对第i到j个硬币的选手最后能取得最大硬币总值
 * 若当前选手取[i],剩下硬币区间[i+1,j]
 *   若对手取[i+1],之后当前选手可最大得到dp(i+2,j)
 *   若对手取[j],之后当前选手可最大得到dp(i+1,j-1)
 *  => 当前选手能拿最大值为 a[i] + min(dp(i+1,j-1), dp(i+2,j))
 * 若当前选手取[j],剩下硬币区间[i,j-1]
 *   若对手取[i],之后当前选手可最大得到dp(i+1,j-1)
 *   若对手取[j-1],之后当前选手可最大得到dp(i,j-2)
 * => 当前选手能拿最大值为 a[j] + min(dp(i+1,j-1),dp(i,j-2))
 * 当前选手选两种选择下最大值
 * => dp[i][j]= max(a[i] + min(dp(i+1,j-1), dp(i+2,j)), a[j] + min(dp(i+1,j-1),dp(i,j-2)))
 * 
 * 初始
 * for i=0~n-1
 * dp[i][i] = values[i];
 * dp[i][i+1] = max(a[i], a[i+1]);
 * 顺序
 * for (int span = 2; span < n; span++)
 *    for (int i = 0, j = i + span; i < n && j < n; i++, j++)
 *       int get_i = values[i] + min(dp[i + 1][j - 1], dp[i + 2][j]);
 *       int get_j = values[j] + min(dp[i][j - 2], dp[i + 1][j - 1]);
 *       dp[i][j] = max(get_i, get_j);
 */
class Solution {
public:
    /**
     * @param values: a vector of integers
     * @return: a boolean which equals to true if the first player will win
     */
    bool firstWillWin(vector<int> &values) {
        int n = values.size();
        if (n == 0) { return false; }
        if (n <= 2) { return true; }

        int sum = 0;
        vector<vector<int> > dp(n, vector<int>(n, 0) );
        for (int i = 0; i < n; i++) {
            dp[i][i] = values[i];
            sum += values[i];
        }
        for (int i = 0; i < n - 1; i++) {
            dp[i][i + 1] = max(values[i], values[i + 1]);
        }
        for (int span = 2; span < n; span++) {
            for (int i = 0, j = i + span; i < n && j < n; i++, j++) {
                int get_i = values[i] + min(dp[i + 1][j - 1], dp[i + 2][j]);
                int get_j = values[j] + min(dp[i][j - 2], dp[i + 1][j - 1]);
                dp[i][j] = max(get_i, get_j);
            }
        }

        return dp[0][n - 1]  > sum - dp[0][n-1];
    }
};
