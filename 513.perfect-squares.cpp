/*
 * @lc app=lintcode id=513 lang=cpp
 *
 * [513] Perfect Squares
 *
 * https://www.lintcode.com/problem/perfect-squares/description
 *
 * lintcode
 * Medium (38.00%)
 * Total Accepted:    8921
 * Total Submissions: 23406
 * Testcase Example:  '12\n'
 *
 * Given a positive integer `n`, find the least number of perfect square
 * numbers (for example, `1, 4, 9, 16, ...`) which sum to n.
 * Example 1:
 *   Input: 12
 *   Output: 3
 *   Explanation: 4 + 4 + 4
 * Example 2:
 *   Input: 13
 *   Output: 2
 *   Explanation: 4 + 9
 * 
 * @Category DP(划分比较型)
 * @Ideas
 * S1: DP T=O(n*sqrt(n)) S=O(n)
 * dp[i]表示i可以分成的完全平方数的最少个数
 * dp[i]=min(dp[i], dp[i-j^2]+1|1<=j^2<=i)
 * 初始化 dp[0]=0  (所有数字>0,则和为0不可能)
 * 实例:
 * i=1
 *  j=1 dp[1]=min(dp[1]=INT_MAX,dp[1-1=0]+1)=1  //1
 * i=2
 *  j=1 dp[2]=min(dp[2]=INT_MAX,dp[2-1=1]+1)=2  //1,1
 * i=3
 *  j=1 dp[3]=min(dp[3]=INT_MAX,dp[3-1=2]+1)=3  //1,1,1
 * i=4
 *  j=1 dp[4]=min(dp[4]=INT_MAX,dp[4-1=3]+1)=4  //1,1,1,1
 *  j=2 dp[4]=min(dp[4]=4, dp[4-4=0]+1)=1       //2 优于 1,1,1,1
 * i=5
 *  j=1 dp[5]=min(dp[5]=INT_MAX,dp[5-1=4]+1)=2  //2,1
 *  j=2 dp[5]=min(dp[5]=2,dp[5-4=1]+1)=2        //1,2
 * i=6
 *  j=1 dp[6]=min(dp[6]=INT_MAX,dp[6-1=5]+1)= 3 //1,2,1
 *  j=2 dp[6]=min(dp[6]=3,dp[6-4=2]+1)=3        //1,1,2
 * i=7
 *  j=1 dp[7]=min(dp[7]=INT_MAX,dp[7-1=6]+1)= 4 //1,1,2,1
 *  j=2 dp[7]=min(dp[7]=4,dp[7-4=3]+1)=4        //1,1,1,2
 * i=8
 *  j=1 dp[8]=min(dp[8]=INT_MAX,dp[8-1=7]+1)=6  //1,1,1,2,1
 *  j=2 dp[8]=min(dp[8]=6,dp[8-4=4]+1)=2        //2,2 优于 1,1,1,2,1
 * i=9
 *  j=1 dp[9]=min(dp[9]=INT_MAX,dp[9-1=8]+1)=3  //2,2,1
 *  j=2 dp[9]=min(dp[9]=2,dp[9-4=5]+1)=3        //1,2,2
 * i=10
 *  j=1 dp[10]=min(dp[10]=INT_MAX,dp[10-1=9]+1)=4 //1,2,2,1
 *  j=2 dp[10]=min(dp[10]=4,dp[10-4=6]+1)=4       //1,1,2,2
 * 
 * S2: 四平方和定理:每个正整数均可表示为4个整数的平方和??
 * 
 */
class Solution {
public:
    /**
     * @param n: a positive integer
     * @return: An integer
     */
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <=n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i - j * j] + 1, dp[i]);
            }
        }
        return dp.back();  // dp[n]
    }

    int numSquares1(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i <= n; ++i) {  // 坑:必须从i=0,j=1开始
            for (int j = 1; i + j * j <= n; ++j) {
                dp[i + j * j] = min(dp[i + j * j], dp[i] + 1);
            }
        }
        return dp.back();
    }
    
    int numSquares2(int n) {
        while (n % 4 == 0) n /= 4;
        if (n % 8 == 7) return 4;
        for (int a = 0; a * a <= n; ++a) {
            int b = sqrt(n - a * a);
            if (a * a + b * b == n) {
                return !!a + !!b;
            }
        }
        return 3;
    }
};
