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
        int posIdx = posCnt > negCnt ? 0 : 1, negIdx = 1 - posIdx;      // 多的数先放
        int n = A.size();
        while (posIdx < n && negIdx < n) {
            while (posIdx < n && A[posIdx] > 0) { posIdx += 2; }        // 找到下一个该为正但实为负的位置1
            while (negIdx < n && A[negIdx] < 0) { negIdx += 2; }        // 找到下一个该为负但实为正的位置2
            if (posIdx < n && negIdx < n) {swap(A[posIdx], A[negIdx]);} // 交换位置1和2使两个正反性都反转
        }
    }
};
