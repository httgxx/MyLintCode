/*
 * @lc app=lintcode id=57 lang=cpp
 *
 * [57] 3Sum
 *
 * https://www.lintcode.com/problem/3sum/description
 *
 * lintcode
 * Medium (24.00%)
 * Total Accepted:    36566
 * Total Submissions: 151360
 * Testcase Example:  '[2,7,11,15]\n\n'
 *
 * Given an array *S* of n integers, are there elements *a*, *b*, *c* in *S*
 * such that `a + b + c = 0`? Find all unique triplets in the array which gives
 * the sum of zero.
 * 
 * Example 1:
 * Input:[2,7,11,15]
 * Output:[]
 * 
 * Example 2:
 * Input:[-1,0,1,2,-1,-4]
 * Output:	[[-1, 0, 1],[-1, -1, 2]]
 * 
 * @Category 2Sum + 剪枝
 * @Idea 2Sum(双指针) + 剪枝
 * T=O(n) S=O(1)
 * 先数组排序小到大
 * 在扫描每个数[i],看剩下的数中能否找到两数和=0-[i]
 * 巧: 剪枝!!!最小值>0或最大值<0都不可能和=0
 * 巧: 只用遍历到倒数第3个数
 * 巧: 剪枝!!!遇到>0停止扫描,因为之后都>0不可能和=0
 * 坑: 跳过重复    
 */
class Solution {
public:
    /**
     * @param numbers: Give an array numbers of n integer
     * @return: Find all unique triplets in the array which gives the sum of zero.
     */
    // 2Sum=0-[i] + 剪枝 T=O(n) S=O(1)
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());                                     // 先从小到大排序 T=O(nlogn)
        if (nums.empty() || nums.back() < 0 || nums.front() > 0) return {}; // 巧: 剪枝!!!最小值>0或最大值<0都不可能和=0
        for (int k = 0; k < nums.size() - 2; ++k) {                         // 巧: 只用遍历到倒数第3个数
            if (nums[k] > 0) { break; }                                     // 巧: 剪枝!!!遇到>0停止扫描,因为之后都>0不可能和=0
            if (k > 0 && nums[k] == nums[k - 1]) { continue; }              // 坑: 跳过重复
            int target = 0 - nums[k], i = k + 1, j = nums.size() - 1;       // 在后面剩下的数中找2Sum
            while (i < j) {                                                 // 双指针法找2Sum=0-[k]
                if (nums[i] + nums[j] == target) {                          //   若两指针和=2Sum
                    res.push_back({nums[k], nums[i], nums[j]});             //     坑: 加3个数(不只是满足2Sum的2个数)入结果集
                    while (i < j && nums[i] == nums[i + 1]) { ++i; }        //     坑: 跳过重复 勿忘i<j
                    while (i < j && nums[j] == nums[j - 1]) { --j; }        //     坑: 跳过重复 勿忘i<j
                    ++i;                                                    //     左右指针内移
                    --j;
                }
                else if (nums[i] + nums[j] < target) { ++i; }               //   若两指针和偏小,左指针右移取更大数
                else { --j; }                                               //   若两指针和偏大,右指针左移取更小数        
            }
        }
        return res;
    }
};
