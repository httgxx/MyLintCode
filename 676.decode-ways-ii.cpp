/*
 * @lc app=lintcode id=676 lang=cpp
 *
 * [676] Decode Ways II
 *
 * https://www.lintcode.com/problem/decode-ways-ii/description
 *
 * lintcode
 * Hard (33.00%)
 * Total Accepted:    776
 * Total Submissions: 2295
 * Testcase Example:  '"1*"'
 *
 * A message containing letters from A-Z is being encoded to numbers using the
 * following mapping way:
 * ```
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * ```
 * Beyond that, now the encoded string can also contain the character `*`,
 * which can be treated as one of the numbers from 1 to 9.
 * Given the encoded message containing digits and the character `*`, return
 * the total number of ways to decode it.
 * Also, since the answer may be very large, you should return the output mod
 * 10^9 + 7.
 * 
 * @Category DP(按情况叠加比较型),枚举细节
 * @Ideas 
 * DP T=O(n) S=O(n)->O(1)
 * dp[i]表示s[0~i]的解码方式总数 =>dp.size=n+1, 
 *      i可以看作当前处理的子串长度
 * 特例: s空或s[0]为'0'时直接返回0 
 * 初始化: dp[0]=1,dp[1]=(s[0]=='*')?9:1
 * for i=2~n: 
 *     dp[i]=decodeOne(s[i-1])*dp[i-1]+decodeTwo(s[i-2],s[i-1])*dp[i-2]
 *     dp[i] %= 1e9+7
 * => 降维: 
 * for i=2~n: 
 *     long dp_i = ways(s[i-1]) * dp[1] + ways(s[i - 2], s[i-1]) * dp[0];
 *     dp_i %= 1e9+7;
 *     dp[0] = dp[1];
 *     dp[1] = dp_i;
 * 坑:s[0]=='0'时,非法直接返回0
 * 坑:'0'前面有数字且数字不是1和2时,非法直接返回0 
 * 坑: vector<long> dp必须long否则溢出
 * 坑: 循环内每次计算出一个dp_i就取模避免大数字运算
 */
class Solution {
public:
    /**
     * @param s: a message being encoded
     * @return: an integer
     */
        int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;  // 特例
        
        int n = s.length(), kMod = 1e9 + 7;
        vector<long> dp(2, 0);  // 必须用long防止溢出

        dp[0] = 1;
        dp[1] = (s[0] == '*') ? 9 : 1;  // *=>1~9 9种编码,k=1~9 1种编码
        
        for (int i = 2; i <= n; ++i) {  // 坑:降维dp[n+1]=>dp[2]
            long dp_i = decodeOneNum(s[i - 1]) * dp[1] +
                decodeTwoNums(s[i - 2], s[i - 1]) * dp[0];
            dp_i %= kMod;  // 坑:每算出一个中间结果就mod来避免大数字mod运算
            dp[0] = dp[1];
            dp[1] = dp_i;
        }
        return dp[1];
    }
    int decodeOneNum(char c) {
        switch(c) {
            case '0': return 0;  // 单独0非法
            case '*': return 9;  // *=>1~9 9种
            default: return 1;  // k=1~9 1种
        }
    }
    int decodeTwoNums(char pre, char cur) {
        // **
        if (pre == '*' && cur == '*') {
            return 15;  // **=>11~26 15种
        }
        // *x
        else if (pre == '*') { // *x=>*0~9都合法
            // *0~*6=>10~16 or 20~26 2种
            // *7~*9=>17~19 1种
            return (cur >= '0' && cur <= '6') ? 2 : 1;
        }
        // x*
        else if (cur == '*') { // x*=>0~9*合法只有1~2*
            switch(pre) {
                case('1'): return 9;  // 1*=>11~19 Q:为什么不把10算进去??
                case('2'): return 6;  // 2*=>21~26 Q:为什么不把20算进去??
                default: return 0;  // 坑: 0*或3~9*都非法直接退出
            }
        }
        // xy
        else  //合法只有10~26
        {
            return (pre == '1' || (pre == '2' && cur >= '0' && cur <= '6'))
                ? 1 : 0;
        }
    }

    int numDecodings0(string s) {
        if (s.empty() || s[0] == '0') return 0;  // 特例
        
        int n = s.length(), kMod = 1e9 + 7;
        vector<long> dp(n + 1, 0);  // 必须用long防止溢出

        dp[0] = 1;
        dp[1] = (s[0] == '*') ? 9 : 1;  // *=>1~9 9种编码,k=1~9 1种编码
        
        for (int i = 2; i <= n; ++i) {
            char cur = s[i - 1], pre = s[i - 2];
            // Case 1: ...x0
            if (cur == '0') {
                // 注意: 单独0不是合法代码 所以不能将0单独解码成1个字符
                // 解码方案: 将x0组合解码成1个字符=>合法组合: 10,20,*0 
                if (pre == '1' || pre == '2') {  // 10,20 都只1种
                    dp[i] += 1 * dp[i - 2];
                }
                else if (pre == '*') {  // 2种方式: *=>1组成10或*=>2组成20
                    dp[i] += 2 * dp[i - 2];
                }
                else {  // 坑: pre=0或pre>2则非法:0,00,30,40,...90=>立即退出
                    return 0;
                }
            }
            // Case 2: ...xk, k=1~9
            else if (cur >= '1' && cur <= '9') {
                // 解码方案1: 将k单独解码成1个字符
                dp[i] += 1 * dp[i - 1];  // 1~9 都只1种
                // 解码方案2: 将xk组合解码成1个字符=>合法组合: 11~26,*k
                if (pre == '1' || (pre == '2' && cur <= '6')) {  // 11~26都只1种
                    dp[i] += 1 * dp[i - 2];
                }
                else if (pre == '*') {
                    if (cur <= '6') {  // 2种方式: *=>1组成11~16或*=>2组成21~26
                        dp[i] += 2 * dp[i - 2];
                    }
                    else {  // 1种方式: 只能*=>1组成17~19, 因为27~29不合法
                        dp[i] += 1 * dp[i - 2];
                    }
                }
                // 坑:pre=0或>2时并不退出,因pre可单独解码或和pre's pre组合解码
            }
            // Case 3: ...x*
            else { // cur == '*'
                // 解码方案1: 将*单独解码成1个字符
                dp[i] += 9 * dp[i - 1];  // *=>1~9 9种
                // 解码方案2: 将x*组合解码成1个字符
                if (pre == '1') {  // 1*=>11~19 9种
                    dp[i] += 9 * dp[i - 2];
                }
                else if (pre == '2') {  // 2*=>21~26 6种
                    dp[i] += 6 * dp[i - 2];
                }
                else if (pre == '*') {  // **=>11~26 15种
                    dp[i] += 15 * dp[i - 2];  // 坑i-2而不是i-1
                }
                // 坑:pre=0或>2时并不退出,因pre可单独解码或和pre's pre组合解码
            }

            dp[i] %= kMod;  // 坑:每算出一个中间结果就mod来避免大数字mod运算
        }
        return dp[n];
    }

    int numDecodings1(string &s) {
        long e0 = 1, e1 = 0, e2 = 0, f0, f1, f2, M = 1e9 + 7;
        for (char c : s) {
            if (c == '*') {
                f0 = 9 * e0 + 9 * e1 + 6 * e2;
                f1 = e0;
                f2 = e0;
            } else {
                f0 = (c > '0') * e0 + e1 + (c <= '6') * e2;
                f1 = (c == '1') * e0;
                f2 = (c == '2') * e0;
            }
            e0 = f0 % M;
            e1 = f1;
            e2 = f2;
        }
        return e0;
    }

    int numDecodings2(string s) {
        long e0 = 1, e1 = 0, e2 = 0, f0 = 0, M = 1e9 + 7;
        for (char c : s) {
            if (c == '*') {
                f0 = 9 * e0 + 9 * e1 + 6 * e2;
                e1 = e0;
                e2 = e0;
            } else {
                f0 = (c > '0') * e0 + e1 + (c <= '6') * e2;
                e1 = (c == '1') * e0;
                e2 = (c == '2') * e0;
            }
            e0 = f0 % M;
        }
        return e0;
    }
};
