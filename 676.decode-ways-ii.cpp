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
                    dp[i] += 15 * dp[i - 2];
                }
                // 坑:pre=0或>2时并不退出,因pre可单独解码或和pre's pre组合解码
            }

            dp[i] %= kMod;
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
