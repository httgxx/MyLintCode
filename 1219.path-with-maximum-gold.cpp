/*
 * @lc app=leetcode id=1219 lang=cpp
 *
 * [1219] Path with Maximum Gold
 *
 * https://leetcode.com/problems/path-with-maximum-gold/description/
 *
 * algorithms
 * Medium (61.67%)
 * Total Accepted:    9.3K
 * Total Submissions: 15.1K
 * Testcase Example:  '[[0,6,0],[5,8,7],[0,9,0]]'
 *
 * In a gold mine grid of size m * n, each cell in this mine has an integer
 * representing the amount of gold in that cell, 0 if it is empty.
 * 
 * Return the maximum amount of gold you can collect under the conditions:
 * Every time you are located in a cell you will collect all the gold in that
 * cell.
 * From your position you can walk one step to the left, right, up or down.
 * You can't visit the same cell more than once.
 * Never visit a cell with 0 gold.
 * You can start and stop collecting gold from any position in the grid that
 * has some gold.
 * 
 * Example 1:
 * Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
 * Output: 24
 * Explanation:
 * [[0,6,0],
 * ⁠[5,8,7],
 * ⁠[0,9,0]]
 * Path to get the maximum gold, 9 -> 8 -> 7.
 * 
 * Example 2:
 * Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
 * Output: 28
 * Explanation:
 * [[1,0,7],
 * ⁠[2,0,6],
 * ⁠[3,4,5],
 * ⁠[0,3,0],
 * ⁠[9,0,20]]
 * Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.
 *
 * Constraints: 
 * 1 <= grid.length, grid[i].length <= 15
 * 0 <= grid[i][j] <= 100
 * There are at most 25 cells containing gold.
 * 
 * @Category DFS
 * @Idea DFS
 * 注:题目给出condition: grid最大15x15,最多25个cell有金子,每个cell最多100金,所以直接DFS
 * 
 */
class Solution {
public:
    // DFS 递归+回溯
    // 设cell值为0(没金子)来标记访问过
    // T=O(4*3^n)=O(4*3^25) S=O(n)=O(25) n=含有金子的cell数目(根据题意n<=25) 
    int getMaximumGold(vector<vector<int>>& g) {
        int res = 0;
        for (int i = 0; i < g.size(); ++i) {
            for (int j = 0; j < g[0].size(); ++j) {
                res = max(res, dfs(g, i, j));
            }
        }
        return res;
    }
    int dfs(vector<vector<int>>& g, int i, int j) {
        vector<int> dirs = {0, 1, 0, -1, 0};
        if (i < 0 || i >= g.size() || i < 0 || j >= g[0].size() || g[i][j] == 0) {
            return 0;                                               // 若出界或没金则返0
        }
        int res = 0, origin = g[i][j];
        g[i][j] = 0;                                                // 标记位访问过(没金子)
        for (int k = 0; k < 4; ++k) {                               // 访问各邻居
            res = max(res, dfs(g, i + dirs[k], j + dirs[k + 1]));   // 递归子,更新max
        }
        g[i][j] = origin;                                           // 回溯,去掉访问标记  
        return res + origin;
    }
};
