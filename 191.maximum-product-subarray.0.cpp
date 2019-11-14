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
 * Example 1:
 * Input:[2,3,-2,4]
 * Output:6
 * 
 * Example 2:
 * Input:[-1,2,4,1]
 * Output:8
 * 
 * @Category DP min max
 * @Idea 动规 min[n] max[n] T=O(n) S=O(n)
 * f[k]表示a[0~i]对应的最大连续子串乘积
 * g[k]表示a[0~i]对应的最小连续子串乘积
 * for k=0~n-1
 *   f[k]=max(f[k-1]*a[k], a[k], g[k-1]*a[k])
 *   g[k]=min(g[k-1]*a[k], a[k], f[k-1]*a[k])
 *   res=max(res, f[k])
 * => 
 * 空间优化
 * res = mx = mn = a[0]
 * for k=0~n-1
 *   tmx=mx, tmn=mn;
 *   mx=max(tmx*a[k], a[k], tmn*a[k])
 *   mn=min(tmn*a[k], a[k], tmx*a[k])
 *   res=max(res, mx)
 * => 
 * 逻辑优化
 * res = mx = mn = a[0]
 * for k=0~n-1
 *   if (a[k]<0) swap(mx, mn)
 *   mx=max(mx*a[k], a[k])
 *   mn=min(mn*a[k], a[k])
 *   res=max(res, mx)
 */
class Solution {
public:
    /**
     * @param nums: An array of integers
     * @return: An integer
     */
    // DP + 2 arrays mn mx //T=O(n) S=O(n)
    // k=0~n-1
    //   if(a[k]<0) swap(mx, mn)
    //   mx=min(mx*a[k], a[k])
    //   mn=max(mn*a[k], a[k])
    //   res=max(res,mx)
    int maxProduct(vector<int> &nums) {
        if (nums.empty()) { return 0; }         // 处理特例:空串
        int res = nums[0], mx = res, mn = res;  // 初始化max和min
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < 0) { swap(mx, mn); }  // 若新数为负数,则交换全局最大和全局最小值
            mx = max(nums[i], mx * nums[i]);    // 更新max和min
            mn = min(nums[i], mn * nums[i]);
            res = max(res, mx);                 // 更新全局max
        }
        return res;
    }
};
