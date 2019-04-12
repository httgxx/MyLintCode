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
 * 特例: 空串解码方法为0
 * 常例限制:一位数时不能为0，两位数不能大于26，其十位上的数也不能为0
 * dp[i]表示到第i个字符有多少种解码方式
 * dp[i]=dp[i-1]|前1位不为0 + dp[i-2]|前两位在10~26即s[i-2]=='1'||(s[i-2]=='2'&&s[i-1]<='6')
 * i从0开始,第0个字符对应的dp[0]=1因为为了使得dp[1]=dp[0]=1,dp数组大小为n+1
 */
class Solution {
public:
    /**
     * @param s: a string,  encoded message
     * @return: an integer, the number of ways decoding
     */
    int numDecodings(string &s) {
        if (s.empty()) { return 0; }
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1; //需要使dp[1]=dp[0]时得到1
        for (int i = 1; i < dp.size(); ++i) { //第i位数字
            // 第i位单独解码
            if (s[i - 1] != '0') { //第i位数字=s[i-1]
                dp[i] += dp[i - 1]; //坑: += 而不是 =
            }
            // 第i位与第i-1位一起解码
            if (i > 1 && //坑: 不要忘记i>1
                (s[i - 2] == '1' || //坑: i-2而不是i-1
                 (s[i - 2] == '2' && s[i - 1] <= '6'))) { // 10~26
                dp[i] += dp[i - 2];
            }
        }
        return dp.back(); //不用dp[index]省得index写错
    }
};
