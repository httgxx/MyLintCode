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
 * There is a stone game.At the beginning of the game the player picks n piles of stones  `in a circle`.
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
 * @Category DP 区间型 有环 
 * @Idea dp+有环
 * 有环则从环任意地方开始,须延长sum到所有可能起点都到终点才可,即2n-1长,e.g.[1,2,3] => [1,2,3,1,2]
 * 计算sum[i]=sum[i-1]+A[i%n] //而非A[i]因为有循环外延
 * dp[i][j]代表从i合并到j的最少花费=min(dp[i][k] + dp[k+1][j] + sum[i,j])
 * sum[i,j]=prefixSum[j]-(i>0?prefixSum[i-1]:0) //坑!()必须要
 * 最后返回min{dp[i][i+n-1] | 0<=i<=n-1}
 * 
 * 坑: sum[i]=sum[i-1]+A[i%n]
 * 坑: sum[i,j]=prefixSum[j]-(i>0?prefixSum[i-1]:0)的括号不能少!!!
 * 坑: 返回不是dp[0][n-1]而是min{dp[i][i+n-1] | 0<=i<=n-1}
 */
class Solution {
public:
    /**
     * @param A: An integer array
     * @return: An integer
     */
    // dp[i][j]代表从i合并到j的最少花费=min(dp[i][k] + dp[k+1][j] + sum[i,j])
    // sum[i,j]=prefixSum[j]-(i>0?prefixSum[i-1]:0) //坑!()必须要
    // 有环则从环任意地方开始,须延长sum到所有可能起点都到终点才可,即2n-1长,e.g.[1,2,3] => [1,2,3,1,2]
    // 计算sum[i]=sum[i-1]+A[i%n] //而非A[i]因为有循环外延
    // 最后返回min{dp[i][i+n-1] | 0<=i<=n-1}
    // T=O(n^2) S=O(n^2)
    int stoneGame2(vector<int> &A) {
        int n = A.size();
        if (n <= 1) { return 0; }                               // 坑:单堆不需合并,花费为0而非A[0]!!

        int m = 2 * n - 1;
        vector<int> sum(m, 0);                                 // 计算前缀和sum[i]=[0,i]间石子重量和
        sum[0] = A[0];                                          // sum[0]单独赋,再for(1~2n-1)循环计算
        for (int i = 1; i < m; ++i) {
            sum[i] = sum[i - 1] + A[i % n];                     // 坑: +A[i%n]而非A[i]
        }

        vector<vector<int>> dp(m, vector<int>(m, INT_MAX));     // dp求最小值故初始化成INT_MAX
        for (int i = 0; i < m; ++i) { dp[i][i] = 0; }           // 坑!:单堆不需合并dp[i][i]=0而非A[i]

        for (int len = 2; len <= m; ++len) {                    // 枚举区间长度k>=2
            for (int i = 0; i + len - 1 < m; ++i) {             //   枚举区间起点i
                int last = i + len - 1;
                int t = sum[last] - (i > 0 ? sum[i - 1] : 0);   // [i,j]间石子重量和=sum[j]-sum[i-1] // 坑!别忘()!!!
                for (int k = i; k < last; ++k) {                // 枚举[i,i+len]中k,使得dp[i][j]最小
                    dp[i][last] = min(dp[i][last], dp[i][k] + dp[k + 1][last] + t);
                }
            }
        }
        
        int res = INT_MAX;
        for (int i = 0; i < n; ++i) {
            res = min(res, dp[i][i + n - 1]);                   // 最后返回min{dp[i][i+n-1] | 0<=i<=n-1}
        }
        return res;
    }
};
