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
 * S1: T=O(n) S=O(n)
 * dp[i]表示到达位置i时可再跳的最大步数 
 * = max(前1位置可再跳的最大步数dp[i-1],前1位置的弹跳力n[i-1])-1//从前1跳到当前
 * = max(dp[i-1],n[i-1])-1
 * 初始 dp[0]=n[0]
 * 返回 只要有一个0~n-1间的k有dp[k]<0则不能跳到终点即返回false,否则返回true
 * 
 * S2: T=O(n^2) S=O(n)
 * dp[i]表示能否跳到位置i(true/false)
 * = 前面有某位置k可以跳到当前位置
 * = if exist 0<k<i: dp[k]==true && k+n[k]>=i
 * 初始 dp[0]=true
 * 返回 dp[n-1]
 */
class Solution {
public:
    /**
     * @param A: A list of integers
     * @return: A boolean
     */
    bool canJump(const vector<int> &A) {  // T=O(n)
        vector<int> dp(A.size(), 0);
        for (int i = 1; i < A.size(); ++i) {
            dp[i] = max(dp[i - 1], A[i - 1]) - 1;
            if (dp[i] < 0) return false;
        }
        return true;
    }
};
