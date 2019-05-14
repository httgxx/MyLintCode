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
 * @Category DP(01背包 计数型) 求n数和为target的总方案数
 * @Idea
 * DP // T=O(n*target) S=O(target)
 * dp[i]表示和为i的总方案数
 * dp[i] = sum(dp[i-a[k]]|a[k]<=i)
 * 初始 dp[0]=1 // 得到0和的方案必有一个:不取任何一个数
 * for i = 1 ~ target  // 目标和
 *     for j = 0 ~ n-1  // 每次增加和都可用任何数做最后1个,用了可以再用
 *         if (i>=a[j]) dp[i] += dp[i-a[j]]  // 叠加构成当前剩余和的方案数*1
 * 返回 dp[target]
 *
 * 坑 dp[0]=1而不是0
 * 坑 i=1~target 背包限制好确定,放在外循环
 * 坑 j=0~n-1是nums数组的坐标 每个数值可选多次不确定,放在内循环
 * 
 * 例子 [1,2,4], target=4  //先算行再算列  //i>=nums[j]时格子[i,j]=左格子[i-1,j]+上方第i-nums[j]行最右边格子
 *     last  nums[0]=1        [1]=2           [2]=4       f[target]
 *   target
 *        0                                               f[0]=1
 *        1  0+f[0]=1   1<2=>still 1    1<4=>still 1      f[1]=1      
 *        2  0+f[1]=1   1+f[0]=2        2<4=>still 2      f[2]=2         
 *        3  0+f[2]=2   2+f[1]=3        3<4=>still 3      f[3]=3
 *        4  0+f[3]=3   2+f[2]=4        4+f[0]=5          f[4]=5
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
        for (int i = 1; i <= target; ++i) {  // 坑: 在外循环且从1开始
            for (int k = 0; k < nums.size(); ++k) {  // 任何数都可做最后1个
                if (i >= nums[k]) {
                    dp[i] += dp[i - nums[k]];  // 枚举所有可做最后1个数的数,每个数都可以做最后1个
                }
            }
        }
        return dp[target];
    }
};
