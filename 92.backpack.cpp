/*
 * @lc app=lintcode id=92 lang=cpp
 *
 * [92] Backpack
 *
 * https://www.lintcode.com/problem/backpack/description
 *
 * lintcode
 * Medium (28.00%)
 * Total Accepted:    26275
 * Total Submissions: 91203
 * Testcase Example:  '10\n[3,4,8,5]\r\n'
 *
 * Given *n* items with size Ai, an integer *m* denotes the size of a backpack.
 * How full you can fill this backpack?
 * 
 * Example 1:
 * Input:  [3,4,8,5], backpack size=10
 * Output:  9
 * 
 * Example 2:
 * Input:  [2,3,5,7], backpack size=12
 * Output:  12
 * 
 * N物品放入容量V的背包,每物品只能放1次,可选放或不放,求能放入背包的物品体积和的最大值
 * 单次选择+最大体积
 * 
 * @Category DP(01背包型)
 * @Idea
 * S1: DP // T=O(mn) S=O(m)
 * dp[i]表示背包容量为i时能放入的物品体积最大值
 * dp[i]= 每多1个物品可选放或不放时,背包容量由小到大时能放入的物品体积和最大值
 * for j=0~n  // 每个物品
 *   for i=m~a[j]  // 每种能装下当前物品的背包容量
 *      dp[i]=max(dp[i], dp[i-a[j]]+a[j])  // max(不放a[i],放a[i])
 * 初始 dp[0~m]=0
 * 顺序 外循环第0~n-1个物品,内循环背包容量m~A[i](必须倒叙)因为需根据旧值而不是新值修改当前值
 * 返回 dp[m]
 * 坑 初始化成0而不是INT_MIN
 * 坑 dp[i]的i是背包容量大小i,不是第i个物品的i
 * 坑 必须倒循环i=m~A[j]因为要用旧dp[i-A[j]]计算
 * 
 * 实例 [3,4,8,5] m=9
 * j=0 a[j]=3
 *   i=9 dp[9]=max(0,dp[9-3]+3=3)=3
 *   i=8 dp[8]=max(0,dp[8-3]+3=3)=3
 *   i=7 dp[7]=max(0,dp[7-3]+3=3)=3
 *   i=6 dp[6]=max(0,dp[6-3]+3=3)=3
 *   i=5 dp[5]=max(0,dp[5-3]+3=3)=3
 *   i=4 dp[4]=max(0,dp[4-3]+3=3)=3
 *   i=3 dp[3]=max(0,dp[3-3]+3=3)=3
 * j=1 a[j]=4
 *   i=9 dp[9]=max(3,dp[9-4]+4=3+4=7)=7  //坑:若不倒循环i=m->A[j]则用到的dp[5]是新值4而不是旧值3
 *   i=8 dp[8]=max(3,dp[8-4]+4=3+4=7)=7
 *   i=7 dp[7]=max(3,dp[7-4]+4=3+4=7)=7
 *   i=6 dp[6]=max(3,dp[6-4]+4=0+4=4)=4
 *   i=5 dp[5]=max(3,dp[5-4]+4=0+4=4)=4
 *   i=4 dp[4]=max(3,dp[4-4]+4=0+4=4)=4
 * j=2 a[j]=8
 *   i=9 dp[9]=max(7,dp[9-8]+8=0+8=8)=8
 *   i=8 dp[8]=max(7,dp[8-8]+8=0+8=8)=8
 * j=3 a[j]=5
 *   i=9 dp[9]=max(8,dp[9-5]+5=4+5=9)=9
 *   i=8 dp[8]=max(8,dp[8-5]+5=4+5=9)=9
 *   i=7 dp[7]=max(7,dp[7-5]+5=0+5=5)=7
 *   i=6 dp[6]=max(4,dp[6-5]+5=0+5=5)=5
 *   i=5 dp[5]=max(4,dp[5-5]+5=0+5=5)=5
 * return dp[9]=9
 * 
 * 参考网友 https://segmentfault.com/a/1190000006325321
 * 
 * S2: DP // T=O(mn) S=O(mn) //TLE!!
 * dp[i][j]表示前i个物品能否被构成体积和j(true/false)
 * dp[i][j]=不用当前最后1个物品[i-1](前i-1个物品已经构成j) or 用[i-1](前i-1个物品构成j-a[i-1])
 * = dp[i-1][j] || dp[i-1][j-A[i-1]]|j>A[i-1]
 * 返回 使dp[n][j]=true的最大j
 */
class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector<int> &A) {
        vector<int> dp(m + 1, 0);  // 坑: 初始化成0而不是INT_MIN
        for (int j = 0; j < A.size(); ++j) {  // 每个物品
            for (int i = m; i >= A[j]; --i) {  // 坑: 必须倒循环因为用的旧dp[i - A[j]
                dp[i] = max(dp[i], dp[i - A[j]] + A[j]);
            }
        }
        return dp[m];
    }

    int backPack1(int m, vector<int> &A) {  // TLE!!
        int n = A.size();
        if (n == 0) return 0;

        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {  // 前i个物品
            for (int j = 0; j <= m; ++j) {  // 构成体积和j
                dp[i][j] = dp[i - 1][j] ||
                    (j >= A[i - 1] && dp[i - 1][j - A[i - 1]]);  // 坑 j>=A[j-1]前提
            }
        }

        for (int j = m; j >=0; --j) {  // 找到使得dp[n][j]为true的最大j
            if (dp[n][j]) return j;
        }

        return 0;
    }
};
