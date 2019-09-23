/*
 * @lc app=lintcode id=1093 lang=cpp
 *
 * [1093] Number of Longest Increasing Subsequence
 *
 * https://www.lintcode.com/problem/number-of-longest-increasing-subsequence/description
 *
 * lintcode
 * Medium (35.00%)
 * Total Accepted:    858
 * Total Submissions: 2431
 * Testcase Example:  '[1,3,5,4,7]'
 *
 * Given an unsorted array of integers, find the number of longest increasing
 * subsequence.
 * 
 * Example 1:
 * Input: [1,3,5,4,7]
 * Output: 2
 * Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
 * 
 * Example 2:
 * Input: [2,2,2,2,2]
 * Output: 5
 * Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5
 * 
 * 
 * 
 */
class Solution {
public:
    /**
     * @param nums: an array
     * @return: the number of longest increasing subsequence
     */
    int findNumberOfLIS(vector<int>& nums) {
        int res = 0, mx = 0, n = nums.size();
        vector<int> len(n, 1), cnt(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] <= nums[j]) continue;
                if (len[i] == len[j] + 1) cnt[i] += cnt[j];
                else if (len[i] < len[j] + 1) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                }
            }
            if (mx == len[i]) res += cnt[i];
            else if (mx < len[i]) {
                mx = len[i];
                res = cnt[i];
            }
        }
        return res;
    }
};
