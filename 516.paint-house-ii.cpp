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
 * @Category DP
 * @Idea
 * S1: DP T=O(n) S=O(n)
 * min1和min2记录之前房子总花费最小和次小值,min1Col记录最小值对应的前房子颜色.
 * 当前房子颜色!=min1Col时用min1算新的总花费,=minCol1则用反之用min2算新总花费.
 * 每刷一个新房子后将当前最小和次小值当作新的总花费的最小和次小
 * 坑:全局min1和min2的初始值时0而不是INT_MAX,因为会先用来赋值而不是比较
 *    全局min1和min2只在2处使用:1)算当前最小值时 2)被当前最小值更新时
 * 坑:局部curMin1和curMin2的初始值是INT_MAX而不是0,因为会先用来比较才再被更新
 *    局部curMin1和curMin2只在颜色j的循环内使用,在房子i的循环内被初始化
 * 
 * S0: DP T=O(mn^2) S=O(mn)
 * dp[i][j]表示刷房子([0]~[i])且房子[i]刷成颜色j的最小花费
 * dp[i][j] = min{dp[i-1][k]}|k!=j + costs[i][j]即把房子[i]刷成颜色j的花费；
 */
class Solution {
public:
    /**
     * @param costs: n x k cost matrix
     * @return: an integer, the minimum cost to paint all houses
     */
    int minCostII(const vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;  // 特例
        int m = costs.size(), n = costs[0].size();
        // 当前总共花费的最小和次小值
        // 坑1:初始值不是INT_MAX而是0,因为会先用来计算而不是比较
        // 坑2:全局最小值只在2处使用:1)算当前最小值时 2)被当前最小值更新时
        int min1 = 0, min2 = 0, lastCol = -1;
        for (int i = 0; i < m; ++i) {  // 刷到房子[i]
            // 每刷1新房子就计算刷完它后当前总花费的最小和次小
            // 坑2:初始值不是0而是INT_MAX,因为会先被用来比较再被更新
            int curMin1 = INT_MAX, curMin2 = INT_MAX, curMin1Col = -1;
            for (int j = 0; j < n; ++j) {  // 房子[i]刷成颜色j
                int cost = costs[i][j] + (j != lastCol ? min1 : min2);
                if (cost < curMin1) {  // 新最小值,更新次小值和最小值对应的颜色
                    curMin2 = curMin1;  // 坑3:不是=minMin1而是=curMin1
                    curMin1 = cost;
                    curMin1Col = j;
                } else if (cost < curMin2) {  // 新次小值,最小值和对应颜色不变
                    curMin2 = cost;
                }
            }
            // 确定当前房子刷的颜色后,更新当前总花费的最小和次小,继续刷下个房子
            min1 = curMin1;
            min2 = curMin2;
            lastCol = curMin1Col;
        }
        return min1;
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
