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
 * @Category DFS+backtrack
 * @Idea DFS 递归+回溯
 * 注:题目给出condition: grid最大15x15,最多25个cell有金子,每个cell最多100金,所以直接DFS
 * T=O(4*3^n)=O(4*3^25) S=O(n)=O(25) n=含有金子的cell数目<=25
 * - main()
 * for(i=0~m-1)
 *    for(j=0~n-1)
 *       res = max(res, dfs(g, i, j));
 * return res
 * - dfs(g,i,j)
 *   if(出界或没金g[i][j]==0) return 0
 *   origin=g[i][j]     // 巧:标记为访问过(没金子)
 *   next=0
 *   for(上/下/左/右邻居) next=max(next,dfs(邻居))
 *   g[i][j]=origin     // 回溯(取消标记)
 *   return origin+next // 坑:勿忘+origin
 */
class Solution {
public:
    // DFS 递归+回溯
    // 设cell值为0(没金子)来标记访问过
    // T=O(4*3^n)=O(4*3^25) S=O(n)=O(25) n=含有金子的cell数目(根据题意n<=25) 
    int getMaximumGold1(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size(), ans = 0;
        function<int(int, int)> dfs = [&](int x, int y) {
            if (x < 0 || x >= m || y < 0 || y >= n || g[x][y] == 0) return 0;
            int c = 0;
            swap(c, g[x][y]);   // g[x][y]=0标记[x,y]为已经访问过(没金子)
            int r = c + max({dfs(x - 1, y), dfs(x + 1, y), dfs(x, y - 1), dfs(x, y + 1)});
            swap(c, g[x][y]);   // 回溯取消标记
            return r;
        };
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {   
                ans = max(ans, dfs(i, j));
            }
        }
        return ans;
    }

    int getMaximumGold(vector<vector<int>>& g) {
        int res = 0;
        for (int i = 0; i < g.size(); ++i) {
            for (int j = 0; j < g[0].size(); ++j) {
                res = max(res, helper(g, i, j));
            }
        }
        return res;
    }
    int helper(vector<vector<int>>& g, int i, int j) {
        if (i < 0 || i >= g.size() || j < 0 || j >= g[0].size() || g[i][j] == 0) {
            return 0;                                               // 若出界或没金则返0
        }
        int origin = g[i][j], next = 0;
        g[i][j] = 0;                                                // 标记位访问过(没金子)
        vector<int> dirs = {0, 1, 0, -1, 0};
        for (int k = 0; k < 4; ++k) {
            next = max(next, helper(g, i + dirs[k], j + dirs[k + 1]));// 递归各邻居,更新max
        }
        g[i][j] = origin;                                           // 回溯(去掉访问标记)  
        return next + origin;                                       // 坑: 勿忘+当前cell
    }
};
