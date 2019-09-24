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
 * @Category 单调性
 * @Idea T=O(n) S=O(1) 
 * S1: 找上山起点,找山顶,找下山终点,更新最长山长,再从下山终点作为新起点,重复进行
 * S2: up=上山长,down=下山长,到山底(down&&[i]>[i-1])或遇到平地([i]==[i-1])时清零up和down,
 *     上山([i]>[i-1])则++up,下山([i]<[i-1])则++down, up>0&&down>0时才用(up+down+1)更新res
 * 
 * 坑: 从[1]而不是[0]开始,因为要查是否上山要和前一个比
 * 坑: 若到山底(down时发现开始递增)或遇平地,则清零up和down
 * 坑: 在上山和下山的过程中不断更新最长山长,更新要用(up+down+1山顶)
 */
class Solution {
public:
    // S1: 找上山起点,找山顶,找下山终点,更新最长山长,再从下山终点作为新起点,重复进行
    // T=O(n) S=O(1)
    int longestMountain1(vector<int>& A) {
        int res = 0, i = 0, last = A.size() - 1;
        while (i <= last - 2) {                                             // 坑: 最短山长=3 起点至少在倒数第3
            while (i <= last - 2 && A[i] >= A[i + 1]) { ++i; }              // 找上山起点: 跳过所有不增
            int peak = i;
            while (peak <= last - 1 && A[peak] < A[peak + 1]) { ++peak; }   // 找山顶: 统计所有递增
            int j = peak;
            while (j <= last - 1 && A[j] > A[j + 1]) { ++j; }               // 找下山终点: 统计所有递减
            if (i < peak && peak < j) { res = max(res, j - i + 1); }        // 坑: 千万别忘 i<peak<j
            i = j;                                                          // 坑: 千万别忘 i=j
        }
        return res;
    }

    // S2: 用up和down分别记录上山和下山的长度,遇到平地或者下到山底则清零up和down,若up和down都>0则用up+down更新最长山长
    // T=O(n) S=O(1)
    int longestMountain(vector<int>& A) {
        int res = 0, up = 0, down = 0, n = A.size();
        for (int i = 1; i < n; ++i) {                               // 坑: 从[1]而不是[0]开始,因为要查是否上山要和前一个比
            if ((down && A[i - 1] < A[i]) || (A[i - 1] == A[i])) {  // 若到山底(down时发现开始递增)或遇平地,则清零up和down
                up = down = 0;
            }
            if (A[i - 1] < A[i]) { ++up; }                          // 否则, 要么在上山, 更新up
            if (A[i - 1] > A[i]) { ++down; }                        // 要么在下山, 更新down
            if (up > 0 && down > 0) res = max(res, up + down + 1);  // 在上山和下山的过程中不断更新最长山长 // 坑: +1算山顶
        }
        return res;
    }
};
