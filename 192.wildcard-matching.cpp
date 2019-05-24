/*
 * @lc app=lintcode id=192 lang=cpp
 *
 * [192] Wildcard Matching
 *
 * https://www.lintcode.com/problem/wildcard-matching/description
 *
 * lintcode
 * Hard (30.00%)
 * Total Accepted:    10992
 * Total Submissions: 36130
 * Testcase Example:  '"aa"\n"a"\n'
 *
 * Implement wildcard pattern matching with support for `'?'` and `'*'`.
 * 
 * - `'?'` Matches any single character.
 * - `'*'` Matches any sequence of characters (including the empty sequence).
 * 
 * The matching should cover the entire input string (not partial).
 * 
 * Example 1:
 * Input："aa"，"a"
 * Output：false
 * Explanation：
 * unable to match
 * 
 * Example 2:
 * Input："aa"，"a*"
 * Output：true
 * Explanation：
 * '*' can repeat a
 * 
 * @Category DP 双序列型
 * @Idea
 * S: DP //T=O(mn) S=O(mn) => 滚动数组优化到O(n)
 * dp[i][j]表示s的前i个字符是否匹配p的前j个字符
 * 1.p尾是'*': s尾配p尾(条件:i>0且(p[j-1]=='?'或s[i-1]==p[j-1]): dp[i][j]=dp[i-1][j-1]
 * 2.p尾非'*': s尾配0或多个p尾 
 *   1)s尾配0个p尾 => 跳过p尾不用配: dp[i][j]=dp[i-1][j]
 *   2)s尾配多个p尾中的最后一个 => s尾配掉1个p尾后,s前一尾配0或多个p尾: dp[i][j]=dp[i][j-1]
 * => 
 * dp[0][0]=true    //前0个字符配空串
 * dp[i>0][0]=false //前多个字符不配空串
 * 大坑:不能判定dp[0][j]=false(前0个字符不配非空串) - 错!!!因为p可以为*,**,***,...都可配前i个字符
 * dp[i>0][j>0]= if(p[j-1]=='*'): (p[j-1]=='?' || s[i-1]==p[j-1]) && dp[i-1][j-1]
 *               else: dp[i][j-1] || dp[i-1][j]   //配0个p尾 或 配多个p尾中的最后一个
 * 返回 dp[m][n]
 * 大坑:不能判定dp[0][j>0]=false(前0个字符不配非空串) - 错!!!因为p可以为*,**,***,...都可配前i个字符
 *      所以dp[0][j>0]也得由公式计算!!!
 * */
class Solution {
public:
    /**
     * @param s: A string 
     * @param p: A string includes "?" and "*"
     * @return: is Match?
     */
    bool isMatch(string &s, string &p) {
        int m = s.length(), n = p.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, false));  //s前i个字符是否匹配p前j个字符
        
        // 坑: 不能直接判定"dp[0][j>0]=f"因为p可*,**...可匹配前0个字符,故dp[0][j>0]也要用公式计算!
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <=n; ++j) {
                if (j == 0) {  // 空pattern
                    dp[i][j] = i == 0;  // 空patter只能匹配前0个字符
                }
                
                // j > 0
                if (p[j - 1] != '*') {  // p尾非*,即p尾为?或字母
                    if (i > 0 && (p[j - 1] == '?' || p[j - 1] == s[i - 1])) {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                }
                else {  // p尾是*(0个或多个*) // 包含dp[i>0][0]的情况
                    dp[i][j] = dp[i][j - 1];  // s尾配0个*
                    if (i > 0) {  // 包含dp[i>0][0]=true的情况即p[j-1]=*
                        dp[i][j] = dp[i][j] || dp[i - 1][j]; //s尾配多个*中最后1个以后
                                                             //p尾又成>=0个*,故j不变
                    }  // if
                }  // else
            }  // for
        }  // for
        
        return dp[m][n];
    }
};
