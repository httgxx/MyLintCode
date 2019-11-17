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
 * =if(A[i-1]==B[j-1]) 1+dp[i-1][j-1]
 *  else max(dp[i-1][j],dp[i][j-1])
 * 初始化 dp[0][j]=dp[i][0]=0
 * 从i=1,j=1开始循环处理
 * 
 * 坑 特例: if A.empty()||B.empty() return 0
 * 坑 初始化 dp[0][j]=dp[i][0]=0
 * 
 * S2: 递归+记忆搜索
 * T=O(mn) S=O(mn)
 * helper(A,subEndIdxA,B,subEndIdxB, mem)=
 *     if 有记忆值mem[subEndIdxA+1][subEndIdxB+1]则返回记忆值
 *     else 计算值并更新记忆
 *          if A[subEndIdxA]==B[subEndIdxB]: 1+helper(subEndIdxA,subEndIdxB)
 *          else: max(helper(subEndIdxA-1,subEndIdxB), helper(subEndIdxA, subEndIdxB-1))
 *     return 新计算的记忆值
 * 坑1: 初始化mem所有为-1而非0来区分没计算过的情况和不匹配的情况
 * 坑2: [al+1][bl+1]因mem[0][i]=0指长为0的A子串(而非首字符A[0])不匹配B
 * 坑3: helper参数传的是subStr末元素index而不是subStr长度, 故m[endA+1][endB+1]
 */
class Solution {
public:
    /**
     * @param A: A string
     * @param B: A string
     * @return: The length of longest common subsequence of A and B
     */
    // S1: DP 双序列 T=O(mn) S=O(mn)
    int longestCommonSubsequence1(string &A, string &B) {
        if (A.empty() || B.empty()) { return 0; }               // 坑: 特例
        int al = A.length(), bl = B.length();
        vector<vector<int>> dp(al + 1, vector<int>(bl + 1, 0)); // dp[i][j]表示A[0,i)和B[0,j)的LCS,(m+1)*(n+1),初始化=0
        for (int i = 1; i <= al; ++i) {
            for (int j = 1; j <= bl; ++j) {                     
                if (A[i - 1] == B[j - 1]) {                     // 若最后字符同, 则最后字符构成新LCM
                    dp[i][j] = 1 + dp[i - 1][j - 1];            //   dp[i][j]=1+dp[i-1][j-1]
                }
                else {                                          // 若最后字符不同,则去掉A[i]或B[j]求最大
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]); //   dp[i][j]=max(dp[i][j-1],dp[i-1][j])
                }
            }
        }
        return dp[al][bl];                                      // 返回dp[m][n]
    }

    // S2: 递归+记忆搜索
    // T=O(mn) S=O(mn)
    int longestCommonSubsequence(const string& A, const string& B) {
        if (A.empty() || B.empty()) { return 0; }               // 坑: 特例
        int al = A.length(), bl = B.length();
        vector<vector<int>> m(al + 1, vector<int>(bl + 1, -1)); // 记忆m[i][j]=A[0,i]和B[0,j]的LCS 坑:al+1,bl+1
                                                                // 坑1: 须初始化所有为-1而非0来区分没计算过的情况和不匹配的情况
                                                                // 坑2: 须[al+1][bl+1]因mem[0][i]=0指长为0的A子串(而非首字符A[0])不匹配B
        for (int i = 0; i <= al; ++i) { m[i][0] = 0; }          // 初始化首行首列m[0][j]=m[i][0]=0
        for (int j = 0; j <= bl; ++j) { m[0][j] = 0; }
        return helper(A, al - 1, B, bl - 1, m);                 // 递归+记忆搜索 // 坑3: 参数传的是subStr末元素index而不是subStr长度
    }
    int helper(const string &A, int endA, const string &B, int endB, vector<vector<int>>& m) {
        if(m[endA + 1][endB + 1] >= 0) {                        // 坑3: 参数传的是subStr末元素index而不是subStr长度, 故m[endA+1][endB+1]
            return m[endA + 1][endB + 1];                       // 若有记忆,直接返回记忆值
        }        
        m[endA + 1][endB + 1] =                                 // 若无记忆,计算并更新记忆 // 坑3: m[endA+1][endB+1]   
            A[endA] == B[endB]
            ? 1 + helper(A, endA - 1, B, endB - 1, m)           //   若最后同, 则最后字符构成新LCM
            : max(helper(A, endA - 1, B, endB, m),              //   若最后不同,则去掉A[i]或B[j]求最大
                  helper(A, endA, B, endB - 1, m));
        return m[endA + 1][endB + 1];                           // 返回新计算的记忆值 // 坑3: m[endA+1][endB+1]
    }
};
