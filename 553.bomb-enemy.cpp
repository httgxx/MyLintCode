/*
 * @lc app=lintcode id=553 lang=cpp
 *
 * [553] Bomb Enemy
 *
 * https://www.lintcode.com/problem/bomb-enemy/description
 *
 * lintcode
 * Medium (35.00%)
 * Total Accepted:    3539
 * Total Submissions: 9944
 * Testcase Example:  '["0E00","E0WE","0E00"]\n'
 *
 * Given a 2D grid, each cell is either a wall `'W'`, an enemy `'E'` or empty
 * `'0'` (the number zero), return the maximum enemies you can kill using one
 * bomb.
 * The bomb kills all the enemies in the same row and column from the planted
 * point until it hits the wall since the wall is too strong to be destroyed.
 * 
 * @Category DP
 * @Ideas
 * DP // T=O(n) S=O(n)
 * 
 */
class Solution {
public:
    /**
     * @param grid: Given a 2D grid, each cell is either 'W', 'E' or '0'
     * @return: an integer, the maximum enemies you can kill using one bomb
     */
    int maxKilledEnemies(vector<vector<char>> &grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0, rowCnt, colCnt[n];
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == 0 || grid[i][j - 1] == 'W') {
                    rowCnt = 0;
                    for (int k = j; k < n && grid[i][k] != 'W'; ++k) {
                        rowCnt += grid[i][k] == 'E';
                    }
                }
                if (i == 0 || grid[i - 1][j] == 'W') {
                    colCnt[j] = 0;
                    for (int k = i; k < m && grid[k][j] != 'W'; ++k) {
                        colCnt[j] += grid[k][j] == 'E';
                    }
                }
                if (grid[i][j] == '0') {
                    res = max(res, rowCnt + colCnt[j]);
                }
            }
        }
        return res;
    }
};
