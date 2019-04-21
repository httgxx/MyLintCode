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
    int numDecodings(string &s) {
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
};
