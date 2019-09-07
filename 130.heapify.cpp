/*
 * @lc app=lintcode id=130 lang=cpp
 *
 * [130] Heapify
 *
 * https://www.lintcode.com/problem/heapify/description
 *
 * lintcode
 * Medium (42.00%)
 * Total Accepted:    17215
 * Total Submissions: 40807
 * Testcase Example:  '[3,2,1,4,5]\n'
 *
 * Given an integer array, heapify it into a min-heap array.For a heap array A,
 * A[0] is the root of heap, and for each A[i], A[i * 2 + 1] is the left child
 * of A[i] and A[i * 2 + 2] is the right child of A[i].
 * 
 * 
 */
class Solution {
public:
    void heapify(vector<int>& nums) {
        for (int i = (nums.size() - 1) / 2; i >= 0; --i) {  // 叶子最低不用再下沉,从倒数第二层开始
            shiftDown(nums, i);
        }
    }

    void shiftDown(vector<int>& nums, int idx) {
        int n = nums.size(), child;
        while (2 * idx + 1 < n) {
            child = 2 * idx + 1; // 访问左子
            if (child + 1 < n && nums[child + 1] < nums[child]) {
                child += 1;
            }
            if (nums[idx] <= nums[child]) return;
            // else
            nums[idx] ^= nums[child];
            nums[child] ^= nums[idx];
            nums[idx] ^= nums[child];
            idx = child;
        }
    }
};
