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
 * @Category DP(01背包 单属性 计数型) 求n数和为target的总方案数
 * @Idea
 * DP // T=O(n*target) S=O(target)
 * dp[i]表示和为i的总方案数
 * dp[i] = sum(dp[i-a[k]]|a[k]<=i)
 * 初始 dp[0]=1 // 得到0和的方案必有一个:不取任何一个数
 * for i = 1 ~ target  // 目标和i = 最后一个选的数+剩下目标和的方案数(之前已经算过)
 *     for j = 0 ~ n-1  // 最后一次选数a[j] // 正序倒序无所谓???
 *         if (i>=a[j]) dp[i] += dp[i-a[j]]  // +=选剩下的目标和的方案数
 * 返回 dp[target]
 *
 * 坑 计数型初始化一定注意,如此题中dp[0]=1而不是0
 * 坑 计数型是+=而不是=
 * 坑 完全背包:目标和正循环(1~m),数组坐标必须正循环(0~n-1)
 *    每个数在计算每个目标和时都可用无限次,故必须外循环数组坐标,内循环目标和且可从A[i]开始(否则要加if(j>=A[i]))
 * 
 * 例子 [1,2,4], target=4  //先算行再算列  //i>=nums[j]时格子[i]+=某左(第i-a[j]个)格子
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
        for (int j = 1; j <= target; ++j) {  // 目标和i
            for (int i = 0; i < nums.size(); ++i) {  // 数[j]
                if (j >= nums[i]) dp[j] += dp[j - nums[i]];  // 枚举每个数做最后1个的情况,叠加方案数
            }
        }
        return dp[target];
    }
};
