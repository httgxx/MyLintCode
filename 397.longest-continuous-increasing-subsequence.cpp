/*
 * @lc app=lintcode id=397 lang=cpp
 *
 * [397] Longest Continuous Increasing Subsequence
 *
 * https://www.lintcode.com/problem/longest-continuous-increasing-subsequence/description
 *
 * lintcode
 * Easy (32.00%)
 * Total Accepted:    14195
 * Total Submissions: 43541
 * Testcase Example:  '[5,4,2,1,3]\n'
 *
 * Give an integer array，find the longest increasing continuous subsequence in
 * this array.
 * An increasing continuous subsequence:
 * - Can be from right to left or from left to right.
 * - Indices of the integers in the subsequence should be continuous.
 * 
 * @Category DP(按情况叠加比较型),单调性
 * @Ideas
 * DP //T=O(n) S=O(1)
 * 最长单调递增/单调递减子串: 从左到右两两比较,每次单调性变化时候更新最长单调子串长度
 * 如果继续单调则对应单调子串长度+1,如果不在继续单调则对应单调子串长度=1
 * 坑: 题目说左到右或者右到左单调递增 故也要考虑单调递减子串长度
 * 坑: 得先处理size<2不够形成单调子串的特例
 * 坑: i从1而不是0开始循环处理
 */
class Solution {
public:
    /**
     * @param A: An array of Integer
     * @return: an integer
     */
    int longestIncreasingContinuousSubsequence(vector<int> &A) {
        int n = A.size();
        if (n < 2) return n;  // 特例:不够长
        
        int incrLen = 1, descLen = 1, maxLen = 1;  // 递增子串长度,递减子串长度
        for (int i = 1; i < n; ++i) {  // i从1开始
            if (A[i] > A[i - 1]) { ++incrLen; }  // 发现单调递增,递增子串长+1
            else { incrLen = 1; }  // 不再单调递增,重置递增子串长为1
            
            if (A[i] < A[i - 1]) { ++descLen; }  // 发现单调递减,递减子串长+1
            else { descLen = 1; }  // 不再单调递减,重置递减子串长为1
            
            maxLen = max(maxLen, max(incrLen, descLen));
        }
        return maxLen;
    }
};
