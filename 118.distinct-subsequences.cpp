/*
 * @lc app=lintcode id=118 lang=cpp
 *
 * [118] Distinct Subsequences
 *
 * https://www.lintcode.com/problem/distinct-subsequences/description
 *
 * lintcode
 * Medium (34.00%)
 * Total Accepted:    13743
 * Total Submissions: 40133
 * Testcase Example:  '"rabbbit"\n"rabbit"'
 *
 * Given two strings `S` and `T`. Count the number of distanct subsequences of
 * `S` which equals `T`.
 * 
 * A subsequence of a string is a new string which is formed from the original
 * string by deleting some (can be none) of the characters without disturbing
 * the relative positions of the remaining characters. (ie, `"ACE"` is a
 * subsequence of `"ABCDE"` while `"AEC"` is not)
 * 
 * Example 1:
 * Input: S = "rabbbit", T = "rabbit"
 * Output: 3
 * Explanation: You could remove any 'b' in S, so there are 3 ways to get T.
 * 
 * Example 2:
 * Input: S = "abcd", T = ""
 * Output: 1
 * Explanation: There is only 1 way to get T - remove all chars in S.
 * 
 * @Category DP 双序列型
 * @Idea
 * DP T=O(mn) T=O(mn)
 * dp[i][j]表示T[0,i)在S[0,j)出现次数
 * dp[0][j]=1   // 空串在任意串中出现1次
 * dp[i>0][0]=0 // 非空串在空串中出现0次
 * dp[i][j]= dp[i][j-1] +  // 不考虑s[j-1]时,T[0,i)在S[0,j-1)中出现次数
 *     S[i-1]==T[j-1] ? dp[i-1][j-1] : 0  
 *     // 考虑s[j-1]时,增加的T[0,i)的出现次数=T[i-1]和S[j-1]匹配T[0,i-1)在S[0,j-1)中出现次数
 * 
 * 坑 一定看清题意是S在T中出现次数,还是T在S中出现次数
 * 坑 dp第1维i是T的idx而不是S的idx,所以dp[tl][sl]而不是dp[sl][tl],T[i-1]而不是T[j-1],S[j-1]而不是S[i-1]
 * 坑 用tl=T.length(),sl=S.length()而不用m,n以防止dp[i][j]定义出错!!!
 * 坑 T在S中出现次数则T必须被完全匹配
 * 坑 初始化 dp[0][j]=1 //空串在任意串中出现1次, dp[i>0][0]=0 //非空串在空串中出现0次
 * 坑 总次数=不考虑s[j-1]时,T[0,i)在S[0,j-1)中出现次数 //dp[i][j-1]
 *         +T与S最后字符配时,增加的T在S中出现次数=各自除去最后字符后T'在S'中出现次数 //dp[i-1][j-1]
 * 坑 没有+1 !!!
 */
class Solution {
public:
    /**
     * @param S: A string
     * @param T: A string
     * @return: Count the number of distinct subsequences
     */
    int numDistinct(string &S, string &T) {
        int tl = T.length(), sl = S.length();
        vector<vector<int>> dp(tl + 1, vector<int>(sl + 1, 0));  // 坑 dp第1维i是T的idx而不是S的idx
        for (int i = 0; i <= tl; ++i) {  // 当前T子串
            for (int j = 0; j <= sl; ++j) {  // 当前S子串
                if (i == 0) { dp[i][j] = 1; }   // 空串在任意串中出现1次
                else if (j == 0)  { dp[i][0] = 0; }   // 非空串在空串中出现0次
                else{
                    dp[i][j] = dp[i][j - 1];  // 不管当前S最后一个字符时,T[0,i)在S[0,j-1)中出现次数
                    // 坑 还要考虑T与S最后字符配时增加的T在S出现次数=各自除去最后字符后T'在S'中出现次数
                    if (T[i - 1] == S[j - 1]) { dp[i][j] += dp[i - 1][j - 1]; }
                }
            }
        }
        return dp[tl][sl];
    }
};
