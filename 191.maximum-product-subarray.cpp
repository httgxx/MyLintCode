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
 *  f[i]表示以[i]为结尾的子串的最大乘积
 *  g[i]表示以[i]为结尾的子串的最小乘积
 *  [i]>0则乘以f[i-1]更大,[i]<0则乘以g[i-1]更大,[i]也参加比较因可能前极值>0但<1
 *  f[i]=max(a[i], max{a[i-1]*f[i-1],a[i]*g[i-1]}|i>=1)
 *  g[i]=min(a[i], min{a[i-1]*f[i-1],a[i]*g[i-1]}|i>=1) 
 *  初始 f[0]=g[0]=a[0]
 *  返回 f[0]~f[n-1]中的最大值 即m=max(m,f[i]) for i=0~n-1
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
            f.push_back(max(nums[i], max(f[i - 1] * nums[i], g[i - 1] * nums[i])));
            g.push_back(min(nums[i], min(f[i - 1] * nums[i], g[i - 1] * nums[i])));
            m = max(m, f[i]);
        }
        return m;
    }
};
