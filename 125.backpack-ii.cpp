/*
 * @lc app=lintcode id=125 lang=cpp
 *
 * [125] Backpack II
 *
 * https://www.lintcode.com/problem/backpack-ii/description
 *
 * lintcode
 * Medium (43.00%)
 * Total Accepted:    17274
 * Total Submissions: 39342
 * Testcase Example:  '10\n[2,3,5,7]\n[1,5,2,4]'
 *
 * There are `n` items and a backpack with size `m`. Given array `A`
 * representing the size of each item and array `V` representing the value of
 * each item.
 * 
 * What's the maximum value can you put into the backpack?
 * 
 * Example 1:
 * Input:  a[3,4,8,5], backpack size=10
 * Output:  9
 * 
 * @Category DP (01背包 单属性 最值型) 求n物品放入m背包能放物品最大体积和
 * @Idea
 * S0: DP // T=O(nm) S=O(nm)
 * dp[i][j]表示前i个数放入容量m的背包可放最大体积和
 * dp[i][j]=max(dp[i-1][j]//不取a[i], v[i]+dp[i-1][j-a[i]]|j>=a[i]//取a[i]) 
 * 初始
 * dp[0][j]=0
 * dp[i][0]=0
 * 顺序
 * for i = 1~n
 *   for j = 1~m
 *     dp[i][j] = dp[i-1][j]
 *     if (j > a[i-1])  dp[i][j] = max(dp[i][j], v[i]+dp[i-1][j-a[i-1]])
 * 返回 dp[n][m]
 
 * S1: 降维 // T=O(nm) S=O(m)
 * dp[i][j] = max(dp[i-1][j], dp[i-1][j-a[i-1]]+a[i-1])
 * [i][j]只跟[i-1][j]和[i-1][j-a[i-1]]相关,可降低1维
 * 大index的新值 += 大index的旧值 + 小index的旧值 => 必须先算大index的新值再算小index的新值
 * => for i = 1 ~ n  // 前i个数
 *      for j = m ~ 0 // 倒着循环j计算
 *        if(j>=a[i-1]) f[j] = max(f[j], f[j-a[i-1]]+v[i-1]) 
 * => for i = 0 ~ n - 1  // 改为用坐标i
 *      for j = m ~ a[i] // 倒着!!!循环j计算到a[i]截至
 *         f[j] = max(f[j], f[j-a[i]]+v[i])  // 必须取最大价值v[i]而不是最大体积
 *  
 * 坑 01背包:必须正着循环数组坐标1~n,必须倒着循环目标和m~0
 *    因为每个A[i]只能用一次,所以数组坐标必须在外循环,目标和在内循环且只用算到A[i](即m~A[i])
 */
class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @param V: Given n items with value V[i]
     * @return: The maximum value
     */
    int backPackII(int m, vector<int> &A, vector<int> &V) {
        vector<int> f(m + 1, 0);  // 初始化为0 坑:f(m+1,0) 不是f(n+1,0)!!
        
        for (int i = 0; i < A.size(); ++i) {  // [i]
            for (int j = m; j >= A[i]; --j) {  // 须倒算!! 因为大index的新值要用小index的旧值来算
                f[j] = max(f[j], f[j - A[i]] + V[i]);  // 只max用[i]时的价值,因不用[i]时价值在考虑[i]前后不变 
            }
        }
        return f[m];
    }
};
