/*
 * @lc app=lintcode id=168 lang=cpp
 *
 * [168] Burst Balloons
 *
 * https://www.lintcode.com/problem/burst-balloons/description
 *
 * lintcode
 * Hard (39.00%)
 * Total Accepted:    4864
 * Total Submissions: 12101
 * Testcase Example:  '[4,1,5,10]\n'
 *
 * Given `n` balloons, indexed from `0` to `n-1`. Each balloon is painted with
 * a number on it represented by array `nums`. You are asked to burst all the
 * balloons. If the you burst balloon `i` you will get `nums[left] * nums[i] *
 * nums[right]` coins. Here left and right are adjacent indices of i. After the
 * burst, the left and right then becomes adjacent.
 * 
 * Find the `maximum` coins you can collect by bursting the balloons wisely.
 * 
 * Example 1:
 * Input：[4, 1, 5, 10]
 * Output：270
 * Explanation：
 * nums = [4, 1, 5, 10] burst 1, get coins 4 * 1 * 5 = 20
 * nums = [4, 5, 10]   burst 5, get coins 4 * 5 * 10 = 200 
 * nums = [4, 10]    burst 4, get coins 1 * 4 * 10 = 40
 * nums = [10]    burst 10, get coins 1 * 10 * 1 = 10
 * Total coins 20 + 200 + 40 + 10 = 270
 * 
 * Example 2:
 * Input：[3,1,5]
 * Output：35
 * Explanation：
 * nums = [3, 1, 5] burst 1, get coins 3 * 1 * 5 = 15
 * nums = [3, 5] burst 3, get coins 1 * 3 * 5 = 15
 * nums = [5] burst 5, get coins 1 * 5 * 1 = 5
 * Total coins 15 + 15 + 5  = 35
 * 
 * @Category DP
 * @Idea DP 
 * 因为计算打爆气球的价值得看留下的左右气球,所以连接左右两端预留价值为1的dummy气球方便计算边界条件.
 * 枚举那段气球被曝,再枚举这段气球最后被爆的气球.
 * dp[i][j]表示只打爆区间[i,j]所有气球(包括[i]和[j],保留[0,i-1],[j+1,n-1])时能获得的最大收益
 * = max(dp[i][n], dp[i][k-1]+score+dp[k+1][j]))且score=A[i]*A[k]*A[j],i<=k<=j 
 * T=O(n^3) S=O(n^2)
 */
class Solution {
public:
    /**
     * @param nums: A list of integer
     * @return: An integer, maximum coins
     */
    // DP
    // dp[i][j]表示只打爆区间[i,j]所有气球(包括[i]和[j],保留[0,i-1],[j+1,n-1])时能获得的最大收益
    // = max(dp[i][n], dp[i][k-1]+score+dp[k+1][j]))且score=A[i]*A[k]*A[j],i<=k<=j   
    // T=O(n^3) S=O(n^2)
    int maxCoins(vector<int> &nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);                                       // 原数组两端加收益1的dummy气球,[4,3]=>[1,4,3,1]
        nums.push_back(1);                                                  // 加上是为了方便处理边界条件.注意加后长度+=2
        vector<vector<int> > dp(nums.size(), vector<int>(nums.size() , 0)); // dp[n+2][n+2]
        for (int len = 1; len <= n; ++len) {                                // 枚举区间长度=1~n个气球
            for (int left = 1; left <= n - len + 1; ++left) {               // 枚举区间左边界位置=>右边界位置=左边界位置+len-1
                int right = left + len - 1;                                 // dp[i][j]表示打爆[i,j]所有气球后的最大收益
                for (int k = left; k <= right; ++k) {                       // 枚举区间中最后1个被打爆的气球位置k
                    dp[left][right] = max(dp[left][right],                  // 用新值更新最大值
                        nums[left - 1] * nums[k] * nums[right + 1] +        // 最后1个被打爆的气球增加的价值
                        dp[left][k - 1] + dp[k + 1][right]);                // +打爆气球k后剩下的两段各自能的最大收益
                }
            }
        }
        return dp[1][n];                                                    // 坑:[0]和[n+1]都是dummy气球所以不用打爆
    }
};
