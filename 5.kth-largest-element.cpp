/*
 * @lc app=lintcode id=5 lang=cpp
 *
 * [5] Kth Largest Element
 *
 * https://www.lintcode.com/problem/kth-largest-element/description
 *
 * lintcode
 * Medium (29.00%)
 * Total Accepted:    38693
 * Total Submissions: 129261
 * Testcase Example:  '1\n[1,3,4,2]'
 *
 * Find K-th largest element in an array.
 * 
 * Example 1:
 * Input: n = 1, nums = [1,3,4,2]
 * Output: 4
 * 
 * Example 2:
 * Input: n = 3, nums = [9,3,2,4,8]
 * Output:4
 * 
 * Challenge: O(n) time, O(1) extra memory.
 * 
 * 
 * @Category TopK  QuickSort / Heap
 * 
 * S1: QuickSort
 * 
 * S2: Heap
 * 
 * 
 */
class Solution {
public:
    /**
     * @param n: An integer
     * @param nums: An array
     * @return: the Kth largest element
     */
    // S1: 快排 T=O(n) S=O(1)
    int kthLargestElement(int k, vector<int> &nums) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int pos = partition(nums, left, right);         // 按pivot分区,使左>=pivot>=右,即pivot归位到降序排序后该在的pos
            if (pos == k - 1) { return nums[pos]; }         // pos正好在第K大,返回pivot (无第0大,第1大=[0],第k大=[k-1])
            if (pos > k - 1) { right = pos - 1; }           // pos在第K大右边,去pos左边递归找第K大,将新pivot归位到新pos
            else { left = pos + 1; }                        // pos在第K大左边,去pos右边递归找第K大,将新pivot归位到新pos
        }
    }
    int partition(vector<int> & nums, int left, int right) {// 按pivot分区=>左>=pivot>=右=>将pivot归位到降序排序后该在的pos
        int pivot = nums[left], l = left + 1, r = right;    // 选最左为pivot,剩下区域最左和最右各站1哨兵
        while (l <= r) {                                    // 循环处理直到2哨兵相遇
            if (nums[l] < pivot && nums[r] > pivot) {       // [l]<pivot<[r]同时满足时,左>=pivot>=右的特性被破坏
                swap(nums[l], nums[r]);                     // 交换2哨兵所在位置的值,修复左>=pivot>=右的特性
            }
            if (nums[l] >= pivot) { ++l; }                  // 先左哨兵一直右走,直到左>=pivot特性被破坏,找到第一个左<pivot
            if (nums[r] <= pivot) { --r; }                  // 再右哨兵一直左走,直到右<=pivot特性被破坏,找到第一个右>pivot
        }
        swap(nums[left], nums[r]);                          // 交换pivot([left])和2哨兵相遇位置r的值[r]
                                                            // 坑:是[r]不是[right]
        return r;                                           // 返回pivot归位处
    }
};
