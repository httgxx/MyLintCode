/*
 * @lc app=lintcode id=154 lang=cpp
 *
 * [154] Regular Expression Matching
 *
 * https://www.lintcode.com/problem/regular-expression-matching/description
 *
 * lintcode
 * Hard (27.00%)
 * Total Accepted:    10304
 * Total Submissions: 36786
 * Testcase Example:  '"aa"\n"a"\n'
 *
 * Implement regular expression matching with support for '.' and '*'.'.'
 * Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * 
 * The matching should cover the entire input string (not partial).
 * 
 * The function prototype should be:
 * bool isMatch(string s, string p)
 * 
 * isMatch("aa","a") → false
 * isMatch("aa","aa") → true
 * isMatch("aaa","aa") → false
 * isMatch("aa", "a*") → true
 * isMatch("aa", ".*") → true
 * isMatch("ab", ".*") → true
 * isMatch("aab", "c*a*b") → true
 * 
 * @Category DP 双序列型
 * @Idea
 * S: DP // O(mn) S=O(mn)
 * dp[i][j]表示s[0,i)和p[0,j)是否match
 * 1.若p尾非*: s尾配p尾, 条件:s[i-1]==p[j-1]||p[j-1]=='.': dp[i][j]=dp[i-1][j-1]
 * 2.若p尾为*: s尾配p尾
 *      条件1: s尾配0个p尾 => 跳过p尾(x*)不用配: dp[i][j]=dp[i][j-2]
 *      条件2: s尾配多个p尾中的最后一个 => s尾配掉1个p尾后,s尾-1配0或多个p尾
 *             条件:s[i-1]==p[j-2]||p[j-2]=='.':  dp[i][j]=dp[i-1][j]
 * 坑: 初始化时千万小心
 *     dp[0][0]=true因为空串匹配空pattern
 *     //dp[i][0]=false因为非空串不能匹配空pattern,不用写因为初始值就是false
 * 坑: i=0~n, j=1~m,因为j=0初始化值就满足
 * 坑: x*配x和x配x的条件都要加i>0
 * 坑: x*配x的条件要s[i-1]==p[j-2]而不是p[j-1]
 * 坑: 跳过x*不配的值是dp[i][j-2]而不是dp[i][j-1]
 */
class Solution {
public:
    /**
     * @param s: A string 
     * @param p: A string includes "." and "*"
     * @return: A boolean
     */
    bool isMatch(string &s, string &p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;  // 空串匹配空pattern
        // dp[i][0] = false; // 因为非空串不能匹配空pattern
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {  // 坑: j从1开始,因为j=0时初始值false已满足
                // 以*结尾
                if (j > 1 && p[j - 1] == '*') {  // 坑: x*长度>1 => j>1
                    dp[i][j] = (i > 0 && isCharMatch(s[i - 1], p[j - 2]) && dp[i - 1][j])  // x*配x
                               || dp[i][j - 2];  // 跳过x*不用配 // 坑: p[j-2],dp[i][j-2]而不是j-1
                }
                // 不以*结尾
                else {  // 坑: s必须非空 => i>0
                    dp[i][j] = i > 0 && isCharMatch(s[i - 1], p[j - 1]) && dp[i - 1][j - 1]; // x配x
                }
            }
        }
        return dp[m][n];
    }
    bool isCharMatch(char sc, char pc) {
        return sc == pc || pc == '.';
    }
};
