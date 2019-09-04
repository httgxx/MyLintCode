/*
 * @lc app=lintcode id=1422 lang=cpp
 *
 * [1422] Shortest Path Visiting All Nodes
 *
 * https://www.lintcode.com/problem/shortest-path-visiting-all-nodes/description
 *
 * lintcode
 * Hard (55.00%)
 * Total Accepted:    57
 * Total Submissions: 100
 * Testcase Example:  '[[1,2,3],[0],[0],[0]]'
 *
 * An undirected, connected graph of N nodes (labeled `0, 1, 2, ..., N-1`) is
 * given as `graph`.
 * 
 * `graph.length = N`, and `j != i` is in the list `graph[i]` exactly once, if
 * and only if nodes `i` and `j` are connected.
 * 
 * Return the length of the shortest path that visits every node. You may start
 * and stop at any node, you may revisit nodes multiple times, and you may
 * reuse edges.
 * 
 * 1≤graph.length≤12  => 说明解法T~O(2^n)
 * 0 \leq graph[i].length < graph.length0≤graph[i].length<graph.length
 * 
 * Example 1:
 * Input: graph = [[1,2,3],[0],[0],[0]]  
 * i.e. 0<->1/2/3; 1<->0; 2<->0; 3<->0,
 *      0
 *    / | \
 *   1  2  3
 * Output: 4
 * Explanation: 
 * One possible path is [1,0,2,0,3]
 * 
 * Example 2:
 * Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
 * i.e.0<->1; 1<->0/2/4; 2<->1/3/4; 3<->2; 4<->1/2
 * 0 - 1 - 2 - 3
 *      \ /
 *       4
 * Output: 4
 * Explanation: 
 * One possible path is [0,1,4,2,3]
 *
 * @Category Graph, Shortest Path
 * @Idea 求最短路径 BFS
 * // T=O(n*2^n) S=O(n*2^n)
 * 难点1:如何避重? 既要允许重复访问一个顶点,又要避免死循环?
 *  思路:什么情况下会死循环?再次访问同一个顶点时发现被访问过的顶点集并没有发生变化
 *      即上次访问该顶点时有哪些顶点被访问过,这次还是这些顶点被访问过,故避重条件
 *      要从"访问顶点i时,顶点i没被访问过(访问状态不同)"state=bool cur_node_status //visited or not 
 *      变成"访问顶点i时,顶点集合的访问状态都不同"state=(int cur_node_idx, set<int> all_visited_nodes)
 *      state最多可能n*2^n种 => BFS最多访问n*2^n次 => T=S=O(n*2^n)
 * 优化1:bit map 
 *      set<int> => int //每个bit记录某顶点是(1)否(0)被访问过
 *      state=(int cur_node_idx, int all_nodes_status)
 * 优化2:编码status
 *      (int,int)=>int //前16位存cur_node_idx,后16位存all_nodes_status
 *      state= (cur_node_idx << 16) | cu_node_idx
 * 难点2:如何做到从任意点出发,即每顶点都可作起点?
 *       开始所有顶点都入队 e.g. q{<0,001>,<1,010>,<2,100>}
 *       每次访问完一个顶点就更新all_node_status 从node0出发访问node1后<0,001>=><1,101>
 * 
 * 坑: 处理特例graph=[[]] 
 * 坑:
 */
class Solution {
public:
    /**
     * @param graph: the graph
     * @return: the shortest path for all nodes
     */
    int shortestPathLength(vector<vector<int>> &graph) {
        int n = graph.size();
        if (n == 0) { return 0; }           // 特例: 空
        if (graph[0].empty()) { return 0; } // 坑!!!: 特例 [[]]

        int steps = 0;
        int final = (1 << n) - 1;      // 目标状态=n位1:所有n个顶点都被访问过
        unordered_set<int> visited;    // 已访问的状态(编码)
        queue<pair<int, int>> q;       // <当前顶点,当前所有顶点访问状态>
        for (int i = 0; i < n; ++i) {  // 初始化:所有顶点入队,即从每个顶点出发
            q.push({i, 1 << i});        
        }
        
        while (!q.empty()) {    // BFS
            int cnt = q.size(); // 当前层大小
            while (cnt--) {
                auto p = q.front(); q.pop();
                int node = p.first, state = p.second;
                if (state == final) { return steps; }       // 分层遍历,先结束的最短
                int stateCode = (node << 16) | state;       // 状态编码,最多n*2^n种=>O(n*2^n)
                if (visited.count(stateCode)) { continue; } // 避重
                visited.insert(stateCode);                  // 存状态以避重
                for (int neighbor : graph[node]) {          // 更新状态,邻居入队
                    q.push({neighbor, state | (1 << neighbor)});
                }
            }
            ++steps;
        }
        return 0;
    }
};
