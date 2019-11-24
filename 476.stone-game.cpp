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
 * There is a stone game.At the beginning of the game the player picks `n` piles of stones in a line.
 * 
 * The goal is to merge the stones in one pile observing the following rules: 
 * 1. At each step of the game,the player can merge two adjacent piles to a new pile.
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
 * @Idea DP 区间型
 * 每次合并相邻石头堆cost为两堆之和,求最小总cost
 * sum[i]表示原序列[0,i]区间的石子重量和=>[i,j]间石子重量和=sum[j]-sum[i-1]
 * dp[i][j]表示合并原序列[i,j]区间的石子的最小代价
 * 找i和j之间的k使得dp[i][j]最小
 * = min{dp[i][k] + dp[k+1][j] + sum[i][j] | k=[i,j)}
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
        if (n <= 1) { return 0; }                       // 特例:空串或只有1堆
        vector<int> sum(n, 0);                          // 计算前缀和sum[i]=[0,i]间石子重量和
        sum[0] = A[0];                                  // sum[0]单独赋值,for(1~n-1)
        for (int i = 1; i < n; ++i) { sum[i] = sum[i - 1] + A[i]; }
        vector<vector<int>> dp(n, vector<int>(n, 0));   // dp[i][j]表示合并[i,j]间石子的最小代价
        for (int len = 1; len <= n; ++len) {            // 枚举区间长度
            for (int i = 0; i + len < n; ++i) {         //   枚举区间起点
                int curSum = sum[i + len] - sum[i - 1]; //     [i,j]间石子重量和=sum[j]-sum[i-1]
                dp[i][i + len] = INT_MAX;
                for (int k = i; k < i + len; ++k) {     //     枚举[i,i+len]间k更新dp[i][j]最小值
                    dp[i][i + len] = min(dp[i][i + len], dp[i][k] + dp[k + 1][i + len] + curSum);
                }
            }
        }
        return dp[0][n - 1];
    }
};
