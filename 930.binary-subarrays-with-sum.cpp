/*
 * @lc app=leetcode id=930 lang=cpp
 *
 * [930] Binary Subarrays With Sum
 *
 * https://leetcode.com/problems/binary-subarrays-with-sum/description/
 *
 * algorithms
 * Medium (39.94%)
 * Total Accepted:    14.4K
 * Total Submissions: 35.5K
 * Testcase Example:  '[1,0,1,0,1]\n2'
 *
 * In an array A of 0s and 1s, how many non-empty subarrays have sum S?
 * 
 * Example 1:
 * Input: A = [1,0,1,0,1], S = 2
 * Output: 4
 * Explanation: 
 * The 4 subarrays are below:
 * [1,0,1, , ]
 * [1,0,1,0, ]
 * [ ,0,1,0,1]
 * [ , ,1,0,1]
 * 
 * Note:
 * A.length <= 30000
 * 0 <= S <= A.length
 * A[i] is either 0 or 1.
 * 
 * @Category 2Sum
 * @Idea 2Sum变种
 * S1: map[子串和值v]=和为v的子串个数n,初始map[0]=1即和为0的子串个数初始为1(空串)
 * 左扫到右,累计前缀和sum,若先前出现过前缀和(sum-k),说明中间部分子串和为sum-(sum-k)=k
 * 每次遇到这种情况就累加已发现的所有具有该和值(sum-k)的子串个数即可 
 */
class Solution {
public:
    // S1: 方法同LC560-sumarray sum to k(2sum变种)
    int numSubarraysWithSum(vector<int>& A, int S) {
        unordered_map<int, int> map;    // map[子串和v]=和为v的子串个数n
        map[0] = 1;                     // 初始化: 和为0的子串个数初始为1(空串)
        int sum = 0, res = 0;           // 前缀和sum,子串个数res
        for (int a : A) {               // 左扫到右
            sum += a;                   // 累加前缀和
            res += map[sum - S];        // 若先前出现过前缀和(sum-S),说明中间部分子串和为sum-(sum-S)=S,累加此类子串个数
            ++map[sum];                 // 更新前缀和sum的子串个数
        }
        return res;
    }
};
