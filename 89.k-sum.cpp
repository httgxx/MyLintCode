/*
 * @lc app=lintcode id=89 lang=cpp
 *
 * [89] k Sum
 *
 * https://www.lintcode.com/problem/k-sum/description
 *
 * lintcode
 * Hard (28.00%)
 * Total Accepted:    11262
 * Total Submissions: 38882
 * Testcase Example:  '[1,2,3,4]\n2\n5'
 *
 * Given n distinct positive integers, integer k (k <= n) and a number target.
 * Find k numbers where sum is target. Calculate how many solutions there are?
 * Example 1
 * Input:
 * List = [1,2,3,4]
 * k = 2
 * target = 5
 * Output: 2
 * Explanation: 1 + 4 = 2 + 3 = 5
 * 
 * @Category DP (01背包 单属性) 求n数和为target的总方案数 + 取数个数有限制 => 增加1维
 * @Idea
 * S0: DP //T=O(n*k*target) S=O(n*k*target)
 * dp[i][j][t]表示前i个数里选j个和为t的方案数
 * dp[i][j][t] =
 *   dp[i-1][j][t] //不选a[i-1]则前i-1个里面选j个和为k
 *   + if(t >= f[i-1][j-1][t-A[i-1]] //选a[i-1]则前i-1个里面选j-1个和为k-a[i-1]
 * 初始
 * dp[i][0][0]=1 其余全=0
 * // i=0时无数可选=>只有在j=t=0时f=1,其余f=0
 * // j=0时选0个数=>只有在t=0时f=1,其余f=0
 * // t=0时和为0=>只有在j=0时f=1,其余f=0
 * 顺序
 * for i=1~n  //前i个数
 *    for j=1~min(i,k) //选j个
 *       for t=1~taregt //目标和t
 *          f[i][j][t] = f[i - 1][j][t];  // 不选a[i-1]
 *          if (t>=A[i-1]) f[i][j][t] += f[i-1][j-1][t-A[i-1]];  // 选a[i-1]
 * 返回
 * dp[n][k][target]
 * 
 * 坑 初始化 dp[i][0][0]=1 其余全=0
 * 
 * S1: DP 降维 //T=O(n*k*target) S=O(k*target) 
 * 初始
 * dp[i][0][0]=1 其余全=0
 * int cur = 1, old = 0;
 * for i=1~n  //前i个数
 *    for j=1~min(i,k) //选j个
 *       for t=1~taregt //目标和t
 *          f[i][j][t] = f[i - 1][j][t];  // 不选a[i-1]
 *          if (t>=A[i-1]) f[i][j][t] += f[i-1][j-1][t-A[i-1]];  // 选a[i-1]
 *    old = cur;
 *    cur = 1 - cur;
 * return f[old][k][target]
 * 
 * 坑: 返回f[old][k][target]而不是f[n][k][target]!!!!
 */
class Solution {
public:
    /**
     * @param A: An integer array
     * @param k: A positive integer (k <= length(A))
     * @param target: An integer
     * @return: An integera
     */
    int kSum0(vector<int> &A, int k, int target) {
        int n = A.size();
        vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(k + 1, vector<int>(target + 1, 0)));
        for (int i = 0; i < n + 1; i++) {
            f[i][0][0] = 1;  // i=0时无数可选=>只有在j=t=0时f=1,其余f=0
                             // j=0时选0个数=>只有在t=0时f=1,其余f=0
                             // t=0时和为0=>只有在j=0时f=1,其余f=0
        }
        for (int i = 1; i <= n; i++) {  // 前i个数里选
            for (int j = 1; j <= k && j <= i; j++) {  // 第j个选出的数字
                for (int t = 1; t <= target; t++) {  // 组成和t
                    f[i][j][t] = f[i - 1][j][t];  // 不选a[i-1]
                    if (t >= A[i - 1]) {
                        f[i][j][t] += f[i - 1][j - 1][t - A[i - 1]];  // 选a[i-1]
                    }
                } // for t
            } // for j
        } // for i
        return f[n][k][target];
    }

    // 降维
    int kSum(vector<int> &A, int k, int target) {
        int n = A.size();
        vector<vector<vector<int>>> f(2, vector<vector<int>>(k + 1, vector<int>(target + 1, 0)));
        for (int i = 0; i < 2; i++) {
            f[i][0][0] = 1;  // i=0时无数可选=>只有在j=t=0时f=1,其余f=0
                             // j=0时选0个数=>只有在t=0时f=1,其余f=0
                             // t=0时和为0=>只有在j=0时f=1,其余f=0
        }
        
        int cur = 1, old = 0;
        for (int i = 1; i <= n; i++) {  // 前i个数里选
            for (int j = 1; j <= k && j <= i; j++) {  // 第j个选出的数字
                for (int t = 1; t <= target; t++) {  // 组成和t
                    f[cur][j][t] = f[old][j][t];  // 不选a[i-1]
                    if (t >= A[i - 1]) {
                        f[cur][j][t] += f[old][j - 1][t - A[i - 1]];  // 选a[i-1]
                    }
                } // for t
            } // for j
            old = cur;
            cur = 1 - cur; 
        } // for i
        return f[old][k][target];  // 坑: 不是f[n][k][target]而是f[old][k][target]
    }
};
