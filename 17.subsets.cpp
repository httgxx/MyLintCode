/*
 * @lc app=lintcode id=17 lang=cpp
 *
 * [17] Subsets
 *
 * https://www.lintcode.com/problem/subsets/description
 *
 * lintcode
 * Medium (29.00%)
 * Total Accepted:    42823
 * Total Submissions: 144185
 * Testcase Example:  '[0]\n'
 * 
 * Given a set of distinct integers, return all possible subsets.
 * Example:
 * Input: [1,2,3]
 * Output:
 * [
 * [3],
 * [1],
 * [2],
 * [1,2,3],
 * [1,3],
 * [2,3],
 * [1,2],
 * []
 * ]
 * 
 * @Category DFS
 * @Idea T=O(2^n) S=O(1)//如果不考虑结果集所占空间
 * 预处理sort input数组,因为需要每个结果subset中元素有序
 * 每个新元素k,对每个已有subnet:先拷贝后加新
 * 如A={1}, subset={[],[1]} => A+2={1,2}, subset={[],[1]}+{[]+2,[1]+2}={[],[1],[2],[1,2]}
 * 
 * 坑 须先排序才能保证最后结果中每个subset里元素有序
 */
class Solution {
public:
    /**
     * @param nums: A set of numbers
     * @return: A list of lists
     */
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> res(1);  // init to {[]}
        sort(nums.begin(), nums.end()); // 若需要最后结果有序
        for (int i = 0; i < nums.size(); ++i) {  // 每个新元素
            int curSize = res.size();  // 坑:必须每次重算因res在不断增大
            for (int j = 0; j < curSize; ++j) {  // 当前每个已有的subset
                res.push_back(res[j]);  // 先拷贝
                res.back().push_back(nums[i]);  // 再加新
            }
        }
        return res;
    }
};
