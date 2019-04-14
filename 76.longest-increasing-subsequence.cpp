/*
 * @lc app=lintcode id=76 lang=cpp
 *
 * [76] Longest Increasing Subsequence
 *
 * https://www.lintcode.com/problem/longest-increasing-subsequence/description
 *
 * lintcode
 * Medium (33.00%)
 * Total Accepted:    25572
 * Total Submissions: 77383
 * Testcase Example:  '[]'
 *
 * Given a sequence of integers, find the longest increasing subsequence (LIS).
 * You code should return the length of the LIS.
 * 
 * @Category DP
 * @Ideas
 * DP // T=O(n) S=T(n)
 * 最长上升子序列LIS
 * 相同长度的LIS末尾越小越有可能append新的更大数形成更长LIS
 * 记录每种长度的LIS的最小末尾数: ends[i]=所有长度为i的LIS的末尾的最小值 
 * 每次访问到新数,用它去替换ends中第1个>=新数的LIS末尾
 * 
 * 注: 若LIS不允许重复数,则ends不允许有重复数; 如果LIS允许重复数,则ends允许有重复数
 *     两种情况下都是用a[i]去替换第一个ends[k]>=a[j] 
 */
class Solution {
public:
    /**
     * @param nums: An integer array
     * @return: The length of LIS (longest increasing subsequence)
     */
    int longestIncreasingSubsequence(vector<int> &nums) {
        vector<int> ends; 
        for (int i = 0; i < nums.size(); ++i) {
            int left = 0, right = ends.size();  // ends可能已增长故每次重算right
            // case1:[i]>当前最长子序列最小末尾,即可append形成更长上升子序列
            if (right == 0 || nums[i] > ends[right - 1]) {
               ends.push_back(nums[i]);
            }
            // case2:[i]<=当前最长子序列最小末尾,即不能append形成更长上升子序列
            // 须降低可降低的最长上升子序列的最小末尾中最大的一个            
            // 即二分找到ends中第一个(最小的)>=[i]的值,并替换成[i]
            else { //ends中至少还有1个数 即left<=right
              while (left < right) { //至少还剩2个数
                int mid = left + (right - left) / 2;
                if (ends[mid] < nums[i]) {
                    left = mid + 1;  // [mid]太小 去右边找更大
                }
                else {
                    right = mid;  // [mid]符合条件,去左边(包含mid)找更小
                }
              }
              ends[right] = nums[i];  // 肯定有1个>[i]所以只可能是这个
            }
        }
        return ends.size();
    }
};
