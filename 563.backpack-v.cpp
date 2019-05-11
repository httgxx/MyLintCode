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
 * @Category DP(01背包 计数型:每物可选1次,重复数字不同顺序算不同方案(排列而非组合),求填满背包的总方案数)
 * 注!! 每物可用1次时,先循环物坐标j=0~n-1,再循环和i=1~target 因为每物只有取和不取两种情况,情况确定的(j)放外循环
 * @Idea
 * S0: DP // T=O(n*target) S=O(n*target)
 * dp[i][j]表示从前i个数任意取得到和为j的总方案数
 * dp[i][j] += dp[i-1][j]//不取[i] + dp[i-1][j-nums[i]]//取[i]
 *
 * 初始
 * dp[i][j] = 0
 * dp[0][0] = 1  // 前0个数构成和0有1种方案
 * dp[0][j>0] = 0  // 前0个数构成和j>0没有方案, =初始值0,故可以不写
 * for i = 1 ~ n // 前i个数
 *     for j = 0 ~ target  // 目标和从小到大 从0开始(这样解法也适合数组中不是所有都正整数的题目)
 *         dp[i][j] = dp[i-1][j]  // 不用数[i-1]
 *         if (j >= nums[i-1]) dp[i][j] += dp[i-1][j-nums[i-1]] // 用数[i-1]
 * 返回 dp[n][target]
 *
 * 例子 [1,2,4], target=4  // 先算行再算列: 当前格子[i,j]=上方格子[i-1,j]+某左上方格子[i-1,j-a[i]]
 *   target  0             1              2             3             4             5 ...
 *   前i个数
 *        0  1             0              0             0             0             0
 *    [0]=1  1 0+[0,1-1=0]=1  0+[0,2-1=1]=0 0+[0,3-1=2]=0 0+[0,4-1=3]=0 0+[0,5-1=4]=0
 *    [1]=2  1 1<2 =>still 1  0+[1,2-2=0]=1 0+[1,3-2=1]=1 0+[1,4-2=2]=0 0+[1,5-2=3]=0
 *    [2]=4  1 1<4 =>still 1  2<4 =>still 1 3<4 =>still 1 0+[2,4-4=0]=1 0+[2,5-4=1]=1  
 *
 * 坑 dp[i][0]=1而不是0 dp[0][j>0]=0而不是1
 * 坑 i=1~n 前i个数,最后1个数是nums[i-1], 循环从1开始而不用从0开始因为dp[0][j]已经算过
 * 坑 j=0~target 从0开始适合数组中不都是正整数的题目,若都正整数则可以先初始化i=1~n:dp[i][j]=1
 * 坑 i=1~n在外循环而i=0~target在内循环,因为每数只用1次所以前i个确定,确定的情况放外循环
 * 坑 for j=0~target: 
 *        dp[i][j] = dp[i-1][j] // 不是 +=
 *        if (j>=nums[i-1]) dp[i][j] += dp[i-1][j-nums[i-1]]   // 不是=,不是nums[i]
 * 
 * 背包问题参考网上资料: https://www.kancloud.cn/kancloud/pack/70125
 */
class Solution {
public:
    /**
     * @param nums: an integer array and all positive numbers
     * @param target: An integer
     * @return: An integer
     */
    int backPackV0(vector<int> &nums, int target) {
        // dp[i][j]表示前i个数中任意取能够成和j的总方案数
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));  // 初始化为0
        dp[0][0] = 1;  // 前0个数构成和0有1种方案
        /*for (int i = 1; i <= n; ++i) { // 前0个数构成和j>0
            dp[i][0] = 0;  // 有0种方案=初始化值0,故可不写
        }*/
        for (int i = 1; i <= n; ++i) {  // 前i个数构成和0
            dp[i][0] = 1;  // 只有1种方案即不用任何数, !=初始化值0,故不能不写,但可以合并到通式中 
        }

        for (int i = 1; i <= n; ++i) {  // 前i个数 注:前0个数已经算过
            for (int j = 1; j <= target; ++j) {  // 目标和j 注:j=0也可以!!!包括了dp[i][0]=1的情况
                dp[i][j] = dp[i - 1][j];  // 不用数[i-1]
                if (j >= nums[i - 1]) dp[i][j] += dp[i - 1][j - nums[i - 1]];  // 用数[i-1] 
            }
        }
        return dp[n][target];
    }

    // 降维 
    // dp[i][j] += dp[i-1][j] + j>=nums[i-1] ? dp[i-1][j-nums[i-1]] : 0
    // [i][j]只跟[i-1][j]和[i-1][j-nums[i-1]]相关,可降低1维
    // 大index的新值 += 大index的旧值 + 小index的旧值 => 必须先算大index的新值再算小index的新值
    // => for i = 1 ~ n  // 前i个数
    //        for j = target ~ 0 // 倒着循环j计算
    //           f[j] += j>=nums[i-1] ? f[j-nums[i-1]] : 0 
    // => for i = 0 ~ n - 1  // 改为用坐标i
    //        for j = target ~ nums[i] // 倒着循环j计算到nums[i]截至
    //           f[j] += f[j-nums[i-1]] 
    int backPackV(vector<int> &nums, int target) {
        // f[j]表示任意取数字能够成和j的总方案数
        int n = nums.size();
        vector<int> f(target + 1, 0);  // 初始化为0
        f[0] = 1;  // 任何取正整数构成和0只有1种方案

        for (int i = 0; i < n; ++i) {  // 数[i]
            for (int j = target; j >= nums[i]; --j) {  // 须倒算!! 因为大index的新值要用小index的旧值来算
                f[j] += f[j - nums[i]];  // 只+=用数[i]时的方案数,因为不用数[i]时方案数在考虑数[i]前后不变 
            }
        }
        return f[target];
    }

};
