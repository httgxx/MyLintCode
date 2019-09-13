/*
 * @lc app=lintcode id=1346 lang=cpp
 *
 * [1346] Dungeon Game
 *
 * https://www.lintcode.com/problem/dungeon-game/description
 *
 * lintcode
 * Hard (59.00%)
 * Total Accepted:    357
 * Total Submissions: 631
 * Testcase Example:  '[[-2,-3,3],[-5,-10,1],[10,30,-5]]'
 *
 * The demons had captured the princess (P) and imprisoned her in the
 * bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid
 * out in a 2D grid. Our valiant knight (K) was initially positioned in the
 * top-left room and must fight his way through the dungeon to rescue the
 * princess.
 * 
 * The knight has an initial health point represented by a positive integer. If
 * at any point his health point drops to 0 or below, he dies immediately.
 * 
 * Some of the rooms are guarded by demons, so the knight loses health
 * (negative integers) upon entering these rooms; other rooms are either empty
 * (0's) or contain magic orbs that increase the knight's health (positive
 * integers).
 * 
 * In order to reach the princess as quickly as possible, the knight decides to
 * move only rightward or downward in each step.
 * 
 * Write a function to determine the knight's minimum initial health so that he
 * is able to rescue the princess.
 * 
 * For example, given the dungeon below, the initial health of the knight must
 * be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
 * 
 * ```plain
 * | -2(K)   | -3     | 3        |
 * | -5      | -10    | 1        |
 * | 10      | 30     | -5(P)    |
 * ```
 * 
 * Example 1
 * Input: [[-2,-3,3],[-5,-10,1],[10,30,-5]]
 * Output: 7
 * Explanation: The path right-> right -> down-> down is the best.
 * 
 * Example 2
 * Input: [[-2,0,3],[-5,100,-999],[10,30,-5]]
 * Output: 3
 * Explanation: The path right -> down -> down -> right is the best.
 * 
 */
class Solution {
public:
    /**
     * @param dungeon: a 2D array
     * @return: return a integer
     */
    // DP + 倒推
    int calculateMinimumHP(vector<vector<int>> &dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));  // dp[i][j]表示进入房间[i][j]时需要的最少血量
                                                                     // 多留1行1列好处理dp公式中[m-1]和[n-1]边界情况
        dp[m][n - 1] = dp[m-1][n] = 1;                               // 入房间[m-1][n-1]屠龙后需活着则从房间[m-1][n-1]出来时血量>=1 
                                                                     // 可设立dummy右房间[m-1][n]和下房间[m][n-1]且进入时最少血量=1
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                dp[i][j] = max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]); // 入当前房间时需最少血量>=1且>=入下个房间时需最少血量-当前房间耗血量
            }
        }
        return dp[0][0]; // 倒推出入第一个房间时需要的最少血量 
    }
};
