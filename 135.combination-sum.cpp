/*
 * @lc app=lintcode id=135 lang=cpp
 *
 * [135] Combination Sum
 *
 * https://www.lintcode.com/problem/combination-sum/description
 *
 * lintcode
 * Medium (33.00%)
 * Total Accepted:    29235
 * Total Submissions: 87690
 * Testcase Example:  '[2,3,6,7]\n7'
 *
 * Given a set of candidtate numbers `candidates` and a target number `target`.
 * Find all unique combinations in `candidates` where the numbers sums to
 * `target`.
 * 
 * The **same** repeated number may be chosen from `candidates` unlimited
 * number of times.
 * 
 * 注: 候选中的数字可有重复, 也可被选多次, 组合中数字无序, 要去除重复组合,
 * e.g. 候选[2,2,3],2和3都可以选多次,[2,2,3]和[2,3,2]只能有一个
 * 
 * @Category Subset 递归 回溯
 * @Idea
 * 候选中的某个数字可能之后还会出现, 而且每个候选中的数字都多被选多次, 这样可能会产生重复组合
 * 所以需要先将候选排序, 之后递归时跳过相邻的相同候选数字才能避免输出重复组合方案
 * 
 */
class Solution {
public:
    /**
     * @param candidates: A list of integers
     * @param target: An integer
     * @return: A list of lists of integers
     */
    // S: 递归+回溯 T=O(n!) S=O(2^n)最差情况 
    vector<vector<int>> combinationSum(vector<int> &nums, int target) {
        vector<int> out;
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());                   // 排序是为之后跳过重复候选
        helper(nums, target, 0, out, res);
        return res;
    }
    void helper(vector<int> &nums, int target, int start, vector<int>& out, vector<vector<int>>& res)
    {
        if (target < 0) { return; }                       // 无法达到目标状态,终止递归
        if (target == 0) { res.push_back(out); return; }  // 已经达到目标状态,记录结果,终止递归
        for (int i = start; i < nums.size(); ++i) {       // [start,n-1]内每个候选依次来试
            if (i > start && nums[i] == nums[i - 1]) { continue; }  // 跳过重复候选
            out.push_back(nums[i]);                       // 选
            helper(nums, target - nums[i], i, out, res);  // 递归(目标状态改变,可重复选故start不变
            out.pop_back();                               // 回溯(恢复选前状态)
        }
    }
};
