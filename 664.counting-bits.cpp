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
 * S1: 从1开始，遇到偶数时，其1的个数和该偶数除以2得到的数字的1的个数相同，遇到奇数时，其1的个数等于该奇数除以2得到的数字的1的个数再加1
 * S2: 
 */
class Solution {
public:
    /**
     * @param num: a non negative integer number
     * @return: an array represent the number of 1's in their binary
     */
    vector<int> countBits(int num) {
        vector<int> res{0};
        for (int i = 1; i <= num; ++i) {
            if (i % 2 == 0) res.push_back(res[i / 2]);
            else res.push_back(res[i / 2] + 1);
        }
        return res;
    }
};
