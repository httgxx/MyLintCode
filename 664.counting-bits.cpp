/*
 * @lc app=lintcode id=664 lang=cpp
 *
 * [664] Counting Bits
 *
 * https://www.lintcode.com/problem/counting-bits/description
 *
 * lintcode
 * Medium (55.00%)
 * Total Accepted:    1672
 * Total Submissions: 2990
 * Testcase Example:  '0\n'
 *
 * Given a **non negative** integer number num. For every numbers i in the
 * range `0 ≤ i ≤ num` calculate the number of 1's in their binary
 * representation and return them as an array.
 *
 * @Category DP
 * @Ideas
 * S1: DP T=O(n) S=O(n)
 * dp[i]表示数值为i的二进制表示种1的个数
 * dp[i]=dp[i>>2]+i%2
 * 初始 dp[0]=0
 * 
 * S2: 每个数i的二进制表示中1的个数都是i&(i-1)对应的值加1
 */
class Solution {
public:
    /**
     * @param num: a non negative integer number
     * @return: an array represent the number of 1's in their binary
     */
    vector<int> countBits(int num) {
        vector<int> res { 0 };
        for (int i = 1; i <= num; ++i) {
            res.push_back(res[i >> 1] + i % 2);
        }
        return res;
    }
    vector<int> countBits1(int num) {
        vector<int> res(num + 1, 0);
        for (int i = 1; i <= num; ++i) {
            res[i] = res[i & (i - 1)] + 1;
        }
        return res;
    }
};
