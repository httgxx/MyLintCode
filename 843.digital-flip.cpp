/*
 * @lc app=lintcode id=843 lang=cpp
 *
 * [843] Digital Flip
 *
 * https://www.lintcode.com/problem/digital-flip/description
 *
 * lintcode
 * Medium (49.00%)
 * Total Accepted:    1402
 * Total Submissions: 2837
 * Testcase Example:  '[1,0,0,1,1,1]'
 *
 * Given an array of `01`. You can flip `1` to be `0` or flip `0` to be `1`. 
 * Find the minimum number of flipping steps so that the array meets the
 * following rules: 
 * The back of `1` can be either` 1` or `0`, but` 0` must be followed by `0`.
 * 
 * @Category DP
 * @Ideas
 * DP // T=O(n) S=O(n)->滚动数组优化到O(1)
 * dp[i][0]=第i位成为0的情况下使前i位满足条件所需的最小翻转次数
 * dp[i][1]=第i位成为1的情况下使前i位满足条件所需的最小翻转次数
 * 如果第i位([i-1])成为1则第i-1位不能成为0
 * dp[i][j]=min{dp[i-1][k]|jk!=01 + 1|[i-1]!=j即第i位需要翻转1次}
 * 初始 dp[0][0]=dp[0][1]=0
 * 顺序 i=0~n-1 j=0~1
 * 返回 min(dp[n][0],dp[n][1])
 */
class Solution {
public:
    /**
     * @param nums: the array
     * @return: the minimum times to flip digit
     */
    int flipDigit(const vector<int> &nums) {
        int n = nums.size();
        if (n <= 1) { return 0; }  // 特列
        vector<vector<int> >dp(n + 1, vector<int>(2, INT_MAX));  // n+1
        dp[0][0] = dp[0][1] = 0;  // 初始化
        for (int i = 1; i <= n; ++i) {  // 坑:前i位指i=1~n
            for (int j = 0; j < 2; ++j) {  // 第i位[i-1]不同情况
                for (int k = 0; k < 2; ++k) {  // 第i-1位[i-2]不同情况
                    if (k == 0 && j == 1) { continue; }  // 跳过非法情况
                    dp[i][j] = min(dp[i][j],
                        dp[i - 1][k] + (nums[i - 1] != j ? 1 : 0));  // 坑:括号
                }
            }
        }
        return min(dp[n][0], dp[n][1]);
    }
};
