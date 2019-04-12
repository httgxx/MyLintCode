/*
 * @lc app=lintcode id=512 lang=cpp
 *
 * [512] Decode Ways
 *
 * https://www.lintcode.com/problem/decode-ways/description
 *
 * lintcode
 * Medium (23.00%)
 * Total Accepted:    10341
 * Total Submissions: 44641
 * Testcase Example:  '"12"\n'
 *
 * A message containing letters from `A-Z` is being encoded to numbers using
 * the following mapping:
 * ```
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * ```
 * Given an encoded message containing digits, determine the total number of
 * ways to decode it.
 * 
 * @Category DP
 * @Ideas
 * dp[i]表示前i个字符有多少种解码方式, i=0~n
 * dp[i]=dp[i-1]|s[i-1]1位单独对应1个字符 + dp[i-2]|s[i-2]s[i-1]2位一起对应1个字符
 * 坑:推倒公式中必须设置dp[0]=1, 但题目要求空串返回0(而不是1)所以必须先处理空串这个特例
 */
class Solution {
public:
    /**
     * @param s: a string,  encoded message
     * @return: an integer, the number of ways decoding
     */
    int numDecodings(const string &s) {
        if (s.empty()) { return 0; }  // 按题意特殊处理空串返回0
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;  // 空子串有一种解码方式
        for (int i = 1; i < dp.size(); ++i) {  // 前i个数字
            // 前i个数字的最后1位(第i-1个数字)是某字符的编码
            if (s[i - 1] != '0') {
                dp[i] += dp[i - 1];  // 坑: += 而不是 =
            }
            // 前i个数字的最后2位(第i-2和i-1个数字)是某字符的编码
            if (i >= 2 &&  // 坑: 不要忘记i>1
                (s[i - 2] == '1' ||  // 坑: i-2而不是i-1
                 (s[i - 2] == '2' && s[i - 1] <= '6'))) {  // 10~26
                dp[i] += dp[i - 2];
            }
        }
        return dp.back();  // 不用写dp[s.size()]省得index写错
    }
};
