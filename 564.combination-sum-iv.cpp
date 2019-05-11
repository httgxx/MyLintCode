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
 * @Category DP(01背包 计数型:每物可选无限次,重复数字不同顺序算不同方案(排列而非组合),求填满背包的总方案数)
 * 注!! 每物可用无限次时,先循环和i=1~target,再循环物坐标j=0~n-1,因为求每种和时每物都可用,情况确定的(和)放外循环
 * @Idea
 * DP // T=O(n*target) S=O(target)
 * dp[i]表示和为i的总方案数
 * dp[i] = sum(dp[i-nums[k]]|k=0~n-1且nums[k]<=i) 须i正序循环,因为用小index的新值算大index的新值
 * 
 * 初始 dp[0]=1 
 * for i = 1 ~ target  // 从1开始
 *     for k = 0 ~ n-1  // 每次都可用任何数做最后1个,用了可以再用
 *         if (i>=nums[i]) dp[i] += dp[i-nums[k]]  // 叠加构成当前剩余和的方案数*1
 * 返回 dp[target]
 * 
 * 例子 [1,2,4], target=4  //先算列再算行
 *   target  1      2      3      4      5 ...
 *     last
 *        1  1 f[1]=1 f[2]=2 f[3]=3 f[4]=6       
 *        2  0 f[0]=1 f[1]=1 f[2]=2 f[3]=3
 *        4  0      0      0 f[0]=1 f[2]=2
 *f[target]  1      2      3      6     11
 * 
 * 坑 dp[0]=1而不是0
 * 坑 k=0~n-1是nums数组的坐标
 * 坑 i=1~target在外循环k=0~n-1在内循环好理解, 表示要构成从小到大的和,每个数字都试作为最后1个(BFS)
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
