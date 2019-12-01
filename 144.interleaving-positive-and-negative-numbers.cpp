/*
 * @lc app=lintcode id=144 lang=cpp
 *
 * [144] Interleaving Positive and Negative Numbers
 *
 * https://www.lintcode.com/problem/interleaving-positive-and-negative-numbers/description
 *
 * lintcode
 * Medium (25.00%)
 * Total Accepted:    7806
 * Total Submissions: 30133
 * Testcase Example:  '[-33,-19,30,26,21,-9]'
 *
 * Given an array with positive and negative integers. Re-range it to interleaving with positive and negative integers.
 * 
 * Example 1
 * Input : [-1, -2, -3, 4, 5, 6]
 * Outout : [-1, 5, -2, 4, -3, 6]
 * Explanation :  any other reasonable answer
 * 
 * @Category array swap + 2pointers
 * @Idea 正负元素交换+双指针
 * 统计正数和负数个数,正数多则正数先,负数多则负数先
 * 同向双指针分别指向当前正数/负数所在位置,每次递进2个单位检查是否还依然是正数/负数
 * 若不是则交换指针使得正负交换来满足当前所需的正负性,同时继续递进2各单位继续检查
 * T=O(n) S=O(n)
 */
class Solution {
public:
    /*
     * @param A: An integer array.
     * @return: nothing
     * @Idea 正负元素交换+双指针
     * 统计正数和负数个数,正数多则正数先,负数多则负数先
     * 同向双指针分别指向当前正数/负数所在位置,每次递进2个单位检查是否还依然是正数/负数
     * 若不是则交换指针使得正负交换来满足当前所需的正负性,同时继续递进2各单位继续检查
     * T=O(n) S=O(n)
     */
    void rerange(vector<int> &A) {
        int posCnt = 0, negCnt = 0;       
        for (auto num : A) {                                            // 统计正负数个数
            if (num > 0) { ++posCnt; }
            else if (num < 0) { ++negCnt; }
        }
        int posIndex = posCnt > negCnt ? 0 : 1;                         // 多的数先放Idx=0
        int negIndex = 1 - posIndex;
        int n = A.size();
        while (posIndex < n && negIndex < n) {
            while (posIndex < n && A[posIndex] > 0) { posIndex += 2; }  // 找到下一个该为正但实为负的index1
            while (negIndex < n && A[negIndex] < 0) { negIndex += 2; }  // 找到下一个该为负但实为正的index2
            if (posIndex < n && negIndex < n) {                         // 交换index1和index2满足双方正负性
                swap(A[posIndex], A[negIndex]);
                posIndex += 2;                                          // 坑:同时继续递进2
                negIndex += 2;
            }
        }
    }
};
