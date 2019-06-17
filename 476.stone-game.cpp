/*
 * @lc app=lintcode id=476 lang=cpp
 *
 * [476] Stone Game
 *
 * https://www.lintcode.com/problem/stone-game/description
 *
 * lintcode
 * Medium (36.00%)
 * Total Accepted:    5346
 * Total Submissions: 14771
 * Testcase Example:  '[3,4,3]\n'
 *
 * There is a stone game.At the beginning of the game the player picks `n`
 * piles of stones in a line.
 * 
 * The goal is to merge the stones in one pile observing the following rules: 
 * 1. At each step of the game,the player can merge two adjacent piles to a new
 * pile.
 * 2. The score is the number of stones in the new pile. 
 * 
 * You are to determine the minimum of the total score.
 * 
 * Example 1:
 * Input: [3, 4, 3]
 * Output: 17
 * 
 * Example 2:
 * Input: [4, 1, 1, 4]
 * Output: 18
 * Explanation:
 *  1. Merge second and third piles => [4, 2, 4], score = 2
 *  2. Merge the first two piles => [6, 4]，score = 8
 *  3. Merge the last two piles => [10], score = 18
 * 
 * @Category DP 区间型
 * dp[i][j]表示合并原序列[i,j]区间的石子的最小代价
 * dp[i][j] = min{dp[i][k] + dp[k+1][j]|k} + sum[i][j], sum[i][j]表示原序列[i,j]区间的石子重量和
 * 初始 f[i][i] = sum[i][i], f[i][i+1] = sum[i][i+1]
 * 返回 f[0][n-1]
 */
class Solution {
public:
    /**
     * @param A: An integer array
     * @return: An integer
     */
    int stoneGame(vector<int> &A) {
        int n = A.size();
        if (n <= 1) { return 0; }
        vector<int> sum, num;
        sum.resize(n + 1);
        num.resize(n + 1);

        vector<vector<int>> f, s;
        for (int i = 0; i <= n; i++) {
            f.push_back(num);
            s.push_back(num);
        }
        
        for (int i = 1; i <= n; i++) {
            num[i] = A[i-1];
            sum[i] = sum[i-1] + num[i];
            f[i][i] = 0;
            s[i][i] = i;
        }
        
        for (int len = 2; len <= n; len++)
            for (int i = 1; i <= n - len + 1; i++) {
                int j = i + len - 1;
                f[i][j] = 0x7fffffff / 3;
                for (int k = s[i][j-1]; k <= s[i+1][j]; k++)
                    if (f[i][k-1] + f[k][j] + sum[j] - sum[i-1] < f[i][j]) {
                        f[i][j] = f[i][k-1] + f[k][j] + sum[j] - sum[i-1];
                        s[i][j] = k;
                    }
            }
        return f[1][n];
    }
};
