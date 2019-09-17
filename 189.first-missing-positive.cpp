/*
 * @lc app=lintcode id=189 lang=cpp
 *
 * [189] First Missing Positive
 *
 * https://www.lintcode.com/problem/first-missing-positive/description
 *
 * lintcode
 * Medium (24.00%)
 * Total Accepted:    13015
 * Total Submissions: 53223
 * Testcase Example:  '[]\n'
 *
 * Given an **unsorted** integer array, find the first **missing** positive
 * integer.
 * 
 * Example 1:
 * Input: [1,2,0]
 * Output: 3
 * 
 * Example 2:
 * Input: [3,4,-1,1]
 * Output: 2
 * 
 * Example 3:
 * Input: [7,8,9,11,12]
 * Output: 1
 * 
 * Note: Your algorithm should run in O(n) time and uses constant extra space.
 * 
 * S1: 扫描数组看是否A[i]=i+1,如A[0]=1,A[1]=2,否则如A[i]=j+1则将A[i]和A[j]交换使A[j]=j+1
 *     交换后若任然有A[i]!=i+1,则继续将A[i]=x和A[x]交换直到A[i]=i+1, 或
 *     然后再从头扫描一次数组看哪一个位置i上不是i+1,则i就是最小缺的正数     // T=O(n) S=O(1)
 * S2: Set存所有数字并找出max,从1到max找最小缺的正数,1到max都有则返回max+1 // T=O(n) S=O(n)
 * 
 */
class Solution {
public:
    /**
     * @param A: An array of integers
     * @return: An integer
     */
    // S1: 从左扫到右,若A[i-1]=i继续,否则交换A[i-1]=j和A[j-1]使得A[j-1]=j
    // 再扫一遍找最小的A[i-1]!=i则i即为最小缺失正数,若1~n都不缺则最小缺失n+1
    // T=O(n) S=O(1)
    int firstMissingPositive(vector<int> &nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n &&  // 只处理/交换1~n,其他的数会被留在/交换到缺失数字该待的位置上
                   nums[nums[i] - 1] != nums[i]) { // expect A[i-1]=i
                swap(nums[i], nums[nums[i] - 1]);  // 交换使得A[j-1]=j,交换后下一轮while继续检查换到i位置的新A[i]
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (nums[i - 1] != i) { return i; }     // 找到最小缺失正数
        }
        return n + 1;                               // 1~n都不缺,则最小缺n+1
    }

    // S2: Set存所有数字并找出max,从1到max找最小缺的正数,1到max都有则返回max+1
    // T=O(n) S=O(n)
    int firstMissingPositive2(vector<int>& nums) {
        int mx = 0;
        unordered_set<int> s;
        for (int num : nums) {
            if (num <= 0) { continue; }     // 坑: 记得跳过负数!!
            s.insert(num);
            mx = max(mx, num);              // 用set去重和找最大正数
        }
        for (int i = 1; i <= mx; ++i) {     // 从1~max找最小缺失正数
            if (!s.count(i)) { return i; }  // 找到最小缺失正数
        }
        return mx + 1;                      // 1~max都有则最小缺max+1
    }

};
