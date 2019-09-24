/*
 * @lc app=leetcode id=845 lang=cpp
 *
 * [845] Longest Mountain in Array
 *
 * https://leetcode.com/problems/longest-mountain-in-array/description/
 *
 * algorithms
 * Medium (34.95%)
 * Total Accepted:    21.7K
 * Total Submissions: 62K
 * Testcase Example:  '[2,1,4,7,3,2,5]'
 *
 * Let's call any (contiguous) subarray B (of A) a mountain if the following
 * properties hold:
 * B.length >= 3
 * There exists some 0 < i < B.length - 1 such that B[0] < B[1] < ... B[i-1] <
 * B[i] > B[i+1] > ... > B[B.length - 1]
 * 
 * (Note that B could be any subarray of A, including the entire array A.)
 * 
 * Given an array A of integers, return the length of the longest mountain. 
 * Return 0 if there is no mountain.
 * 
 * Example 1:
 * Input: [2,1,4,7,3,2,5]
 * Output: 5
 * Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
 *
 * Example 2:
 * Input: [2,2,2]
 * Output: 0
 * Explanation: There is no mountain.
 *  
 * Note:
 * 0 <= A.length <= 10000
 * 0 <= A[i] <= 10000
 *
 * Follow up: solve in 1 pass 且 S=O(1)
 * 
 * 
 * 
 */
class Solution {
public:
    // S1: 找上山起点,找山顶,找下山终点,更新最长山长,终点成新起点循环进行
    int longestMountain(vector<int>& A) {
        int res = 0, i = 0, last = A.size() - 1;
        while (i <= last - 2) {                                             // 坑: 最短山长=3 起点至少在倒数第3
            while (i <= last - 2 && A[i] >= A[i + 1]) { ++i; }             // 找上山起点: 跳过所有不增
            int peak = i;
            while (peak <= last - 1 && A[peak] < A[peak + 1]) { ++peak; }  // 找山顶: 统计所有递增
            int j = peak;
            while (j <= last - 1 && A[j] > A[j + 1]) { ++j; }              // 找下山终点: 统计所有递减
            if (i < peak && peak < j) { res = max(res, j - i + 1); }        // 坑: 千万别忘 i<peak<j
            i = j;                                                          // 坑: 千万别忘 i=j
        }
        return res;
    }

    // S
};
