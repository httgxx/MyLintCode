/*
 * @lc app=leetcode id=912 lang=cpp
 *
 * [912] Sort an Array
 *
 * https://leetcode.com/problems/sort-an-array/description/
 *
 * algorithms
 * Medium (62.86%)
 * Total Accepted:    32.5K
 * Total Submissions: 51.6K
 * Testcase Example:  '[5,2,3,1]'
 *
 * Given an array of integers nums, sort the array in ascending order. 
 *
 * Example 1:
 * Input: nums = [5,2,3,1]
 * Output: [1,2,3,5]
 * 
 * Example 2:
 * Input: nums = [5,1,1,2,0,0]
 * Output: [0,0,1,1,2,5]
 *
 * Constraints:
 * 1 <= nums.length <= 50000
 * -50000 <= nums[i] <= 50000
 * 
 * @Category Sort
 * @Idea
 * S1: Count Sort
 * S2: Quick Sort
 * S3: Merge Sort
 */
class Solution {
public:
    // Count Sort T=O(n) S=O(max(n,K))
    vector<int> sortArray1(vector<int>& nums) {
        int n = nums.size(), j = 0;
        vector<int> res(n), count(100001);
        for (int num : nums) { ++count[num + 50000]; }      // 待排序的数做index统计计数,index>=0所以须[-5000,5000]=>[0,10000]
        for (int i = 0; i < count.size(); ++i) {
            while (count[i]-- > 0) {                        // index按小到大顺序将计数>0的数加入结果集
                res[j++] = i - 50000;                       // 加入结果集时必须[0,10000]=>[-5000,5000]恢复后再加
            }
        }
        return res;
    }

    // Quick Sort T=O(lognX) S=O(n)
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
    void quickSort(vector<int>& nums, int start, int end) {
        if (start >= end) { return; }
        int pivot = nums[start], i = start + 1, j = end;    // 二分找pivot
        while (i <= j) {
            if (nums[i] > pivot && nums[j] < pivot) {       // 按pivot来将左边>pivot的和右边<pivot的元素交换
                swap(nums[i++], nums[j--]);
            }
            if (nums[i] <= pivot) { ++i; }
            if (nums[j] >= pivot) { --j; }
        }
        swap(nums[start], nums[j]);                         // 坑:最后一次交换队首和j
        quickSort(nums, start, j - 1);
        quickSort(nums, j + 1, end);
    }
};
