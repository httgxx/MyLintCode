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
 * 
 * dp[i][j][k]表示前i个数里选j个和为k的方案数
 * = 不选a[i-1]=前i-1个里面选j个和为k + 选a[i-1]=前i-1个里面选j-1个和为k-a[i-1]
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
