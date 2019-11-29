/*
 * @lc app=lintcode id=1103 lang=cpp
 *
 * [1103] Split Array into Consecutive Subsequences
 *
 * https://www.lintcode.com/problem/split-array-into-consecutive-subsequences/description
 *
 * lintcode
 * Medium (51.00%)
 * Total Accepted:    448
 * Total Submissions: 877
 * Testcase Example:  '[1,2,3,3,4,5]'
 *
 * Given an integer array `nums`. You need to split `nums` into several (at least 1) subsequences, 
 * where each subsequence contains at least 3 consecutive integers.
 * Return whether you can make such a split.
 * 
 * Note:
 * nums.length will be in the range of [1, 10000].
 * nums has been sorted in ascending order and may contain duplicates.
 * A legitimate subsequence can only consist of consecutive elements and cannot contain duplicate elements.
 * 
 * Example 1:
 * Input: [1,2,3,3,4,5]
 * Output: True
 * Explanation: You can split them into two subsequences: 
 *  [1, 2, 3]
 *  [3, 4, 5]
 * 
 * Example 2:
 * Input: [1,2,3,3,4,4,5,5]
 * Output: True
 * Explanation: You can split them into two subsequences: 
 *  [1, 2, 3, 4, 5]
 *  [3, 4, 5]
 * 
 * Example 3:
 * Input: [1,2,3,4,4,5]
 * Output: False
 * Explanation: We can't split them into several legal subsequences.
 * 
 * @Category 数学 不间断的连续子区间
 * @Idea 数学 不间断的连续子区间
 * 数组是否能分割成>=1个不间断的长度>=3的连续子区间
 * 类似手里的牌须全是至少3连顺的顺子段,如[1,2,3,7,8,9]=>[1,2,3],[7,8,9]
 * 注意前面出现的数字之后可再用,如[1,2,2,3,3,4]=>[1,2,3][2,3,4]
 * 思路: // T=O(n) S=O(n)
 * - freq[数字]=当前出现次数
 * - canAppend[数字]=可挂接的当前连续子区间个数
 * 先左扫到右,统计freq[i],此时对每个i都有freq[i]>0且need[i]=0 
 * 再左扫到右,对每个[i]:
 *   若freq[i]>0且canAppend[i]=0且freq[i+1]>0且freq[i+2]>0, 则[i]可造新3连顺[[i],[i+1],[i+2]]
 *     所以
 *       提前预支[i+1]和[i+2], 即--freq[i+1]和--freq[i+2]
 *       标明可挂接[i+3],      即++canAppen[i+3]
 *       减少[i]的出现次数,    即--freq[i]
 *   若freq[i]>0且canAppend[i]>0, 则[i]可挂接之前某连续子区间
 *     所以
 *       减少可挂接的连续子区间数, 即--canAppend[i]
 *       标明可挂接[i+1],         即++canAppen[i+1]
 *       减少[i]的出现次数,       即--freq[i]
 *   若freq[i]=0, 则[i]已被提前预支去造顺子,跳过
 */
class Solution {
public:
    /**
     * @param nums: a list of integers
     * @return: return a boolean
     */
    // 手里的牌须全是至少3连顺的顺子段,且相邻的两段顺子间必须有重叠(即前段顺子最大数须>=后段顺子最小数)
    // 如[1,2,3,5,6,7]不行,因为[1,2,3]和[5,6,7]之间断了
    // 注意前面出现的数字可以之后再用,如[1,2,2,3,3,4]=>[1,2,3][2,3,4]
    // T=O(n) S=O(n)
    bool isPossible(vector<int> &nums) {
        unordered_map<int, int> freq, canAppend;
        for (auto num : nums) { ++freq[num]; }  // 统计每个数字出现频率
        for (auto num : nums) {
            if (freq[num] == 0 ) { continue; }  // 若num已经被预支去造新3连顺,故跳过
            if (canAppend[num] > 0) {           // 若num没被预支但可挂接当前某连续子区间
                --canAppend[num];               //    挂接num 
                ++canAppend[num + 1];           //    标明num+1可挂接当前某连续子区间 // 可>=3连顺
            }
            else if (freq[num + 1] > 0 &&       // 若num可以和num+1,num+2建新3连胜
                     freq[num + 2] > 0) {
                --freq[num + 1];                //    预支num+1建新3连胜
                --freq[num + 2];                //    预支num+2建新3连胜
                ++canAppend[num + 3];           //    标明num+3可挂接当前某某连续子区间
            }
            else { return false; }              // 若num不属于3连顺,返回false

            --freq[num];                        // 坑: 千万别忘!!!
        }

        return true;                            // 每个数字都在某个>=3连顺里
    }
};
