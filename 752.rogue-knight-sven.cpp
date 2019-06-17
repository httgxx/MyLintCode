/*
 * @lc app=lintcode id=752 lang=cpp
 *
 * [752] Rogue Knight Sven
 *
 * https://www.lintcode.com/problem/rogue-knight-sven/description
 *
 * lintcode
 * Medium (41.00%)
 * Total Accepted:    1086
 * Total Submissions: 2626
 * Testcase Example:  '1\n1\n1\n[0,1]'
 *
 * In material plane "reality", there are `n + 1` planets, namely planet 0,
 * planet 1, ..., planet n.
 * Each planet has a portal through which we can reach the target planet
 * directly without passing through other planets.
 * But portal has two shortcomings.
 * First, planet `i` can only reach the planet whose number is **greater than**
 * `i`, and the difference between `i` can not exceed the limit.
 * Second,  it takes `cost[j]` gold coins to reach the planet `j` through the
 * portal.
 * Now, Rogue Knight Sven arrives at the planet `0` with `m` gold coins, how
 * many ways does he reach the planet `n` through the portal?
 * 
 * Example 1:
 * Input: n = 1, m = 1, limit = 1, cost = [0, 1]
 * Output: 1
 * Explanation:
 * Plan 1: planet 0 → planet 1
 * 
 * Example 2:
 * Input: n = 1, m = 1, limit = 1, cost = [0,2]
 * Output: 0
 * Explanation:
 * He can not reach the target planet.
 * 
 * @Category DP
 * @Idea
 * dp[i][j]表示从星球0出发到达星球i后拥有j个金币的方案数
 * dp[i][j] = sum{dp[t][j + cost[i]]|t=max(0, i-limit)~(i-1)}
 * 初始 dp[0][m]=1
 * 返回 sum{dp[n][j]ans|j=0~m}
 */
class Solution {
public:
    /**
     * @param n: the max identifier of planet.
     * @param m: gold coins that Sven has.
     * @param limit: the max difference.
     * @param cost: the number of gold coins that reaching the planet j through the portal costs.
     * @return: return the number of ways he can reach the planet n through the portal.
     */
    long long getNumberOfWays(int n, int m, int limit, vector<int> &cost) {
        long long dp[n + 1][m + 1];
        for (int i = 0; i < m; i++) {
            dp[0][i] = 0;
        }
        dp[0][m] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = 0;
                for (int t = max(0, i - limit); t <= i - 1; t++) {
                    if (j + cost[i] <= m) {
                        dp[i][j] += dp[t][j + cost[i]];
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i <= m; i++) {
            ans += dp[n][i];
        }
        return ans;
    }
};
