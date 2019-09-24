/*
 * @lc app=lintcode id=382 lang=cpp
 *
 * [382] Triangle Count
 *
 * https://www.lintcode.com/problem/triangle-count/description
 *
 * lintcode
 * Medium (37.00%)
 * Total Accepted:    13869
 * Total Submissions: 36908
 * Testcase Example:  '[3,4,6,7]\n'
 *
 * Given an array of integers, how many three numbers can be found in the
 * array, so that we can build an triangle whose three edges length is the
 * three numbers that we find?
 * 
 * Example 1:
 * Input: [3, 4, 6, 7]
 * Output: 3
 * Explanation:
 * They are (3, 4, 6), 
 *          (3, 6, 7),
 *           (4, 6, 7)
 * Example 2:
 * Input: [4, 4, 4, 4]
 * Output: 4
 * Explanation: Any three numbers can form a triangle. So the answer is C(3, 4) = 4
 * 
 * @Category 2sum
 * @Idea
 * S1: 双指针 O(n) O(1)
 * 
 */
class Solution {
public:
    /**
     * @param S: A list of integers
     * @return: An integer
     */
    // S1 双指针 O(n) O(1)
    int triangleCount(vector<int>& nums) {
        int res = 0, n = nums.size();
        sort(nums.begin(), nums.end());         // 先从小到大排序
        for (int i = n - 1; i >= 2; --i) {      // 从后往前扫,每次将扫到的数当作三角形的1边长度
            int left = 0, right = i - 1;        // 双指针从两端向中间取三角形的另外2边长度
            while (left < right) {
                if (nums[left] + nums[right] > nums[i]) {
                    res += right - left;    // 若另2边之和>第1边,合法三角形个数+=两指针所夹数字总个数,
                    --right;                // 减小1边长度,继续循环查看和
                }
                else { ++left; }            // 若另2边之和<=第1边,不是合法三角形,增加啊1边长度,继续循环查看和
            }
        }
        return res;
    }
};
