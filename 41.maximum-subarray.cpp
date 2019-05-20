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
 * 
 * Example:
 * Input: [−2,2,−3,4,−1,2,1,−5,3]
 * Output: 6
 * Explanation: the contiguous subarray [4,−1,2,1] has the largest sum = 6.
 * 
 * @Category MaxSubArray
 * @Idea
 * S1: Greedy 和<0了就重新开始算 // T=O(n) S=O(1)
 * curSum = 0
 * for (num in nums)
 *     curSum = num + max(curSum, 0);  // 包含num的局部最大和
 *     res = max(res, curSum);  // 不包含num或包含num的全局最大和
 * 
 * S2: 二分法
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
            curSum = num + max(curSum, 0);  // 包含num的局部最大和
            res = max(res, curSum);  // 不包含num或包含num的全局最大和
        }
       return res;
    }
};
