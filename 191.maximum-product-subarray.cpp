/*
 * @lc app=lintcode id=191 lang=cpp
 *
 * [191] Maximum Product Subarray
 *
 * https://www.lintcode.com/problem/maximum-product-subarray/description
 *
 * lintcode
 * Medium (32.00%)
 * Total Accepted:    14236
 * Total Submissions: 44424
 * Testcase Example:  '[-1]\n'
 *
 * Find the contiguous subarray within an array (containing at least one
 * number) which has the largest product.
 *
 * @Category DP,DFS+Memo
 * @Ideas
 *  A[i]可正可负,若为正则应该乘以上一步的最大值,若为负则应该乘以上一步的最小值，所以必须记录每一步的最大值f(i)和最小值g(i)
 *  maxV[i] = max(i=1~n-1 | maxV[i-1]*A[i], minV[i-1]*A[i], A[i])
 *  minV[i] = min(i=1~n-1 | maxV[i-1]*A[i], minV[i-1]*A[i], A[i])
 *  init： f[0]=A[0], g[0]=A[0]
 *  从左往右更新 返回max(i=0~n-1|f[i])
 */
class Solution {
public:
    /**
     * @param nums: An array of integers
     * @return: An integer
     */
    int maxProduct(vector<int> &nums) {
        vector<int> f = { nums[0] };
        vector<int> g = { nums[0] };
        int m = f[0];
        for (int i = 1; i < nums.size(); ++i) {
            f.push_back(max(max(f[i - 1] * nums[i], g[i - 1] * nums[i]), nums[i]));
            g.push_back(min(min(f[i - 1] * nums[i], g[i - 1] * nums[i]), nums[i]));
            m = max(m, f[i]);
        }
        return m;
    }
};
