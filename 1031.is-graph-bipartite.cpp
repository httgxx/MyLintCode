/*
 * @lc app=lintcode id=1031 lang=cpp
 *
 * [1031] Is Graph Bipartite?
 *
 * https://www.lintcode.com/problem/is-graph-bipartite/description
 *
 * lintcode
 * Medium (42.00%)
 * Total Accepted:    1132
 * Total Submissions: 2664
 * Testcase Example:  '[[1,3],[0,2],[1,3],[0,2]]'
 *
 * Given an undirected `graph`, return `true` if and only if it is bipartite.
 * 
 * Recall that a graph is _bipartite_ if we can split it's set of nodes into
 * two independent subsets A and B such that **every edge** in the graph has
 * one node in A and another node in B.
 * 
 * The graph is given in the following form: `graph[i]` is a list of indexes
 * `j` for which the edge between nodes `i` and `j` exists.  Each node is an
 * integer between `0` and `graph.length - 1`.  
 * 
 * There are no self edges or parallel edges: `graph[i]` does not contain `i`,
 * and it doesn't contain any element twice.
 * 
 * Example 1:
 * Input: [[1,3], [0,2], [1,3], [0,2]]
 * Output: true
 * Explanation: The graph looks like this:
 * 0----1
 * |    |
 * |    |
 * 3----2
 * We can divide the vertices into two groups: {0, 2} and {1, 3}.
 * 
 * Example 2:
 * Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
 * Output: false
 * Explanation: The graph looks like this:
 * 0----1
 * | \  |
 * |  \ |
 * 3----2
 * We cannot find a way to divide the set of nodes into two independent subsets.
 *
 * @Category Graph-color grouping
 * @Idea 染色法 0=unvisited, 1=black 2=white
 * S1: BFS 从某点出发设成col1,访问其所有邻居并都设为不同颜色col2,再将这些邻居入队进入下一层
 *     将这些邻居的邻居设为和邻居不同的颜色col1, 一旦发现邻居和当前点同色则不是二分图
 * T=O(n) S=O(|E|)
 */
class Solution {
public:
    /**
     * @param graph: the given undirected graph
     * @return:  return true if and only if it is bipartite
     */
    // S1: 染色法 T=O(|E|)边数 S=O(|V|)点数 
    bool isBipartite(vector<vector<int>> &graph) {
        vector<int> colors(graph.size());           // 0=unvisited, 1=black, 2=white
        for (int i = 0; i < graph.size(); ++i) {    // 每个顶点都得作为起点BFS一次
            if (colors[i] != 0) { continue; }       // 访问过则跳过
            colors[i] = 1;                          // 未访问过则设成某种颜色
            queue<int> q{{i}};                      // 入队做种子开始分层扩散
            while (!q.empty()) {                
                int t = q.front(); q.pop();
                for (auto a : graph[t]) {           // 将当前顶点的每个邻居都设成不同的颜色
                    if (colors[a] == colors[t]) { return false; }  // 一旦发现邻居同色则非二分图,终止递归
                    if (colors[a] == 0) {           // 邻居第一次被访问
                        colors[a] = -1 * colors[t]; // 邻居设成和当前相反的颜色
                        q.push(a);                  // 进队递归
                    }
                }
            }
        }
        return true;
    }
};
