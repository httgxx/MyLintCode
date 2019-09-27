/*
 * @lc app=lintcode id=364 lang=cpp
 *
 * [364] Trapping Rain Water II
 *
 * https://www.lintcode.com/problem/trapping-rain-water-ii/description
 *
 * lintcode
 * Hard (32.00%)
 * Total Accepted:    7625
 * Total Submissions: 23222
 * Testcase Example:  '[[12,13,0,12],[13,4,13,12],[13,8,10,12],[12,13,12,12],[13,13,13,13]]\n'
 *
 * Given *n* x *m* non-negative integers representing an elevation map 2d where
 * the area of each cell is *1* x *1*, compute how much water it is able to
 * trap after raining.
 * 
 * 
 * ![](https://lintcode-media.s3.amazonaws.com/problem/trapping-rain-water-ii.jpg
 * "")
 * 
 * Example 1:
 * Given `5*4` matrix 
 * Input: [[12,13,0,12],[13,4,13,12],[13,8,10,12],[12,13,12,12],[13,13,13,13]]
 * Output: 14
 * 
 * Example 2:
 * Input: [[2,2,2,2],[2,2,3,4],[3,3,3,1],[2,3,4,5]]
 * Output: 0
 * 
 * @Category BFS + visited[][]
 * @Idea
 * queue{{边界上所有点}}
 */
class Solution {
public:
    /**
     * @param heights: a matrix of integers
     * @return: an integer
     */
    // BFS + visited + 2维坐标1维化: T=O() S=O()
    int trapRainWater(vector<vector<int>>& heights) {
        if (heights.empty()) { return 0; }
        int m = heights.size(), n = heights[0].size(), res = 0, mx = INT_MIN;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;  // 最小堆-堆顶最低(木桶原理)
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {                         // 边界上个点无法装水
                    q.push({ heights[i][j], i * n + j });                                   // 入队列作起始点<高度,1维化坐标>
                    visited[i][j] = true;                                                   // 标记为已访问
                }
            }
        }
        vector<vector<int>> dir{{0,-1},{-1,0},{0,1},{1,0}};
        while (!q.empty()) {
            auto t = q.top(); q.pop();
            int h = t.first, r = t.second / n, c = t.second % n;                            // 坐标恢复2维
            mx = max(mx, h);                                                                // 更新当前最高
            for (int i = 0; i < dir.size(); ++i) {                                          // 遍历4邻居
                int x = r + dir[i][0], y = c + dir[i][1];
                if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y]) { continue; }      // 出界或以访问过跳过
                visited[x][y] = true;                                                       // 否则标记已访问
                if (heights[x][y] < mx) { res += mx - heights[x][y]; }                      // 与当前最高差值为水量
                q.push({ heights[x][y], x * n + y });                                       // 邻居入队列下一层访问
            }
        }
        return res;
    }
};
