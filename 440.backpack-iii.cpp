/*
 * @lc app=lintcode id=440 lang=cpp
 *
 * [440] Backpack III
 *
 * https://www.lintcode.com/problem/backpack-iii/description
 *
 * lintcode
 * Hard (61.00%)
 * Total Accepted:    4463
 * Total Submissions: 7298
 * Testcase Example:  '[2,3,5,7]\n[1,5,2,4]\n10\n'
 *
 * Given `n` kinds of items, and each kind of item has an infinite number
 * available. The `i-th` item has size `A[i]` and value `V[i]`.
 * 
 * Also given a backpack with size `m`. What is the maximum value you can put
 * into the backpack?
 * 
 * @Category DP (01背包 双属性 最值型) 求n物品放入m背包能放物品的最大价值和
 * @Idea
 * S1: DP // T=O(nm) S=O(nm)
 * dp[i]表示任取物品放入容量m的背包可放最大价值和
 * dp[i]=max(dp[i]//不取a[i], v[i]+dp[i-a[j]]|j>=a[i]//取a[i])
 
 * 初始 dp[0]=0
 * for i = 0 ~ n-1  // 物品数组坐标
 *     for j = a[i] ~ m  // 由小到大的目标和
 *         dp[j] = max(dp[j], v[i]+dp[j-a[i]])
 * 返回 dp[m]
 *
 * 坑 计数型初始化一定注意,如此题中dp[0]=1而不是0
 * 坑 完全背包:目标和必须正循环(0~m),数组坐标必须正循环(0~n-1)
 *    计算每个目标和时都可用每个数无限次,故必须外循环目标和,内循环数组坐标且可从A[i]开始(否则要加if(j>=A[i]))
 */
class Solution {
public:
    /**
     * @param A: an integer array
     * @param V: an integer array
     * @param m: An integer
     * @return: an array
     */
    int backPackIII(vector<int> &A, vector<int> &V, int m) {
        vector<int> f(m + 1, 0);  // 坑:f(m+1,0)针对从小到大的背包容量i,而不是f(n+1,0)前i个物品
        // dp[0][i]=0, dp[0][j]=0
        for (int i = 0; i < A.size(); ++i) {  // 坑: 体积存在A[i]而不是V[i] 看清条件
            for (int j = A[i]; j <= m; ++j) {  // 坑: 必须正序!!!因为要用小index的新值来算大index的新值
                f[j] = max(f[j], f[j - A[i]] + V[i]);  // 不选A[i]时=f[j]不占容积不算价值
                                                       // 选A[i]时=A[i]对应的价值+选A[i]之前的最大价值
                                                       //         =V[i]+背包容量为i-A[i]时的最大价值
                                                       // 坑: f[j-A[i]]不是f[i-A[i]],要用背包容量j
            }
        }
        return f[m];
    }
};
