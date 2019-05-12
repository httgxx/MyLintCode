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
                                               // 坑: 体积存在A[i]而不是V[i]!!!
                f[j] = max(f[j], f[j - A[i]] + V[i]);  // 只max用[i]时的价值,因不用[i]时价值在考虑[i]前后不变 
            }
        }
        return f[m];
    }
};
