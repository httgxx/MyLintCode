/*
 * @lc app=lintcode id=29 lang=cpp
 *
 * [29] Interleaving String
 *
 * https://www.lintcode.com/problem/interleaving-string/description
 *
 * lintcode
 * Medium (27.00%)
 * Total Accepted:    16434
 * Total Submissions: 58864
 * Testcase Example:  '"aabcc"\n"dbbca"\n"aadbbcbcac"'
 *
 * Given three strings: *s1*, *s2*, *s3*, determine whether *s3* is formed by
 * the interleaving of *s1* and *s2*.
 * Example 1:
 * Input: "aabcc" "dbbca" "aadbbcbcac"
 * Output: true
 * 
 * Example 2:
 * Input: "" "" "1"
 * Output: false
 * 
 * Example 3:
 * Input: "aabcc" "dbbca" "aadbbbaccc"
 * Output: false
 * 
 * @Category DP 双序列
 * @Idea
 * DP T=O(mn) S=O(mn)
 * 1.首先检查长度 if(s1.len+s2.len != s2.len) return false
 * 2.dp[i][j]表示s1[0,i)和s2[0,j)是否能构成s2[0,i+j)
 *   dp[i][j]=
 *     1)if s3尾配s1尾: s3[i+j-1]==s1[i-1] && dp[i-1][j]
 *     2)if s3尾配s2尾: s3[i+j-1]==s2[j-1] && dp[i][j-1]
 *     3)else false
 *   初始化 
 *     1)if s1和s2都空: dp[0][0]=true
 *     2)if 只有s1为空: 须s3尾配s1尾 dp[0][j>0]=dp[0][j-1]&&s3[j-1]==s2[j-1]
 *     3)if 只有s2为空: 须s3尾配s1尾 dp[i>0][0]=dp[i-1][0]&&s3[i-1]==s1[i-1]
 *   返回 dp[s1.len][s2.len]   
 */
class Solution {
public:
    /**
     * @param s1: A string
     * @param s2: A string
     * @param s3: A string
     * @return: Determine whether s3 is formed by interleaving of s1 and s2
     */
    bool isInterleave(string &s1, string &s2, string &s3) {
        int n1 = s1.length(), n2 = s2.length(), n3 = s3.length();
        if (n1 + n2 != n3) return false;
        //if (n1 == 0) return s2 == s3;  // can be handled by code bellow
        //if (n2 == 0) return s1 == s3;  // can be handled by code bellow
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        for (int i = 0; i <= n1; ++i) {
            for (int j = 0; j <= n2; ++j) {
                if (i == 0 && j == 0) { dp[i][j] = true; }  // 空+空=空
                else if (i == 0) { dp[i][j] = dp[0][j - 1] && s3[j - 1] == s2[j - 1]; }//空+非空2=非空2
                else if (j == 0) { dp[i][j] = dp[i - 1][0] && s3[i - 1] == s1[i - 1]; }//非空1+空=非空1
                else {  // 非空1+非空2=非空3
                    dp[i][j] = (s3[i + j - 1] == s1[i - 1] && dp[i - 1][j]) ||  //非空1 - 1 =非空3 - 1
                               (s3[i + j - 1] == s2[j - 1] && dp[i][j - 1]);    //非空2 - 1 =非空3 - 1
                }
            }
        }
        return dp[n1][n2];
    }
};
