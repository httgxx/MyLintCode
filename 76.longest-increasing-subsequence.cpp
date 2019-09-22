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
 * Example 1:
 * Input:  [5,4,1,2,3]
 * Output:  3
 * Explanation: LIS is [1,2,3]
 * 
 * Example 2:
 * Input: [4,2,4,5,3,7]
 * Output:  4
 * 
 * Explanation: 
 * LIS is [2,4,5,7]
 * 
 * Challenge: Time complexity O(n^2) or O(nlogn)
 * 
 * @Category DP(按情况叠加比较型)
 * @Ideas
 * S1: // T=O(nlogn) S=O(n) 
 * 最长上升子序列LIS
 * 同长LIS中end越小越可能append新数成为更长LIS,故记录每种长度的LIS的最小end即ends[i]=长度为i的LIS的最小end
 * 每次进新数x,就看它能否让某些长度的LIS的最小end变得更小
 * 若找到可以替换的end, 找到最小的那个替换为x; 若没找到,则直接append到ends末尾,即找到更长的LIS
 * 最后ends的长度也就是最长LIS的长度
 * 注: 若LIS不允许重复数,则ends不允许有重复数;如果LIS允许重复数,则ends允许有重复数
 *    两种情况下都是用a[i]去替换第一个>=a[j]的ends[k]
 * 
 * S2: // T=O(n^2) S=O(n)
 * dp[i]表示以a[i]结尾的LIS长度
 * =以a[i]前面的某个<a[i]的a[k]为结尾的LIS中最长的长度+1
 * =max{dp[k]|k<i且a[k]<a[i]} + 1
 * 初始 dp[0]=1
 * 顺序 i=0~n-1, k=i~i-1
 * 返回 max(dp[i])
 * 注: 若LIS不允许重复数,则ends不允许有重复数,要找a[k]<a[i]
 *     若LIS允许重复数,则ends允许有重复数,要找a[k]<=a[i]
 * 坑: dp[]初始化为1而不是0
 * 坑: 返回max(dp[i])而不是dp[n-1] 因为最长LIS可能是以任1个[i]结尾
 */
class Solution {
public:
    /**
     * @param nums: An integer array
     * @return: The length of LIS (longest increasing subsequence)
     */
    // S1: DP ends[] // T=O(nlogn) S=O(n)
    // 同长LIS中end越小越可能append新数成为更长LIS,故记录每种长度的LIS的最小end即ends[i]=长度为(i+1)的LIS的最小end
    // 每次进新数x,就看它能否让某些长度的LIS的最小end变得更小
    // 若找到可以替换的end, 找到最小的那个替换为x; 若没找到,则直接append到ends末尾,即找到更长的LIS
    // 最后ends的长度也就是最长LIS的长度
    int longestIncreasingSubsequence1(const vector<int> &nums) {
        vector<int> ends;                                       // ends[i]=长度为(i+1)的LIS的最小end
        for (int i = 0; i < nums.size(); ++i) {                 // 每访问一个新数
            int left = 0, right = ends.size();                  // 坑: 必须每次重新计算ends.size(),因为ends可能已变
            while (left < right) {                              // 二分查找ends中第1个>=新数的值
                int mid = left + (right - left) / 2;
                if (ends[mid] < nums[i]) { left = mid + 1; }    // 要找>=新数的最小值,[mid]<新数,不够大,故去右边找更大
                else {  right = mid; }                          // [mid]>=新数符合条件,继续去左边(含mid)找是否有更小的符合条件
            }
            if (right < ends.size()) { ends[right] = nums[i]; } // 若找到,则用新数替换它,使其对应长度的LIS的最小end变得更小(更可能以后形成更长LIS)
            else { ends.push_back(nums[i]); }                   // 若没找到,则加到ends尾,表明发现了更长的LIS,其最小end是新数
        }
        return ends.size();                                     // ends[0]=长度为0+1的LIS的最小end => ends[last]对应长度为last+1=size的LIS
    }
    // S1.1 DP ends[] + lower_bound // T=O(nlogn) S=O(n)
    int longestIncreasingSubsequence(const vector<int> &nums) {
        vector<int> ends;                                       // ends[i]=长度为(i+1)的LIS的最小end
        for (auto a : nums) {                                   // 每访问一个新数
            auto it = lower_bound(ends.begin(), ends.end(), a); // 找到ends中第1个>=新数的值
            if (it == ends.end()) { ends.push_back(a); }        // 若没找到,则加到ends尾,表明发现了更长的LIS,其最小end是新数
            else { *it = a; }                                   // 若找到,则用新数替换它,使其对应长度的LIS的最小end变得更小(更可能以后形成更长LIS)
        }
        return ends.size();                                     // ends[0]=长度为0+1的LIS的最小end => ends[last]对应长度为last+1=size的LIS
    }
};
