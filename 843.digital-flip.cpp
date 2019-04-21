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
 * @Category DP(按情况选择比较型)
 * @Ideas
 * DP // T=O(n) S=O(n)->滚动数组优化到O(1)
 * dp[i][0]=第i位成为0的情况下使前i位满足条件所需的最小翻转次数
 * dp[i][1]=第i位成为1的情况下使前i位满足条件所需的最小翻转次数
 * 规则 如果第i位([i-1])成为1则第i-1位不能成为0
 * dp[i][j]=min{dp[i-1][k]|jk不组成01 + 1|[i-1]!=j即第i位需要翻转1次}
 * 初始 dp[0][0]=dp[0][1]=0
 * 顺序 i=0~n-1 j=0~1
 * 返回 min(dp[n][0],dp[n][1])
 * 坑 前i位则i=1~n而不是0~n-1
 * 坑 ?:最好加括号否则很容易优先级错误
 * 坑 最后返回min(dp[n][0],dp[n][1])
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
        for (int i = 1; i <= n; ++i) {  // 坑:前i位指第i-1位[i-1]
            for (int j = 0; j <= 1; ++j) {  // 当前位[i]的可能值(0,1)
                // 对每种前1位的可能值(0,1)查看能否找到更小的翻转次数
                for (int k = 0; k <= 1; ++k) {  // 前1位[i-1]的可能值(0,1)
                    if (k == 0 && j == 1) { continue; }  // 跳过非法情况
                    dp[i][j] = min(dp[i][j],
                        dp[i - 1][k] + (nums[i - 1] != j ? 1 : 0));  // 坑:括号
                        // 前i位=第i-1位=nums[i-1] 若不是j则需要额外翻转1次
                }
            }
        }
        return min(dp[n][0], dp[n][1]);
    }
};
