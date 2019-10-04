/*
 * @lc app=lintcode id=159 lang=cpp
 *
 * [159] Find Minimum in Rotated Sorted Array
 *
 * https://www.lintcode.com/problem/find-minimum-in-rotated-sorted-array/description
 *
 * lintcode
 * Medium (44.00%)
 * Total Accepted:    43516
 * Total Submissions: 98669
 * Testcase Example:  '[1,2,3]\n'
 *
 * Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 * 
 * (i.e., `0 1 2 4 5 6 7` might become `4 5 6 7 0 1 2`).
 * 
 * Find the minimum element.
 * 
 * Example 1:
 * Input: [3,4,5,1,2] 
 * Output: 1
 * 
 * Example 2:
 * Input: [4,5,6,7,0,1,2]
 * Output: 0
 */
class Solution {
public:
    /**
     * @param nums: a rotated sorted array
     * @return: the minimum number in the array
     */
    // 数组没转或转点在左半段时,右半段仍升序即中间值小于最右值
    // e.g.1234567,6712345故[mid]<[right]时要去左半边继续搜
    // T=O(logn) S=O(1)
    int findMin(vector<int> &nums) {
        int left = 0, right = (int)nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) { left = mid + 1; }
            else right = mid;
        }
        return nums[right];
    }
};
