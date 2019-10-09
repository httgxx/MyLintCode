/*
 * @lc app=lintcode id=663 lang=cpp
 *
 * [663] Walls and Gates
 *
 * https://www.lintcode.com/problem/walls-and-gates/description
 *
 * lintcode
 * Medium (49.00%)
 * Total Accepted:    4603
 * Total Submissions: 9266
 * Testcase Example:  '[[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]\n'
 *
 * You are given a m x n 2D grid initialized with these three possible values.
 * 
 * `-1`  - A wall or an obstacle.
 * `0`   - A gate.
 * `INF` - Infinity means an empty room. We use the value `2^31 - 1 =
 * 2147483647` to represent INF as you may assume that the distance to a gate
 * is less than `2147483647`.
 * Fill each empty room with the distance to its nearest gate. If it is
 * impossible to reach a `ROOM`, that room should remain filled with `INF`
 * 
 * Example1
 * Input:
 * [[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]
 * Output: [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
 * Explanation:
 * the 2D grid is:
 * INF  -1  0  INF
 * INF INF INF  -1
 * INF  -1 INF  -1
 * 0  -1 INF INF
 * the answer is:
 *   3  -1   0   1
 *   2   2   1  -1
 *   1  -1   2  -1
 *   0  -1   3   4
 * 
 * Example2
 * Input: [[0,-1],[2147483647,2147483647]]
 * Output:[[0,-1],[1,2]]
 * 
 * @Category 迷宫 BFS DFS
 * @Idea BFS DFS
 * 
 */
class Solution {
public:
    /**
     * @param rooms: m x n 2D grid
     * @return: nothing
     */
    void wallsAndGates(vector<vector<int>> &rooms) {
        queue<pair<int, int>> q;
        vector<vector<int>> dirs{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
        int m = rooms.size(), n = rooms[0].size();
        for (int i = 0; i < rooms.size(); ++i) {
            for (int j = 0; j < rooms[i].size(); ++j) {
                if (rooms[i][j] == 0) { q.push({i, j}); }      
            }
        }
        while (!q.empty()) {
            int i = q.front().first, j = q.front().second; q.pop();
            for (int k = 0; k < dirs.size(); ++k) {
                int x = i + dirs[k][0], y = j + dirs[k][1];
                if (x < 0 || x >= rooms.size() || y < 0 || y >= rooms[0].size() ||
                    rooms[x][y] < rooms[i][j] + 1) { continue; }
                rooms[x][y] = rooms[i][j] + 1;
                q.push({x, y});
            }
        }
    }
};
