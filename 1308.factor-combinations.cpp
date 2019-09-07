/*
 * @lc app=lintcode id=1308 lang=cpp
 *
 * [1308] Factor Combinations
 *
 * https://www.lintcode.com/problem/factor-combinations/description
 *
 * lintcode
 * Medium (60.00%)
 * Total Accepted:    1201
 * Total Submissions: 1985
 * Testcase Example:  '32'
 *
 * Numbers can be regarded as product of its factors. For example,
 * 
 * ~~~~.
 * 8 = 2 x 2 x 2;
 * ⁠ = 2 x 4.
 * ~~~~
 * Write a function that takes an integer n and return all possible
 * combinations of its factors.
 */
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> res;
        helper(n, 2, {}, res);
        return res;
    }
    void helper(int n, int start, vector<int> out, vector<vector<int>> &res) {
        if (n == 1) {
            if (out.size() > 1) res.push_back(out);
        } else {
            for (int i = start; i <= n; ++i) {
                if (n % i == 0) {
                    out.push_back(i);
                    helper(n / i, i, out, res);
                    out.pop_back();
                }
            }
        }
    }
};
