/*
 * @lc app=lintcode id=116 lang=cpp
 *
 * [116] Jump Game
 *
 * https://www.lintcode.com/problem/jump-game/description
 *
 * lintcode
 * Medium (39.00%)
 * Total Accepted:    24955
 * Total Submissions: 62868
 * Testcase Example:  '[0,8,2,0,9]'
 *
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.
 * Each element in the array represents your maximum jump length at that
 * position. 
 * 
 * Determine if you are able to reach the last index.
 *
 * @Category DP
 * @Ideas
 *
 */
class Solution {
public:
    /**
     * @param A: A list of integers
     * @return: A boolean
     */
    bool canJump(const vector<int> &A) {
        vector<int> dp(A.size(), 0);
        for (int i = 1; i < A.size(); ++i) {
            dp[i] = max(dp[i - 1], A[i - 1]) - 1;
            if (dp[i] < 0) return false;
        }
        return true;
    }
};
