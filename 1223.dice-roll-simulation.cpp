/*
 * @lc app=leetcode id=1223 lang=cpp
 *
 * [1223] Dice Roll Simulation
 *
 * https://leetcode.com/problems/dice-roll-simulation/description/
 *
 * algorithms
 * Medium (42.47%)
 * Total Accepted:    4.1K
 * Total Submissions: 9.7K
 * Testcase Example:  '2\n[1,1,2,2,2,3]'
 *
 * A die simulator generates a random number from 1 to 6 for each roll. You
 * introduced a constraint to the generator such that it cannot roll the number
 * i more than rollMax[i] (1-indexed) consecutive times. 
 * 
 * Given an array of integers rollMax and an integer n, return the number of
 * distinct sequences that can be obtained with exact n rolls.
 * 
 * Two sequences are considered different if at least one element differs from
 * each other. Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: n = 2, rollMax = [1,1,2,2,2,3]
 * Output: 34
 * Explanation: There will be 2 rolls of die, if there are no constraints on
 * the die, there are 6 * 6 = 36 possible combinations. In this case, looking
 * at rollMax array, the numbers 1 and 2 appear at most once consecutively,
 * therefore sequences (1,1) and (2,2) cannot occur, so the final answer is
 * 36-2 = 34.
 * 
 * Example 2:
 * Input: n = 2, rollMax = [1,1,1,1,1,1]
 * Output: 30
 * 
 * Example 3:
 * Input: n = 3, rollMax = [1,1,1,2,2,3]
 * Output: 181
 *
 * Constraints:
 * 1 <= n <= 5000
 * rollMax.length == 6
 * 1 <= rollMax[i] <= 15
 * 
 * @Category DP
 * @Idea DP
 * @reference: https://www.bilibili.com/video/av71187385/
 * S1: dp[i][j][k]表示第i次掷色子得j点且j已连续出现了k次
 * = if(k>1): dp[i-1][j][k-1]                                          =>T=O(5000*6*14)
 *   if(k==1): sum(dp[i-1][p][s] | p!=j且1<=s<=rollmax[p])             =>T=O(5000*6*5*15)
 *        优化=sum(dp[i-1][*][*])-sum(dp[i-1][j][s] | 1<=s<=rollmax[j])=>T=O(5000*6*15)//优化降低了5倍
 */
class Solution {
public:
    // DP
    // dp[i][j][k]表示第i次掷色子得j点且j已连续出现了k次
    // k==1时: dp[i][j][1]=sum(dp[i-1][*][*])-sum(dp[i-1][j][*]
    // k>1时:  dp[i][j][k]=dp[i-1][j][k-1]
    // 最后累加 dp[n][*][*]
    // T=O(m*n*k*t) m=掷色子最多次数 n=每个色子的最大值 k=点数可以连续出现的最大次数        
    int dieSimulator(int n, vector<int>& rollMax) {
        constexpr int kMaxRolls = 15;
        constexpr int kMod = 1e9 + 7;
        vector<vector<vector<int>>> dp(n + 1,                           // dp[i][j][k]=#of sequences ends with k consecutive j after i rolls
            vector<vector<int>>(6, vector<int>(kMaxRolls + 1)));        // 坑: +1!!!
        for (int j = 0; j < 6; ++j) { dp[1][j][1] = 1; }                // 初始化:掷1次色子得j点且j没重复的方案数=1
        for (int i = 2; i <= n; ++i) {                                  // 第i>=2次掷色子
            int sum = 0;
            for (int j = 0; j < 6; ++j) {
                for (int k = 1; k <= rollMax[j]; ++k) {
                    sum = (sum + dp[i - 1][j][k]) %kMod;                // 计算第i次得j最多连续出现k次的总方案数sum(dp[i][*][*])
                }
            }
            for (int j = 0; j < 6; ++j) {                               // 对每个可能得的点数j
                dp[i][j][1] = sum;
                for (int k = 1; k <= rollMax[j]; ++k) {                 //   对每个j连续出现的次数k
                    dp[i][j][1] =                                       //     k=1时=sum(dp[i-1][*][*])-sum(dp[i-1][j][*]
                        (dp[i][j][1] - dp[i - 1][j][k] + kMod) % kMod;  //     坑:因为有减法所以先+kMod再%kMod
                }
                for (int k = 2; k <= rollMax[j]; ++k) {                 //     k>1时=dp[i-1][j][k-1] 
                    dp[i][j][k] = dp[i - 1][j][k - 1]; 
                }
            }
        }
        int ans = 0;
        for (int j = 0; j < 6; ++j) {                                   // 累计dp[n][*][*]
            for (int k = 1; k <= rollMax[j]; ++k) {
                ans = (ans + dp[n][j][k]) % kMod;
            }
        }
        return ans;
    }
};
