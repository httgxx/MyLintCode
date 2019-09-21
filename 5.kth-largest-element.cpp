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
 * @Category TopK  QuickSort / Heap
 * 
 * S1: QuickSort快排变体 T=O(n) S=O(1) 
 * 找第K大,则在从大到小倒序数列中(K-1)位置上 (无第0大,第1大=[0],第k大=[k-1])
 * 注: 快排即全部都排时avg T=O(nlogn) 但这里只找第K大而不用全部都排序,每次只用去左子区或者右子区递归
 *     故时间复杂度T=O(1+n/2+n/4+...)=O(n)
 * 
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
    // S1: 快排变体 T=O(n) S=O(1) 
    //     找第K大,则在从大到小倒序数列中(K-1)位置上 (无第0大,第1大=[0],第k大=[k-1])
    // 注: 快排即全部都排时avgT=O(nlogn) 但这里只找第K大而不用全部都排序,每次只用去左子区或者右子区递归
    //     T=O(1+n/2+n/4+...)=O(n)
    int kthLargestElement(int k, vector<int> &nums) {       // 找第K大,则在从大到小倒序数列中(K-1)位置上 (无第0大,第1大=[0],第k大=[k-1])
        int left = 0, right = nums.size() - 1;              
        while (true) {                                      // 注: 不用全部都排序,每次只用去1个子区递归T=O(1+n/2+n/4+...=n)
            int pos = partition(nums, left, right);         // 按pivot分区,使左>=pivot>=右,即pivot归位到降序排序后该在的pos
            if (pos == k - 1) { return nums[pos]; }         // pos正好在第K大,返回pivot
            if (pos > k - 1) { right = pos - 1; }           // pos在第K大右边,去pos左边递归找第K大,将新pivot归位到新pos
            else { left = pos + 1; }                        // pos在第K大左边,去pos右边递归找第K大,将新pivot归位到新pos
        }
    }
    // S1.1: 快排写法1 T=O(n) S=O(1)
    int partition(vector<int> & nums, int left, int right) {// 按pivot分区=>左>=pivot>=右=>将pivot归位到降序排序后该在的pos
        if (left == right) { return left; }                 // 特例: 单个数不用排
        int pivot = nums[left], l = left, r = right;        // 选最左为pivot,包括pivot在内的区域内进行扫描
        while(l != r) {                                     // 从左右两边交替扫描，直到左右相遇
            while(r > l && nums[r] <= pivot) { --r; }       // 从右往左扫,找到第1个比pivot小的
            swap(nums[l], nums[r]);                         // 找到后与左指针的值交换  // 坑: swap([l]],[r])而不是[l]=[r]
            while(l < r && nums[l] >= pivot) { ++l; }       // 从左往右扫,找到第一个比pivot小的
            swap(nums[l], nums[r]);                         // 找到后与右指针的值交换  // 坑: swap([l]],[r])而不是[l]=[r]
        }
        nums[r] = pivot;                                    // 将pivot归位(到排序后该在的位置)
        return r;                                           // 返回pivot最终的位置
    }
    // S1.2 快排写法2(简洁但不好懂!!!) T=O(n) S=O(1)
    int partition1(vector<int> & nums, int left, int right){// 按pivot分区,左>=pivot>=右,将pivot归位到降序排序后该在的pos
        //if (left == right) { return left; }               // 特例: 单个数不用排 // 以下代码已处理此特例
        int pivot = nums[left], l = left + 1, r = right;    // 选最左为pivot,剩下区域最左和最右各站1哨兵
        while (l <= r) {                                    // 循环处理直到2哨兵第一次交错
            if (nums[l] < pivot && nums[r] > pivot) {       // [l]<pivot<[r]同时满足时,左>=pivot>=右的特性被破坏
                swap(nums[l], nums[r]);                     // 交换2哨兵所在位置的值,修复左>=pivot>=右的特性
            }                                               // 注: 同时满足条件才交换,避免了[l]==[r]时没必要的交换
            if (nums[l] >= pivot) { ++l; }                  // 先左哨兵一直右走,直到左>=pivot特性被破坏,找到第一个左<pivot
            if (nums[r] <= pivot) { --r; }                  // 再右哨兵一直左走,直到右<=pivot特性被破坏,找到第一个右>pivot
                                                            // 注: 两比较都带=,这样若有同pivot的值,左右哨兵都会跳过
                                                            // 注: 每次两个哨兵都只走1步,这样第一次交错就会终止循环
        }                                                   
        swap(nums[left], nums[r]);                          // 最后交换pivot([left])和2哨兵相遇位置r的值[r] 坑:不是[right]
                                                            // 极端情况:如11,最终r移到最左端,pivot和自己交换,也不会出错
        return r;                                           // 返回pivot交换后的最终位置,即排序后该在的位置
    }
};
