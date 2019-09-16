/*
 * @lc app=leetcode id=1162 lang=cpp
 *
 * [1162] As Far from Land as Possible
 *
 * https://leetcode.com/problems/as-far-from-land-as-possible/description/
 *
 * algorithms
 * Medium (38.65%)
 * Total Accepted:    6.1K
 * Total Submissions: 15.7K
 * Testcase Example:  '[[1,0,1],[0,0,0],[1,0,1]]'
 *
 * Given an N x N grid containing only values 0 and 1, where 0 represents water
 * and 1 represents land, find a water cell such that its distance to the
 * nearest land cell is maximized and return the distance.
 * 
 * The distance used in this problem is the Manhattan distance: the distance
 * between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
 * 
 * If no land or water exists in the grid, return -1.
 *
 * Example 1: 
 * Input: [[1,0,1],[0,0,0],[1,0,1]]
 * Output: 2
 * Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
 * 
 * Example 2:
 * Input: [[1,0,0],[0,0,0],[0,0,0]]
 * Output: 4
 * Explanation: The cell (2, 2) is as far as possible from all the land with distance 4.
 * 
 * Note:
 * 1 <= grid.length == grid[0].length <= 100
 * grid[i][j] is 0 or 1
 * 
 * @Category DFS BFS
 * @Idea
 * S1: BFS: 从每个land出发分层同步扩散 + 双队列方便debug?
 * 
 * 坑: dist从0开始,先++dist,再赋值dist给找到的water
 * 坑: return dist == 1 ? -1 : dist - 1;
 * 
 */
class Solution {
public:
    // S1 BFS: 从每个land出发分层同步扩散 + 双队列方便debug?
    // T=O(m*n*n) m=land的个数 S=O(n)
    int maxDistance(vector<vector<int>>& g) {
        int n = g.size(), dist = 0;         // 坑: dist从0开始!!!
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        queue<pair<int, int>> q, q1;
        for (auto i = 0; i < n; ++i) {      // 初始化:所有land入队
            for (auto j = 0; j < n; ++j) {
                if (g[i][j] == 1) {
                    for (auto dir : dirs) {
                        q.push({i + dir.first, j + dir.second});
                    }
                }
            }
        }
        while (!q.empty()) {
            ++dist; // 坑:先增加dist再赋值给找到的water
            while (!q.empty()) {
                int i = q.front().first, j = q.front().second;
                q.pop();
                if (i >= 0 && j >= 0 && i < n && j < n && g[i][j] == 0) { // 找到新water则立即更新其最小离地距离
                    g[i][j] = dist;
                    for (auto dir : dirs) {
                        q1.push({i + dir.first, j + dir.second});
                    }
                }
            }
            swap(q1, q); // 交换reference
        }
        return dist == 1 ? -1 : dist - 1;
    }

    // S2: DFS T=O(m*n*n) m=land数量,n=grid边长, S=O(n)  // Timeout!!!
    // 从每个land出发上下左右四方向走到底,更新water的最小离地距离,直到所有water都被访问过
    int maxDistanceDFS(vector<vector<int>>& g) {
        int mx = -1, n = g[0].size();
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < n; ++j)
                if (g[i][j] == 1) { dfs(g, i, j, 1, true); }    // 从每个land出发递归找water
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < n; ++j)
                if (g[i][j] > 1) { mx = max(mx, g[i][j] - 1); } // 对每个water统计最小离地距离的最大值 
                                                                // 坑:记得>1才统计且-1!
        return mx;
    }
    void dfs(vector<vector<int>>& g, int i, int j, int dist, bool isStart = false) {
        if (!isStart) {                                                 // 对起始land无序检测直接递归邻居
            if (i < 0 || j < 0 || i >= g.size() || j >= g[i].size() ||  // 若出界,终止递归
                (g[i][j] != 0 && g[i][j] <= dist)) { return; }          // 若land或已有更近land的water,终止递归
            g[i][j] = dist;                                             // 新water或water离当前更近,更新最短距离
        }
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // 坑: 不是{-1,-1} etc, 必有一个为0
        for (auto dir : dirs) { dfs(g, i + dir[0], j + dir[1], dist + 1); } // 递归邻居
    }
};
