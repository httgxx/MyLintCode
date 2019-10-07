/*
 * @lc app=lintcode id=477 lang=cpp
 *
 * [477] Surrounded Regions
 *
 * https://www.lintcode.com/problem/surrounded-regions/description
 *
 * lintcode
 * Medium (27.00%)
 * Total Accepted:    9701
 * Total Submissions: 35053
 * Testcase Example:  '["XXXX","XOOX","XXOX","XOXX"]\n'
 *
 * Given a 2D board containing `'X'` and `'O'`, capture all regions surrounded
 * by `'X'`.
 * 
 * A region is captured by flipping all `'O'`'s into `'X'`'s in that surrounded
 * region.
 * 
 * Example 1:
 * Input:
 *   X X X X
 *   X O O X
 *   X X O X
 *   X O X X
 * Output:
 *   X X X X
 *   X X X X
 *   X X X X
 *   X O X X
 * 
 * Example 2:
 * Input:
 *   X X X X
 *   X O O X
 *   X O O X
 *   X O X X
 * Output:
 *   X X X X
 *   X O O X
 *   X O O X
 *   X O X X
 * 
 * @Category BFS DFS
 * @Idea BFS DFS
 * 
 * 
 */
class Solution {
public:
    /*
     * @param board: board a 2D board containing 'X' and 'O'
     * @return: nothing
     */
    // BFS + tag
    // T=O(mn) S=O(1)
    void surroundedRegions(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) { return; }
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != 0 && i != m - 1 && j != 0 && j != n - 1) { continue; } // 非边界点则跳过
                if (board[i][j] != 'O') { continue; }                           // 已包围或已访问的点跳过
                                                                                // 此时确认当前结点为:边界上没被包围的点
                board[i][j] = '$';                                              // 标记当前点(为已访问过)
                queue<int> q{{i * n + j}};                                      // 当前点入队列(坐标压缩1维化)
                while (!q.empty()) {
                    int t = q.front(), x = t / n, y = t % n; q.pop();           // 取队首结点(坐标恢复2维化)
                                                                                // 访问其上下左右4邻居,若不在边界且没被包围则标记后入列
                    if (x >= 1    && board[x - 1][y] == 'O') { board[x - 1][y] = '$'; q.push(t - n); } // 上邻居
                    if (x < m - 1 && board[x + 1][y] == 'O') { board[x + 1][y] = '$'; q.push(t + n); } // 下邻居
                    if (y >= 1    && board[x][y - 1] == 'O') { board[x][y - 1] = '$'; q.push(t - 1); } // 左邻居
                    if (y < n - 1 && board[x][y + 1] == 'O') { board[x][y + 1] = '$'; q.push(t + 1); } // 右邻居
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') { board[i][j] = 'X'; }                  // 不在边界上且不和任何边界上'O'连通的'O'都会被包围变成'X' 
                if (board[i][j] == '$') { board[i][j] = 'O'; }                  // 边界上的'O'或和边界上'O'连通的'O'仍然恢复成'O'
            }
        }
    }
};
