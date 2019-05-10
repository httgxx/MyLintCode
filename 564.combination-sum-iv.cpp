/*
 * @lc app=lintcode id=564 lang=cpp
 *
 * [564] Combination Sum IV
 *
 * https://www.lintcode.com/problem/combination-sum-iv/description
 *
 * lintcode
 * Medium (37.00%)
 * Total Accepted:    5665
 * Total Submissions: 14917
 * Testcase Example:  '[1,2,4]\n4\n'
 *
 * Given an integer array `nums` with all positive numbers and no duplicates,
 * find the number of possible combinations that add up to a positive integer
 * `target`.
 * Example1
 *   Input: nums = [1, 2, 4], and target = 4
 *   Output: 6
 *   Explanation:
 *   The possible combination ways are:
 *   [1, 1, 1, 1]
 *   [1, 1, 2]
 *   [1, 2, 1]
 *   [2, 1, 1]
 *   [2, 2]
 *   [4]
 * Example2
 *   Input: nums = [1, 2], and target = 4
 *   Output: 5
 *   Explanation:
 *   The possible combination ways are:
 *   [1, 1, 1, 1]
 *   [1, 1, 2]
 *   [1, 2, 1]
 *   [2, 1, 1]
 *   [2, 2]
 * 
 * @Category DP(01背包 计数型:每物可选无限次,重复数字不同顺序算不同方案,求填满背包的总方案数)
 * @Idea
 * DP T=O(n*target) S=O(target)
 * dp[i]表示和为i的总方案数
 * dp[i] = sum(dp[i-v[k]]|k=0~n-1且v[k]<=i) 须i正序！！
 * 
 * 初始 dp[0]=1 
 * for i = 1 ~ target  // 从1开始
 *     for k = 0 ~ n-1  // k为nums中的坐标
 *         if (i>=nums[i]) dp[i] += dp[i-nums[k]]
 * 返回 dp[target]
 * 
 * 坑 dp[0]=1而不是0
 * 坑 k=0~n-1是nums数组的坐标
 * 坑 i=1~target从1开始而不是nums[k],why???
 * 坑 i=1~targetz在外循环,k=0~n-1在内循环,why???
 * 坑 i=nums[k]~target必须正着循环！！！// 因为要用小index的新值计算大index的新值
 * 
 * 背包问题参考网上资料: https://www.kancloud.cn/kancloud/pack/70125
 */
class Solution {
public:
    /**
     * @param nums: an integer array and all positive numbers, no duplicates
     * @param target: An integer
     * @return: An integer
     */
    int backPackVI(vector<int> &nums, int target) {
        vector<int> dp(target + 1, 0);  // dp[i]表示和为i的总方案数
        dp[0] = 1;
        for (int i = 1; i <= target; ++i) {  // 坑: 目标和i正循环才能用小index的新值更新大index的值
                                                 // 坑: 必须从1开始而不是从nums[k]开始
            for (int k = 0; k < nums.size(); ++k) {  // 当前方案最后1个数在nums中index
                if (i >= nums[k]) {
                    dp[i] += dp[i - nums[k]];  // 枚举所有可以做最后1个数的数字,累加剩余target的方案数
                }
            }
        }
        return dp[target];
    }
};
