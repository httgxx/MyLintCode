/*
 * @lc app=lintcode id=593 lang=cpp
 *
 * [593] Stone Game II
 *
 * https://www.lintcode.com/problem/stone-game-ii/description
 *
 * lintcode
 * Medium (43.00%)
 * Total Accepted:    2285
 * Total Submissions: 5218
 * Testcase Example:  '[1,1,4,4]\n'
 *
 * There is a stone game.At the beginning of the game the player picks n piles
 * of stones  `in a circle`.
 * 
 * The goal is to merge the stones in one pile observing the following rules:
 * At each step of the game,the player can merge two adjacent piles to a new pile.
 * The score is the number of stones in the new pile.
 * 
 * You are to determine the minimum of the total score.
 * 
 * Example 1:
 * Input:[1,1,4,4]
 * Output:18
 * Explanation:
 * 1. Merge second and third piles => [2, 4, 4], score +2
 * 2. Merge the first two piles => [6, 4]，score +6
 * 3. Merge the last two piles => [10], score +10
 * 
 * Example 2:
 * Input:[1, 1, 1, 1]
 * Output:8
 * Explanation:
 * 1. Merge first and second piles => [2, 1, 1], score +2
 * 2. Merge the last two piles => [2, 2]，score +2
 * 3. Merge the last two piles => [4], score +4
 * 
 * @Category DP 区间型
 * dp[i][j]代表从i合并到j的最少花费。
 * dp[i][j] = min(dp[i][k] + dp[k+1][j] + sum[j + 1] - sum[i])
 */
class Solution {
public:
    /**
     * @param A: An integer array
     * @return: An integer
     */
    int stoneGame2(vector<int> &A) {
        int n = A.size();
        if (n <= 1) { return 0; }
        
        vector<int> sum(2 * n + 1);
        vector<vector<int> > dp(2 * n, vector<int>(2 * n));
        
        sum[0] = 0;
        for (int i = 0; i < 2 * n; i++) {
            sum[i + 1] = sum[i] + A[i % n];
            dp[i][i] = 0;

        }

        for (int len = 2; len <= 2 * n; len++)
            for (int i = 0; i < 2 * n && i + len <= 2 * n; i++) {
                int j = i + len - 1;
                dp[i][j] = 0x7fffffff / 4;
                for ( int k = i; k < j; k++)
                    if (dp[i][k] + dp[k + 1][j] + sum[j + 1] - sum[i] < dp[i][j]) {
                        dp[i][j] = dp[i][k]+dp[k + 1][j] + sum[j + 1] - sum[i];
                }
            }

        int ans = 0x7fffffff / 4;
        for (int i = 0; i < n; ++i) {
            if (dp[i][i + n - 1] < ans) { ans = dp[i][i + n - 1]; }
        }
        return ans;
    }
};
