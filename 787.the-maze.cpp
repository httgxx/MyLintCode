/*
 * @lc app=lintcode id=787 lang=cpp
 *
 * [787] The Maze
 *
 * https://www.lintcode.com/problem/the-maze/description
 *
 * lintcode
 * Medium (39.00%)
 * Total Accepted:    2606
 * Total Submissions: 6545
 * Testcase Example:  '[[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]]\n[0,4]\n[3,2]'
 *
 * There is a ball in a maze with empty spaces and walls. The ball can go
 * through empty spaces by rolling `up`, `down`, `left` or `right`, `but it
 * won't stop rolling until hitting a wall`. When the ball stops, it could
 * choose the next direction.
 * 
 * Given the ball's start position, the destination and the maze, determine
 * whether the ball could stop at the destination.
 * 
 * The maze is represented by a binary 2D array. 1 means the wall and 0 means
 * the empty space. You may assume that the borders of the maze are all walls.
 * The start and destination coordinates are represented by row and column
 * indexes.
 */
class Solution {
public:
    /**
     * @param maze: the maze
     * @param start: the start
     * @param destination: the destination
     * @return: whether the ball could stop at the destination
     */
    // BFS T=O(mn)) S=O(mn)
    bool hasPath(vector<vector<int>> &maze, vector<int> &start, vector<int> &destination) {
        if (maze.empty() || maze[0].empty()) { return true; }                   // 特例:空迷宫
        int m = maze.size(), n = maze[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
        queue<pair<int, int>> q;
        q.push({start[0], start[1]});                                           // 起点入队列                                   
        visited[start[0]][start[1]] = true;                                     // 设为访问过
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            if (t.first == destination[0] && t.second == destination[1]) {      // 若到达终点,结束返回
                return true;
            }
            for (auto dir : dirs) {                                             // 否则分别访问4个邻居
                int x = t.first, y = t.second;
                while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) { // 若没出界且没撞墙
                    x += dir[0]; y += dir[1];                                   // 就一直闷头同向走
                }
                x -= dir[0]; y -= dir[1];                                       // 返回多走的最后一步
                if (!visited[x][y]) {                                           // 若没访问过
                    visited[x][y] = true;                                       // 则设为访问过
                    q.push({x, y});                                             // 且入队列下一层访问
                }
            }
        }
        return false;                                                           // 坑:无法到达!!!
    }
};
