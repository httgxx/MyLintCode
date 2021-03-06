/*
 * @lc app=lintcode id=1057 lang=cpp
 *
 * [1057] Network Delay Time
 *
 * https://www.lintcode.com/problem/network-delay-time/description
 *
 * lintcode
 * Medium (39.00%)
 * Total Accepted:    338
 * Total Submissions: 901
 * Testcase Example:  '[[2,1,1],[2,3,1],[3,4,1]]\n4\n2'
 *
 * There are `N` network nodes, labelled `1` to `N`.
 * 
 * Given `times`, a list of travel times as **directed** edges `times[i] = (u,
 * v, w)`, where `u` is the source node, `v` is the target node, and `w` is the
 * time it takes for a signal to travel from source to target.
 * 
 * Now, we send a signal from a certain node `K`. How long will it take for all
 * nodes to receive the signal? If it is impossible, return `-1`.
 * 
 * 1. N will be in the range [1, 100].
 * 2.K will be in the range [1, N].
 * 3.The length of times will be in the range [1, 6000].
 * 4.All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.
 * 
 * Example 1:
 * Input:  times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
 * Output:  2
 * 
 * Example 2:
 * Input: times = [[1,2,1],[1,2,2]], N = 2, K = 1
 * Output:  1
 * Explanation: Choose the shortest one.
 * 
 * 有向图最短路径:求单点K到每个点的最短路径的最大值
 * 思路:若有边(u,v)使dist(u)+w(u,v)<dist(v)则更新dist(v)
 * 
 * 方法一: Dijkstra Algorithm (单源最短路径 单点到任意点, 权重必须为正!)
 *   以起点为中心，向外层层扩展, 直到扩展到终点为止, 用visited数组记录已访问过的结点来避重
 *   T=O(V2),基于优先队列的T=O(E+VlogV)
 * 
 * 方法二: Floyd-Warshall Algorithm (单源最短路径 单点到任意点, 权重可以为负,但不能有权重为负的环)
 * 
 * 方法三: Bellman-Ford Algorithm (多源最短路径 任意点到任意点, 权重可以为负,但不能有权重为负的环)
 *    DP 如果存在负环则报错
 *    T=O(VE)  
 * 
 * @Cateogry Graph
 * @Idea
 * S1: Dijkstra T=O(V2)
 * 坑: 最后如果不可达(K孤岛)len=INT_MAX则返回-1
 * 
 */
class Solution {
public:
    /**
     * @param times: a 2D array
     * @param N: an integer
     * @param K: an integer
     * @return: how long will it take for all nodes to receive the signal
     */
    // S1: Dijkstra Algorithm  BFS, T=O(V^2) 单点到任意点最短路径的最大值
    int networkDelayTime1(vector<vector<int>> &times, int N, int K) {
        int res = 0;
        vector<vector<int>> edges(101, vector<int>(101, -1));
        for (auto e : times) edges[e[0]][e[1]] = e[2];      // 整理输入:边=>权重, <v,u,w>=>[v,u]=w
        vector<int> dist(N + 1, INT_MAX);                   // 预备输出:点=>最小路径长度,点index=1~N,0不用,故大小=N+1
        dist[K] = 0;
        queue<int> q{{K}};                                  // 从起点开始分层扩散
        while (!q.empty()) {
            unordered_set<int> visited;                     // 当前层已经访问过的结点
            for (int i = q.size(); i > 0; --i) {            // 倒减i以避免顺加时q.size()已变
                int u = q.front(); q.pop();                 // 当前点u为起点
                for (int v = 1; v <= 100; ++v) {            // 对1~N每个点v(包括v==u)都查一遍看u是否使d(v)更短
                    if (edges[u][v] != -1 &&
                        dist[u] + edges[u][v] < dist[v]) {  // 一旦发现u使d(v)更短则更新d(v)
                        if (!visited.count(v)) {            // 防止重复访问v
                            visited.insert(v); 
                            q.push(v);                      // 更新过d(v)的v入队下一层更新因v可能可使d(x)更短
                        }
                        dist[v] = dist[u] + edges[u][v];    // 更新d(x)
                    }
                }
            }
        }
        for (int i = 1; i <= N; ++i) {                      // K到个点的最短路径的最大值
            res = max(res, dist[i]);
        }
        return res == INT_MAX ? -1 : res;                   // 如果不可达(K孤岛)则返回-1
    }

    // S2: Bellman-Ford DP T=O(VE)
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        int res = 0;
        vector<int> dist(N + 1, INT_MAX);
        dist[K] = 0;
        for (int i = 1; i < N; ++i) {       // 每次循环至少relax一条边,总共N-1条边,所以循环N-1次
            for (auto e : times) {          // 访问每条边,若某边使得某邻居的dist更短则更新
                int u = e[0], v = e[1], w = e[2];
                if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;  // DP
                }
            }
        }
        for (int i = 1; i <= N; ++i) {
            res = max(res, dist[i]);
        }
        return res == INT_MAX ? -1 : res;  // 如果不可达(K孤岛)则返回-1
    }
};
