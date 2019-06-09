/*
 * @lc app=lintcode id=18 lang=cpp
 *
 * [18] Subsets II
 *
 * https://www.lintcode.com/problem/subsets-ii/description
 *
 * lintcode
 * Medium (29.00%)
 * Total Accepted:    29118
 * Total Submissions: 98138
 * Testcase Example:  '[0]\n'
 *
 * Given a collection of integers that might contain duplicates, *nums*, return
 * all possible subsets (the power set).
 * 
 * Input: [1,2,2]
 * Output:
 * [
 * [2],
 * [1],
 * [1,2,2],
 * [2,2],
 * [1,2],
 * []
 * ]
 * 
 * @Category DFS
 * @Idea 和Subset I区别: 需要去重
 * S1: 一次性处理重复元素
 * 
 * S2: 重复元素时跳过基础子集 
 * A={1}, subset={[],[1]} => lastSize=0, curSize=2
 * A+2={1,2}, subset={[],[1]} + {[]+2,[1]+2} => lastSize=2, curSize=4
 * A+2={1,2,2}, subset={[],[1],[2],[1,2]} + {[2]+2,[1,2]+2} 
 * 前lastSize个基础子集不能加新否则会重([]+2,[1]+2),只能为坐标从lastSize开始的子集加新([2]+2,[1,2]+2)
 * 
 * 坑 先处理特例空input
 * 坑 用last和lastSize来标记无重的最后一个元素及其基础子集个数
 * 坑 初始last=a[0],lastSize=1而不是0
 */
class Solution {
public:
    /**
     * @param nums: A set of numbers.
     * @return: A list of lists. All valid subsets.
     */
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        vector<vector<int>> res(1);
        int n = nums.size();
        if (n == 0) { return res; }  // 特例

        sort(nums.begin(), nums.end());
        for (int i = 0; i < n;) {  // 坑:不在此处++i
            int curSize = res.size();
            do{
                for (int j = 0; j < curSize; j++){
                    res.push_back(res[j]);
                    res[j].push_back(nums[i]);
                }  
                i++;  // 坑: 在此处++i因为可以一次性处理重复元素
            } while (i < n && nums[i - 1] == nums[i]);  // 坑:一次性处理重复元素
        }
        return res;
    }

    vector<vector<int>> subsetsWithDup2(vector<int> &nums) {
        vector<vector<int>> res(1);  // init to {[]}
        if (nums.empty()) { return res; }  // 坑: 特例
        
        sort(nums.begin(), nums.end());  // 最后结果中每个subset的元素须有序
        int last = nums[0], lastSize = 1;  // 上次无重复的最后一个元素以及其subset个数
                                           // 坑: lastSize = 1而不是0
        for (int i = 0; i < nums.size(); ++i) {
            if (last != nums[i]) {  // 不同前时更新最后一个元素last以及其子集个数lastSize
                last = nums[i];
                lastSize = res.size();
            }
            int curSize = res.size();
            for (int j = curSize - lastSize; j < curSize; ++j) {  // 不同前curSize==lastSize即j从0开始
                                                                  // 同前lastSize部分不能再加新否则会重
                res.push_back(res[j]);
                res.back().push_back(nums[i]);
            }
        }
        return res;
    }
};
