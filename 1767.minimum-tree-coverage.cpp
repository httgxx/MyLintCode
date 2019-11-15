/*
 * @lc app=lintcode id=1767 lang=cpp
 *
 * [1767] Minimum Tree Coverage
 *
 * https://www.lintcode.com/problem/minimum-tree-coverage/description
 *
 * lintcode
 * Hard (57.00%)
 * Total Accepted:    4
 * Total Submissions: 7
 * Testcase Example:  '[[1,2],[2,3],[2,4],[4,5],[1,6],[2,7],[5,8],[2,9],[5,10],[2,11],[3,12],[9,13],[11,14]]\n8'
 *
 * Given a tree of `n` nodes and a positive integer `k`, the length of edge of
 * the tree is `1`. you can place a person in any nodes of tree. This person
 * can supervise all nodes that are no more than `k` from the node of person.
 * Out put the minimum number of person that can be placed to supervise the
 * entire tree.
 * 
 * Note:
 * 1 ≤ k ≤ n ≤ 1e5
 * the input array a is the edge set of tree.
 * 
 * Example 1:
 * Input：[[1,2],[2,3],[2,4],[4,5],[1,6],[2,7],[5,8],[2,9],[5,10],[2,11],[3,12],[9,13],[11,14]],8
 * Output：1
 * Explanation：You can place a person at node 1, and he can supervise other nodes.
 * 
 * Example 2:
 * Input：[[1,2],[1,3],[1,4],[1,5]],1
 * Output：1
 * Explanation：You can place a person at node 1, and he can supervise node 1, 2, 3, 4, 5.
 * 
 * @Category DP+DFS
 * @Idea
 * 
 */
class Solution {
public:
    /**
     * @param a: the edge set
     * @param k: the integer k
     * @return: return the minimum number of people required to supervise this tree
     */
    // DP + DFS 
    // dp[x]=-i时表示自身向下i层需要被覆盖。dp[x]=i时表示自身向上i层可以被覆盖
    // Mn表示从当前结点向下需要覆盖的层数,Mx表示从当前结点向上可以覆盖的层数
    // T=O(n^2) S=O(n^2)
    static const int INF = 1e8 + 10;
    static const int A = 2e5 + 10;
    vector<int> g[A]; // 结点上的人向上管祖先向下管子孙,故把树当无向图存成邻接表[结点:邻居结点list] 
    int dp[A], res;
 
    int minCover(vector<vector<int>> &a, int k) {
        int n = a.size() + 1;                       // 树的结点数=边数+1
        if (n == 1) { return 1; }                   // 特例:单节点数
        for (int i = 0; i <= n; i++) { g[i].clear(); }
        for (int i = 0; i < n - 1; i++) {
            int u = a[i][0], v = a[i][1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        memset(dp, 0, sizeof(dp));
        res = 0;
        dfs(1, 1, k);                               // dp+dfs
        if (dp[1] < 0) { ++res; }
        return res;
    }
    void dfs(int u, int pre, int k) {               // 递归检查结点u处是否需要加人
        int Mn = INF, Mx = -INF;
        for (int i = 0; i < g[u].size(); i++) {     // 遍历每个邻居(父/子)节点
            int v = g[u][i];
            if (v == pre) { continue; }             // 防止循环访问
            dfs(v, u, k);                           // 递归
            Mn = min(Mn, dp[v]);                    // 找到需要覆盖的最大层数
            Mx = max(Mx, dp[v]);                    // 找到能够覆盖的最大层数
        }
        if(Mn == INF) { dp[u] = -1; }               // 若访问到叶结点: 需要覆盖的层数为1
        else if (Mn <= -k){ dp[u] = k; ++res; }     // 若需要覆盖的层数超过k: 在该节点加人,且更新该节点可覆盖的层数为k
        else if (Mn + Mx > 0) { dp[u] = Mx - 1; }   // 若能覆盖的层数>需要覆盖的层数: 覆盖该层,能覆盖的层数-1
        else { dp[u] = Mn - 1; }                    // 若能覆盖的层数<=需要覆盖的层数: 不能覆盖该层,需要覆盖的层数+1
    }
};
