/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 *
 * https://leetcode.com/problems/two-sum/description/
 *
 * algorithms
 * Easy (43.07%)
 * Total Accepted:    1.7M
 * Total Submissions: 3.8M
 * Testcase Example:  '[2,7,11,15]\n9'
 *
 * Given an array of integers, return indices of the two numbers such that they
 * add up to a specific target.
 * You may assume that each input would have exactly one solution, and you may
 * not use the same element twice.
 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 *
 * @Category 2Sum,2Pointers
 * @Ideas
 * S1: T=O(n)   S=O(n) 单指针从左到右边扫边匹配/存，若map里已有（sum-[i])则找到匹配输出，否则记录i坐标map[i]=i
 * S2: T=O(nlgn)S=O(1) 先从小到大排序!再双指针两边往中间扫,左右之和与目标值比较1)等于则输出2)偏小则左指针后移3)偏大则右指针前移 
 * BF: T=O(n^2) S=O(1) 同向双指针从左扫到右,左指针每右移1位,右指针从其下一位开始扫向尾,直到找到左右之和等于目标值 
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indices;
        for (int i = 0; i < nums.size(); i++) {
            if (indices.find(target - nums[i]) != indices.end()) {
                return {indices[target - nums[i]], i};
            }
            indices[nums[i]] = i;
        }
        return {};
    }
};