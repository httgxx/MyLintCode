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
 *  S0: DP T=O(n) S=O(n)
 *  f[i],g[i]分别表示以[i]为结尾的子串的最大，最小乘积
 *  [i]>0则乘以f[i-1]更大,[i]<0则乘以g[i-1]更大,[i]也参加比较因可能前极值>0但<1
 *  f[i]=max(f[i-1]*a[i], a[i], g[i-1]*a[i])
 *  g[i]=min(g[i-1]*a[i], a[i], f[i-1]*a[i]) 
 *  初始 f[0]=g[0]=a[0]
 *  返回 f[0]~f[n-1]中的最大值 即m=max(m,f[i]) for i=0~n-1
 * 
 *  S1: DP+空间优化
 *  只用2个变量而不是2个数组来存当前位置的最大和最小值,算下个位置前更新这2变量
 *  res = curMax = curMin = a[0]
 *  for(i=1~n-1)
 *      mx=curMax, mn=curMin
 *      curMax= max (mx*a[i], a[i], mn*a[i])
 *      curMin= min (mn*a[i], a[i], mx*a[i])
 *      res=max(res, curMax)
 *  return res
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
