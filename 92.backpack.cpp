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
 * S1: dp[i]表示背包容量为i时能放入的物品体积最大值
 * dp[i]= 
 * for i=0~n  // 每个物品
     for j=m~1  // 倒循环每种背包容量
       if(j>=a[i])  // 若背包容量>=物品i体积a[i]
         dp[j]=max(dp[j], dp[j-a[i]]+a[i])  // max(不放a[i],放a[i])
 * 初始 dp[0]=0 dp.size=n+1
 * 返回 dp[n]
 * 坑 dp[i]的i是背包容量大小i,不是第i个物品的i
 * 
 * S2: dp[i]表示体积和V能否被构成(T/F))
 * dp[i]= 物品i放或不放
 * 返回 最大的i使dp[i]=true
 * 
 * 参考 https://segmentfault.com/a/1190000006325321
 */
class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector<int> &A) {
        vector<int> dp(m + 1, 0);
        for (int j = 0; j < A.size(); ++j) {
            for (int i = m; i >= A[j]; --i) {
                dp[i] = max(dp[i], dp[i - A[j]] + A[j]);
            }
        }
        return dp[m];
    }
};
