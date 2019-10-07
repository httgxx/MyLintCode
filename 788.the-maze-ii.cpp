/*
 * @lc app=lintcode id=788 lang=cpp
 *
 * [788] The Maze II
 *
 * https://www.lintcode.com/problem/the-maze-ii/description
 *
 * lintcode
 * Medium (62.00%)
 * Total Accepted:    2330
 * Total Submissions: 3711
 * Testcase Example:  '[[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]]\n[0,4]\n[4,4]'
 *
 * There is a ball in a maze with empty spaces and walls. The ball can go
 * through empty spaces by rolling `up`, `down`, `left` or `right`, but it
 * won't stop rolling until hitting a wall. When the ball stops, it could
 * choose the next direction.
 * 
 * Given the ball's start position, the destination and the maze, find the
 * shortest distance for the ball to stop at the destination. The distance is
 * defined by the number of empty spaces traveled by the ball from the start
 * position (excluded) to the destination (included). If the ball cannot stop
 * at the destination, return -1.
 * 
 * The maze is represented by a binary 2D array. 1 means the wall and 0 means
 * the empty space. You may assume that the borders of the maze are all walls.
 * The start and destination coordinates are represented by row and column
 * indexes.
 * 
 * 1.There is only one ball and one destination in the maze.
 * 2.Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
 * 3.The given maze does not contain border (like the red rectangle in the example pictures), but you could assume 
 *   the border of the maze are all walls.
 * 4.The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
 * 
 * Example 1:
 * 	Input:  
 * 	(rowStart, colStart) = (0,4)
 * 	(rowDest, colDest)= (4,4)
 * 	0 0 1 0 0
 * 	0 0 0 0 0
 * 	0 0 0 1 0
 * 	1 1 0 1 1
 * 	0 0 0 0 0
 * 	Output:  12
 * 	Explanation: (0,4)->(0,3)->(1,3)->(1,2)->(1,1)->(1,0)->(2,0)->(2,1)->(2,2)->(3,2)->(4,2)->(4,3)->(4,4)
 * 
 * Example 2:
 * 	Input:
 * 	(rowStart, colStart) = (0,4)
 * 	(rowDest, colDest)= (0,0)
 * 	0 0 1 0 0
 * 	0 0 0 0 0
 * 	0 0 0 1 0
 * 	1 1 0 1 1
 * 	0 0 0 0 0
 *  Output:  6
 * 	Explanation: (0,4)->(0,3)->(1,3)->(1,2)->(1,1)->(1,0)->(0,0)
 * 
 * @Category Maze DFS/BFS
 * @Idea
 * 
 */
class Solution {
public:
    /**
     * @param maze: the maze
     * @param start: the start
     * @param destination: the destination
     * @return: the shortest distance for the ball to stop at the destination
     */
    // BFS + 一个方向上不停走直到撞墙
    // T=O(mn*max(m,n)) S=O(mn)
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> dists(m, vector<int>(n, INT_MAX));                  // 初始化:从起点到终点的路上各点处走过的最小步数=INT_MAX
        vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
        queue<pair<int, int>> q;
        q.push({start[0], start[1]});                                           // 起点入队列
        dists[start[0]][start[1]] = 0;                                          // 起点处走过的步数=0,也表明访问过
        while (!q.empty()) {                                                    // T=O(mn*...)
            auto t = q.front(); q.pop();
            for (auto d : dirs) {                                               // 往4个方向
                int x = t.first, y = t.second, dist = dists[t.first][t.second]; // 从队首点所在位置出发
                while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) { // 此方向上只要不出界不撞墙就闷头滚且+步数 T=O(max(m,n)*...)
                    x += d[0];
                    y += d[1];
                    ++dist;
                }
                x -= d[0];                                                      // 回退在出界或撞墙时多走的最后一步
                y -= d[1];
                --dist;
                if (dists[x][y] > dist) {
                    dists[x][y] = dist;                                         // 更新最小步数
                    if (x != destination[0] || y != destination[1]) { q.push({x, y}); } // 没到终点,入队列下一层访问
                }
            }
        }
        int res = dists[destination[0]][destination[1]];
        return (res == INT_MAX) ? -1 : res;
    }
};
