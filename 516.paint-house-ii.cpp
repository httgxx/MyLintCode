/*
 * @lc app=lintcode id=516 lang=cpp
 *
 * [516] Paint House II
 *
 * https://www.lintcode.com/problem/paint-house-ii/description
 *
 * lintcode
 * Hard (31.00%)
 * Total Accepted:    5268
 * Total Submissions: 16722
 * Testcase Example:  '[[14,2,11],[11,14,5],[14,3,10]]\n'
 *
 * There are a row of `n` houses, each house can be painted with one of the `k`
 * colors. The cost of painting each house with a certain color is different.
 * You have to paint all the houses such that no two adjacent houses have the
 * same color.
 * 
 * The cost of painting each house with a certain color is represented by a `n`
 * x `k` cost matrix. For example, `costs[0][0]` is the cost of painting house
 * `0` with color `0`; `costs[1][2]` is the cost of painting house `1` with
 * color `2`, and so on... Find the minimum cost to paint all houses.
 *
 * @Category DP(按情况叠加比较型)
 * @Idea
 * S1: DP T=O(mn) S=O(1)
 * 全局min1和min2记录刷前面房子[0~n-1]总花费最小和次小值,min1Col记录最小值对应的前房子颜色.
 * 局部curMin1和curMin2记录当前房子[i]刷颜色j时总花费的最小和次小值
 * 若当前房子[i]颜色!=min1Col则总花费cost=costs[i][j]+min1,否则=costs[i][j]+min2
 * 每次处理完一种颜色后,用cost更新局部最小值和次小值
 * 每刷完1个房子后,用局部最小值更新全局最小值
 * 坑:全局min1和min2的初始值时0而不是INT_MAX,因为会先用来赋值而不是比较
 *    全局min1和min2只在2处使用:1)算当前最小值时 2)被当前最小值更新时
 * 坑:局部curMin1和curMin2的初始值是INT_MAX而不是0,因为会先用来比较才再被更新
 *    局部curMin1和curMin2只在颜色j的循环内使用,在房子i的循环内被初始化
 * 
 * S0: DP T=O(mn) S=O(mn)
 * min1Col和min2Col记录之前房子总花费最小和次小值对应的颜色.
 * dp[i][j]表示刷到房子[i]且刷成颜色j时最小的总共花费
 * dp[i][j] = costs[i][j] +
 *   if (i>0 && j!=min1Col) dp[i-1][min1Col]
 *   else if (i>0 && j==min1Col) dp[i-1][min2Col]
 */
class Solution {
public:
    /**
     * @param costs: n x k cost matrix
     * @return: an integer, the minimum cost to paint all houses
     */
    // DP T=O(mn) S=O(1)
    int minCostII(const vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;                // 特例:没房子刷不要钱
        int m = costs.size(), n = costs[0].size();
        int min1 = 0, min2 = 0, lastCol = -1;                           // 刷完当前房子后的全局最小(min1)和次小(min2)总费,以及全局最小对应的房子颜色(lastCol)
                                                                        // (坑1:全局最小/次小总费初始值不是INT_MAX而是0,因为会先被用来计算而不是比较)
        for (int i = 0; i < m; ++i) {                                   // 每刷完1个房子[i],更新全局最小/次小总费
            int curMin1 = INT_MAX, curMin2 = INT_MAX, curMin1Col = -1;  // (坑2:局部最小/次小总费初始值不是0而是INT_MAX,因为会先被用来比较再被更新)
            for (int j = 0; j < n; ++j) {                               // 房子[i]刷成每种颜色j,更新局部最小/次小总费
                int cost = costs[i][j] + (j != lastCol ? min1 : min2);  // 由于不能连续同色，故根据颜色j是否和上次全局最小对应颜色同色,来计算当前总费(当前花费+全局最小还是次小)
                if (cost < curMin1) {                                   // 发现当前总费<局部最小,则新局部最小=当前总费,新局部次小=旧局部最小,更新局部最小对应的房子颜色为j
                    curMin2 = curMin1;                                  // (坑3:局部最小/次小而不是全局最小/次小)
                    curMin1 = cost;
                    curMin1Col = j;
                } 
                else if (cost < curMin2) { curMin2 = cost; }            // 发现当前总费>=局部最小但是<局部次小,则新局部次小=当前总费 (局部最小和对应的房子颜色不变)
            }
            min1 = curMin1;                                             // 对房子[i]枚举完所有颜色后,用局部最小/次小更新全局最小/次小,以及全局最小对应的房子颜色
            min2 = curMin2;
            lastCol = curMin1Col;
        }
        return min1;                                                    // 返回全局最小花费
    }

    int minCostII1(const vector<vector<int>> &costs) {
        if (costs.empty() || costs[0].empty()) return 0;  // 特例
        int m = costs.size(), n = costs[0].size();
        // 当前总共花费最小和次小对应的颜色
        // 坑1:初始值不是0而是-1,因为会先用来比较
        // 坑2:全局最小值只在2处使用:1)算当先最小值时 2)被当前最小值更新时
        int min1Col = -1, min2Col = -1;
        vector<vector<int>> dp = costs;  // 初始化dp[i][j]=cost[i][j]
        for (int i = 0; i < m; ++i) {
            // 每刷1新房子就计算刷完它后总花费最小和次小对应的颜色
            // 坑3:初始值不是0而是-1,因为会先被用来比较再被更新
            int curMin1Col = -1, curMin2Col = -1;
            for (int j = 0; j < n; ++j) {
                if (i > 0) {  // 从刷第2个房子开始才累加刷前面房子的花费
                    // min1Col和min2Col应该在i=0时就被更新而不会为-1
                    dp[i][j] += j != min1Col
                        ? dp[i - 1][min1Col]   // 累加前房子最小花费
                        : dp[i - 1][min2Col];  // 累加前房子次小花费
                }
                // 发现新最小值
                // 坑4: curMin1Col而不是min1Col
                if (curMin1Col < 0 || dp[i][j] < dp[i][curMin1Col]) {
                    curMin2Col = curMin1Col;  // 坑4:不是=minMin1而是=curMin1
                    curMin1Col = j;
                }
                // 发现新次小值
                // 坑5: curMin2Col而不是min2Col
                else if (curMin2Col < 0 || dp[i][j] < dp[i][curMin2Col]) {
                    curMin2Col = j;
                }
            }
            // 确定当前房子刷的颜色后,更新当前总花费的最小和次小,继续刷下个房子
            min1Col = curMin1Col;
            min2Col = curMin2Col;
        }
        return dp.back()[min1Col];
    }
};
