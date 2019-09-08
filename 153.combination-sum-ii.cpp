/*
 * @lc app=lintcode id=153 lang=cpp
 *
 * [153] Combination Sum II
 *
 * https://www.lintcode.com/problem/combination-sum-ii/description
 *
 * lintcode
 * Medium (36.00%)
 * Total Accepted:    19832
 * Total Submissions: 54602
 * Testcase Example:  '[7,1,2,5,1,6,10]\n8\n'
 *
 * Given an array `num` and a number `target`. Find all unique combinations in
 * `num` where the numbers sum to `target`.
 */
class Solution {
public:
    /**
     * @param num: Given the candidate numbers
     * @param target: Given the target number
     * @return: All the combinations that sum to target
     */
    //S: 递归+回溯+去重
    //去重方法: 预处理排序,每次递归前跳过相邻重复候选项
    vector<vector<int>> combinationSum2(vector<int> &nums, int target) {
        vector<int> out;
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());                   // !!!预处理: 排序是为了后面去重!!!
        helper(nums, target, 0, out, res);
        return res;
    }
    void helper(vector<int> &nums, int target, int start, vector<int>& out, vector<vector<int>>& res)
    {
        if (target == 0) { res.push_back(out); return; }  // 达到目标状态,记录结果,终止递归
        for (int i = start; i < nums.size(); ++i) {       // [start,n-1]内每个候选依次来试
            if (nums[i] > target) { return; }             // !!!剪枝:从小到大故若比target大则不必递归
            if (i > start && nums[i] == nums[i - 1]) { continue; }  // !!!去重: 跳过相邻重复候选
            out.push_back(nums[i]);                       // 选(原结果上加,不是拷贝后加)
            helper(nums, target - nums[i], i + 1, out, res);  // 递归(目标状态变+递归起始位置变)
            out.pop_back();                               // 回溯(恢复选前状态)
        }
    }
};
