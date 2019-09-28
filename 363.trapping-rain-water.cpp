/*
 * @lc app=lintcode id=363 lang=cpp
 *
 * [363] Trapping Rain Water
 *
 * https://www.lintcode.com/problem/trapping-rain-water/description
 *
 * lintcode
 * Medium (44.00%)
 * Total Accepted:    14886
 * Total Submissions: 33468
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]\n'
 *
 * Given *n* non-negative integers representing an elevation map where the
 * width of each bar is `1`, compute how much water it is able to trap after
 * raining.
 * 
 * ![Trapping Rain
 * Water](https://lintcode-media.s3.amazonaws.com/problem/rainwatertrap.png
 * "Trapping Rain Water I")
 * 
 * Example 1:
 * Input: [0,1,0]
 * Output: 0
 * 
 * Example 2:
 * Input: [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Challenge
 * O(n) time and O(1) memory
 * O(n) time and O(n) memory is also acceptable.
 * 
 * @Category 双指针
 * @Idea 左右指针往中间走,
 * 
 * 
 */
class Solution {
public:
    /**
     * @param heights: a list of integers
     * @return: a integer
     */
    // S1: 双指针
    int trapRainWater1(vector<int> &heights) {
        // write your code here
    }

    // S2: 木头原理:用低的板更新水平面 T=O(n) S=O(1)
    int trapRainWater(vector<int>& height) {
        int l = 0, r = height.size() - 1, level = 0, res = 0;
        while (l < r) {
            int lower = height[(height[l] < height[r]) ? l++ : r--];    // 取低的那边,指针向中间移(木桶原理)
            level = max(level, lower);                                  // 用低的那边更新当前水平面
            res += level - lower;                                       // 计算可多存的水量
        }
        return res;
    }
};
