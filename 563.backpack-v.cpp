/*
 * @lc app=lintcode id=563 lang=cpp
 *
 * [563] Backpack V
 *
 * https://www.lintcode.com/problem/backpack-v/description
 *
 * lintcode
 * Medium (51.00%)
 * Total Accepted:    3633
 * Total Submissions: 7078
 * Testcase Example:  '[1,2,3,3,7]\n7\n'
 *
 * Given n items with size `nums[i]` which an integer array and all positive
 * numbers. An integer `target` denotes the size of a backpack. Find the number
 * of possible fill the backpack.
 * 
 * `Each item may only be used once`
 * 
 * Example
 * Given candidate items [1,2,3,3,7] and target 7,
 * A solution set is: 
 * [7]
 * [1, 3, 3]
 * return 2
 * 
 * @Category DP(01背包 计数型:每物可选1次,重复数字不同顺序算不同方案,求填满背包的总方案数)
 * @Idea
 * DP T=O(n*target) S=O(target)
 * dp[i]表示和为i的总方案数
 * dp[i] = sum(dp[i-v[k]]|k=0~n-1且v[k]<=i) 须i倒序！！
 * 
 * 初始 dp[0]=1 
 * for k = 1 ~ n-1  // 从1开始
 *     for i = target ~ nums[k]  // 到nums[k]结束
 *         dp[i] += dp[i-nums[k]]
 * 返回 dp[target]
 * 
 * 坑 dp[0]=1而不是1
 * 坑 k=1~n-1 从1开始
 * 坑 k=1~n-1在外循环, i=target~nums[k]在内循环, 这样可以直接结束于nums[k]因为其中k已在外循环已知
 * 坑 i=target~nums[k]必须倒着循环！！！// 因为要用小index的旧值计算大index的新值
 * 
 * 参考网友: https://www.kancloud.cn/kancloud/pack/70125
 */
class Solution {
public:
    /**
     * @param nums: an integer array and all positive numbers
     * @param target: An integer
     * @return: An integer
     */
    int backPackV(vector<int> &nums, int target) {
        vector<int> dp(target + 1, 0);  // size=target+1
        dp[0] = 1;
        for (int k = 0; k < nums.size(); ++k) {  // 当前方案最后1个数在nums中index
            for (int i = target; i >= nums[k]; --i) {  // 坑: 目标和i倒循环才能用index小的旧值更新index大的值
                                                       // 坑: 目标和i放在内循环,可直接在i<nums[k]时结束循环
                dp[i] += dp[i - nums[k]];  // 枚举所有可以做最后1个数的数字,累加剩余target的方案数
            }
        }
        return dp[target];
    }
};
