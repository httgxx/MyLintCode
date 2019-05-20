/*
 * @lc app=lintcode id=41 lang=cpp
 *
 * [41] Maximum Subarray
 *
 * https://www.lintcode.com/problem/maximum-subarray/description
 *
 * lintcode
 * Easy (40.00%)
 * Total Accepted:    39103
 * Total Submissions: 95365
 * Testcase Example:  '[-2,2,-3,4,-1,2,1,-5,3]\n\n\n'
 *
 * Given an array of integers, find a contiguous subarray which has the largest
 * sum.
 */
class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A integer indicate the sum of max subarray
     */
    int maxSubArray(vector<int> &nums) {
        int res = INT_MIN, curSum = 0;
        for (int num : nums) {
            curSum = max(curSum + num, num);
            res = max(res, curSum);
        }
       return res;
    }
};
