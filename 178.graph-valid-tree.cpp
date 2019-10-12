/*
 * @lc app=lintcode id=178 lang=cpp
 *
 * [178] Graph Valid Tree
 *
 * https://www.lintcode.com/problem/graph-valid-tree/description
 *
 * lintcode
 * Medium (31.00%)
 * Total Accepted:    27771
 * Total Submissions: 86861
 * Testcase Example:  '5\n[[0,1],[0,2],[0,3],[1,4]]\n'
 *
 * Given `n` nodes labeled from `0` to `n - 1` and a list of `undirected` edges
 * (each edge is a pair of nodes), write a function to check whether these
 * edges make up a valid tree.
 * 
 * Example 1:
 * Input: n = 5 edges = [[0, 1], [0, 2], [0, 3], [1, 4]]
 * Output: true.
 * 
 * Example 2:
 * Input: n = 5 edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]]
 * Output: false.
 * 
 * @Category Union Find
 * @Idea Union Find
 * Tree需要Graph连通且无环
 * Union Find合并连通的点到相同连通区间,若最后只有一个连通区间则
 */
class Solution {
public:
    /**
     * @param n: An integer
     * @param edges: a list of undirected edges
     * @return: true if it's a valid tree, or false
     */
    // Graph是树的要求: 连通且无环
    // T=O(|V|=|E|) S=O(|V|)
    bool validTree(int n, vector<vector<int>> &edges) {
        vector<int> roots(n, -1);                   // 初始化为-1
        for (auto a : edges) {                      // 每条边的两端点分别找root
            int x = find(roots, a[0]);
            int y = find(roots, a[1]);
            if (x == y) { return false; }           // 若已经同root说明之前已经连通,则加此边就形成环=>非树
            roots[x] = y;                           // 否则将一端设为另一端儿子
        }
        return edges.size() == n - 1;               // 若有孤岛则不连通=>非树
    }
    int find(vector<int> &roots, int i) {           // 坑:不能
        while (roots[i] != -1) { i = roots[i]; }
        return i;
    }
};
