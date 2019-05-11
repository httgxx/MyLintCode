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
 * DP T=O(n*target) S=O(target)
 * dp[i][j]表示从前i个数任意取得到和为j的总方案数
 * dp[i][j] += dp[i-1][j]//不取[i] + dp[i-1][j-nums[i]]//取[i]
 *
 * 初始
 * dp[0][0]=1  // 前0个数构成和0有1种方案
 * dp[0][j]=0  // 前0个数构成和j>0没有方案
 * for i = 1 ~ n-1 // 前i个数
 *     for j = 0 ~ target  // 目标和从小到大
 *         dp[i][j] = dp[i-1][j]  // 不用数[i]
 *         if (j > nums[i]) dp[i][j] += dp[i-1][j-nums[i]] // 用数[i]
 * 返回 dp[n][target]
 *
 * 例子 [1,2,4], target=4  //先算列再算行
 *     last  1      2      4 
 *   target
 *        1  1     
 *        2  
 *        3 
 *        4
 *      ...
 *f[target]  1      2      3      6     11
 *
 * 坑 dp[0]=1而不是0
 * 坑 k=0~n-1是nums数组的坐标
 * 坑 k=0~n-1在外循环i=1~target在内循环,表示第k个为最后1个,构成从小到大和的方案数
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
    int backPackV1(vector<int> &nums, int target) {
        vector<int> dp(target + 1, 0);  // dp[i]表示和为i的总方案数
        dp[0] = 1;
        for (int k = 0; k < nums.size(); ++k) {  // 当前方案最后1个数在nums中index
            for (int i = target; i >= nums[k]; --i) {
                dp[i] += dp[i - nums[k]];  // 枚举所有可以做最后1个数的数字,累加剩余target的方案数
            }
        }
        return dp[target];
    }

    int backPackV(vector<int> &nums, int target) {
        // dp[i][j]表示前i个数中任意取能够成和j的总方案数
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));  // 初始化为0
        dp[0][0] = 1;  // 前0个数构成和0有1种方案
        /*for (int i = 1; i <= n; ++i) { // 前0个数构成和j>0
            dp[i][0] = 1;  // 有0种方案=初始化值0,故可不写
        }*/
        for (int i = 1; i <= n; ++i) {  // 前i个数构成和0
            dp[i][0] = 1;  // 只有1种方案即不用任何数, !=初始化值0,故不能不写,但可以合并到通式中 
        }

        for (int i = 1; i <= n; ++i) {  // 前i个数 注:前0个数已经算过
            for (int j = 1; j <= target; ++j) {  // 目标和j 注:j=0也可以!!!包括了dp[i][0]=1的情况
                dp[i][j] += dp[i - 1][j];  // 不用数[i-1]
                if (j >= nums[i - 1]) dp[i][j] += dp[i - 1][j - nums[i - 1]];  // 用数[i-1] 
            }
        }
        return dp[n][target];
    }
};
