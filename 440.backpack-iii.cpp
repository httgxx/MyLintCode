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
        /*vector<int> f(m + 1, 0);  // 初始化为0 坑:f(m+1,0) 不是f(n+1,0)!!
        
        for (int i = 0; i < A.size(); ++i) {  // [i] 坑: 体积存在A[i]而不是V[i]!!!
            for (int j = A[i]; j <= m; ++j) {  // 须倒算!! 因为大index的新值要用小index的新值来算
                f[j] = max(f[j], f[i - A[i]] + V[i]);  // 只max用[j]时的价值,因不用[j]时价值在考虑[j]前后不变 
            }
        }*/
        int n = A.size();
        vector<int> f(m + 1);
        for (int i = 0; i < n; ++i)
            for (int j = A[i]; j <= m; ++j)
                f[j] = max(f[j], f[j - A[i]] + V[i]);
        return f[m];
    }
};
