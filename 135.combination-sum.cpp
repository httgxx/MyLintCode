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
 * 条件: 候选集可有重复数字, 每个候选项可选多次
 * 要求: 结果集必须无重复
 * e.g. 候选[2,2,3],2和3都可以选多次,[2,2,3]和[2,3,2]只能有一个
 * 
 * @Category Subset 递归+回溯+去重组合
 * @Idea
 * 候选中的某个数字可能之后还会出现, 而且每个候选中的数字都多被选多次, 这样可能会产生重复组合
 * 所以需要先将候选排序, 之后递归时跳过相邻的相同候选数字才能避免输出重复组合方案
 * 每个候选项可选多次, 所以下一层递归还是从当前候选项开始, 新start=i
 * 
 * 坑: 答案组合去重: 预处理排序候选数,每次递归前跳过相邻重复候选
 * 坑: 排序预处理方便后面剪枝: 一旦候选数>target则不用再递归下去
 * 坑: 每个候选项可选多次: 下一层递归的候选项起始位置和当前层一样(start=i)
 */
class Solution {
public:
    /**
     * @param candidates: A list of integers
     * @param target: An integer
     * @return: A list of lists of integers
     */
    // S1: 递归+回溯 去重方法: 预处理排序重复候选
    vector<vector<int>> combinationSum1(vector<int> &nums, int target) {
        vector<int> out;
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());                  // 预处理: 去除排序并重复候选      
        vector<int> uniqueNums;
        for (int i = 0; i < nums.size(); ++i) {
            if (i == 0 || nums[i] != nums[i - 1]) {
                uniqueNums.push_back(nums[i]);
            }
        }
        dfs(uniqueNums, target, 0, out, res);
        return res;
    }
    void dfs(vector<int> &nums, int target, int start, vector<int>& out, vector<vector<int>>& res)
    {
        if (target < 0) { return; }                       // 无法达到目标状态,终止递归
        if (target == 0) { res.push_back(out); return; }  // 已经达到目标状态,记录结果,终止递归
        for (int i = start; i < nums.size(); ++i) {       // [start,n-1]内每个候选依次来试
            if (nums[i] > target) { return; }             // 剪枝: 从小到大故遇到比target大的不用往下递归了
            out.push_back(nums[i]);                       // 选
            dfs(nums, target - nums[i], i, out, res);     // 递归(目标状态改变,可重复选故start不变
            out.pop_back();                               // 回溯(恢复选前状态)
        }
    }
    
    // S2: 递归+回溯 去重方法: 排序重之后跳过相邻的重复候选
    vector<vector<int>> combinationSum(vector<int> &nums, int target) {
        vector<int> out;
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());                   // !!!预处理: 排序(此处不用去除重复候选)
        helper(nums, target, 0, out, res);
        return res;
    }
    void helper(vector<int> &nums, int target, int start, vector<int>& out, vector<vector<int>>& res)
    {
        if (target == 0) { res.push_back(out); return; }  // 达到目标状态,记录结果,终止递归
        for (int i = start; i < nums.size(); ++i) {       // [start,n-1]内每个候选依次来试
            if (nums[i] > target) { return; }             // !!!剪枝1: 从小到大故遇到比target大的则不必再递归
            if (i > start && nums[i] == nums[i - 1]) { continue; }  // !!!去重:跳过相邻重复数
                                                                    // 注意:若无重复候选则不需要这一步
                                                                    // 若每个候选只能选一次则一定不要这一步
            out.push_back(nums[i]);                       // 选(原结果上加,不是拷贝后加)
            helper(nums, target - nums[i], i, out, res);  // 递归(目标状态改变,可重复选故start不变
            out.pop_back();                               // 回溯(恢复选前状态)
        }
    }
};
