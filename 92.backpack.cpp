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
 * @Category DP (01背包 单属性 最值型) 求n物品放入m背包能放物品的最大体积和
 * @Idea
 * S0: DP // T=O(nm) S=O(nm)
 * dp[i][j]表示前i个数放入容量m的背包可放最大体积和
 * dp[i][j]=max(dp[i-1][j]//不取a[i], a[i]+dp[i-1][j-a[i]]|j>=a[i]//取a[i])
 * 初始
 * dp[0][j]=0
 * dp[i][0]=0
 * 顺序
 * for i = 1~n
 *   for j = 1~m
 *     dp[i][j] = dp[i-1][j]
 *     if (j > a[i-1])  dp[i][j] = max(dp[i][j], a[i]+dp[i-1][j-a[i-1]])
 * 返回 dp[n][m]
 
 * S1: 降维 // T=O(nm) S=O(m)a
 * dp[i][j] = max(dp[i-1][j], dp[i-1][j-a[i-1]]+a[i-1])
 * [i][j]只跟[i-1][j]和[i-1][j-a[i-1]]相关,可降低1维
 * 大index的新值 += 大index的旧值 + 小index的旧值 => 必须先算大index的新值再算小index的新值
 * => for i = 1 ~ n  // 前i个数
 *      for j = m ~ 0 // 倒着循环j计算
 *        if(j>=a[i-1]) f[j] = max(f[j], f[j-a[i-1]]+a[i-1]) 
 * => for i = 0 ~ n - 1  // 改为用坐标i
 *      for j = m ~ a[i] // 倒着!!!循环j计算到A[i]截至
 *         f[j] = max(f[j], f[j-a[i]]+a[i])
 * 
 * 坑 最值型初始化一定注意,如此题中dp[0]=1而不是0
 * 坑 01背包:必须正着循环数组坐标1~n,1维则必须倒着循环目标和m~0(2维则可正循环) 
 *    因为每个A[i]只能用一次,所以数组坐标必须在外循环,目标和在内循环且只用到A[i](即m~A[i])否则要加if(j>=a[i])
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
 */
class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack0(int m, vector<int> &A) {
        int n = A.size();
        // dp[i][j]表示前i个数放入容量m的背包可放最大体积和
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));  // 初始化为0
        /*for (int i = 0; i <= n; ++i) { // 前i个物品任选放入容量0的背包能达到最大体积为0
            dp[i][0] = 0;  // =初始化值0,故可不写
        }
        for (int j = 1; j <= m; ++j) {  // 前0个物品任选放入容量j的背包能达到最大体积为0
            dp[0][j] = 0;  // =初始化值0,故可不写 
        }*/

        for (int i = 1; i <= n; ++i) {  // 前i个数 注:前0个数已初始化
            for (int j = 1; j <= m; ++j) {  // 目标和j 注:j=0已初始化
                dp[i][j] = dp[i - 1][j];  // 不取物品A[i-1]
                if (j >= A[i - 1]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - A[i - 1]] + A[i - 1]);  // 取物品A[i-1]
                }
            }
        }
        return dp[n][m];
    }

    // 降维 
    // dp[i][j] = max(dp[i-1][j], dp[i-1][j-A[i-1]]+A[i-1])
    // [i][j]只跟[i-1][j]和[i-1][j-A[i-1]]相关,可降低1维
    // 大index的新值 += 大index的旧值 + 小index的旧值 => 必须先算大index的新值再算小index的新值
    // => for i = 1 ~ n  // 前i个数
    //        for j = target ~ 0 // 倒着循环j计算
    //           if(j>=A[i-1]) f[j] = max(f[j], f[j-A[i-1]]+A[i-1]) 
    // => for i = 0 ~ n - 1  // 改为用坐标i
    //        for j = target ~ A[i] // 倒着循环j计算到A[i]截至
    //           f[j] = max(f[j], f[j-A[i]]+A[i])
    int backPack(int m, vector<int> &A) {
        vector<int> dp(m + 1, 0);  // 坑: 初始化成0
        for (int i = 0; i < A.size(); ++i) {  // 物品[i]
            for (int j = m; j >= A[i]; --j) {  // 背包容量j 坑: 必须倒循环因为用的旧dp[i - A[j]
                dp[j] = max(dp[j], dp[j - A[i]] + A[i]);
            }
        }
        return dp[m];
    }
};
