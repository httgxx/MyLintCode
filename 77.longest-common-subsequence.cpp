/*
 * @lc app=lintcode id=77 lang=cpp
 *
 * [77] Longest Common Subsequence
 *
 * https://www.lintcode.com/problem/longest-common-subsequence/description
 *
 * lintcode
 * Medium (41.00%)
 * Total Accepted:    21847
 * Total Submissions: 53048
 * Testcase Example:  '""\n""'
 *
 * Given two strings, find the longest common subsequence (*LCS*).
 * 
 * Your code should return the length of *LCS*.
 * Example:
 * Input:  "ABCD" and "EDCA"
 * Output:  1
 * Explanation:
 * LCS is 'A' or  'D' or 'C'
 * 
 * @Category DP 双序列
 * @Idea 
 * S1: DP T=O(mn) S=O(mn)
 * 特例: if A.empty()||B.empty() return 0
 * dp[i][j]表示A[0,i)和B[0,j)的LCS
 * dp[i][j]= 
 *   if A[i-1]==B[j-1] 1+dp[i-1][j-1]
 *   else max(dp[i-1][j],dp[i][j-1])
 * 初始化 dp[0][j]=dp[i][0]=0
 * 
 * 坑 特例: if A.empty()||B.empty() return 0
 * 坑 初始化 dp[0][j]=dp[i][0]=0
 * 
 * S2: Recursion
 */
class Solution {
public:
    /**
     * @param A: A string
     * @param B: A string
     * @return: The length of longest common subsequence of A and B
     */
    // S1: DP 双序列 T=O(mn) S=O(mn)
    int longestCommonSubsequence(string &A, string &B) {
        if (A.empty() || B.empty()) { return 0; }               // 坑: 特例
        int al = A.length(), bl = B.length();
        vector<vector<int>> dp(al + 1, vector<int>(bl + 1, 0)); // dp[i][j]表示A[0,i)和B[0,j)的LCS，初始化0
        for (int i = 1; i <= al; ++i) {
            for (int j = 1; j <= bl; ++j) {                     
                if (A[i - 1] == B[j - 1]) {                     // 若最后字符同, 则最后字符构成新LCM
                    dp[i][j] = 1 + dp[i - 1][j - 1];            //   dp[i][j]=1+dp[i-1][j-1]
                }
                else {                                          // 若最后字符不同,则去掉A[i]或B[j]
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]); //   dp[i][j]=max(dp[i][j-1],dp[i-1][j])
                }
            }
        }
        return dp[al][bl];                                      // 返回dp[m-1][n-1]
    }
};
