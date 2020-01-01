/*
 * @lc app=leetcode id=560 lang=cpp
 *
 * [560] Subarray Sum Equals K
 *
 * https://leetcode.com/problems/subarray-sum-equals-k/description/
 *
 * algorithms
 * Medium (43.18%)
 * Total Accepted:    174K
 * Total Submissions: 402.1K
 * Testcase Example:  '[1,1,1]\n2'
 *
 * Given an array of integers and an integer k, you need to find the total
 * number of continuous subarrays whose sum equals to k.
 * 
 * Example 1:
 * Input:nums = [1,1,1], k = 2
 * Output: 2
 *
 * Note:
 * The length of the array is in range [1, 20,000].
 * The range of numbers in the array is [-1000, 1000] and the range of the
 * integer k is [-1e7, 1e7].
 * 
 * @Category 2Sum
 * @Idea 2Sum变种
 * map[子串和值v]=和为v的子串个数n,初始map[0]=1即和为0的子串个数初始为1(空串)
 * 左扫到右,累计前缀和sum,若先前出现过前缀和(sum-k),说明中间部分子串和为sum-(sum-k)=k
 * 每次遇到这种情况就累加已发现的所有具有该和值(sum-k)的子串个数即可 
 */
class Solution {
public:
    // 和为k的子串个数(2sum变种): map[子串和值v]=和为v的子串个数n,初始map[0]=1即和为0的子串个数初始为1(空串)
    // 左扫到右,累计前缀和sum,若先前出现过前缀和(sum-k),说明中间部分子串和为sum-(sum-k)=k
    // 每次遇到这种情况就累加已发现的所有具有该和值(sum-k)的子串个数即可 
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> map; // map[子串和值v]=和为v的子串个数n
        map[0] = 1;                 // 和为0的子串个数初始为1(空串)
        int sum = 0, res = 0;
        for (int num : nums) {
            sum += num;             // 累加前缀和
            res += map[sum - k];    // 若先前出现过前缀和(sum-k),说明中间部分子串和为sum-(sum-k)=k,累加此类子串个数
            ++map[sum];             // 更新子串和对应的子串个数
        }
        return res;
    }
};
