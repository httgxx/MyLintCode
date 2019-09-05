/*
 * @lc app=lintcode id=1298 lang=cpp
 *
 * [1298] Minimum Height Trees
 *
 * https://www.lintcode.com/problem/minimum-height-trees/description
 *
 * lintcode
 * Medium (31.00%)
 * Total Accepted:    755
 * Total Submissions: 2417
 * Testcase Example:  '4\n[[1,0],[1,2],[1,3]]'
 *
 * For a undirected graph with tree characteristics, we can choose any node as
 * the root. The result graph is then a rooted tree. Among all possible rooted
 * trees, those with minimum height are called minimum height trees (MHTs).
 * Given such a graph, write a function to find all the MHTs and return a list
 * of their root labels.
 * 
 * **Format**
 * The graph contains `n` nodes which are labeled from `0` to `n - 1`. You will
 * be given the number n and a list of undirected `edges` (each edge is a pair
 * of labels).
 * 
 * You can assume that no duplicate edges will appear in `edges`. Since all
 * edges are undirected, `[0, 1]` is the same as `[1, 0]`and thus will not
 * appear together in edges.
 * 
 * Example1
 * Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]
 * Output: [1]
 * Explanation:
 *         0
 *         |
 *         1
 *        / \
 *       2   3
 * Example2
 * 
 * Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
 * Output: [3, 4]
 * Explanation:
 *      0  1  2
 *       \ | /
 *         3
 *         |
 *         4
 *         |
 *         5
 * 
 * @Category Tree Graph BFS
 * @Idea
 * 找根=>图最中心的点=>到每个最边缘的点(叶子结点,度为的点)的距离的最大值要最小(这个最大值就是树的高度)
 * =>每个叶子同步往中间走,多个相遇则合并为一,最后只剩1个或2个时就是中心/根(因为>=3个结点时无环则必有一个不是叶子,它到其他点的最长距离一定最小)
 * =>从每个度为1的点入队列,开始分层剥洋葱,出队列所有这些点后将度数变为1的点入队列,依次下去直到队列只剩1或2个结点
 */
class Solution {
public:
    /**
     * @param n: n nodes labeled from 0 to n - 1
     * @param edges: a undirected graph
     * @return:  a list of all the MHTs root labels
     */
    // BFS T=O(n) S=O(n)
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
        if (n == 0) { return {}; }   // 特例:空图
        if (n == 1) { return {0}; }  // 特例:单点
        
        vector<unordered_set<int>> nbrs(n);        // 边集合=>邻接矩阵 用set可高效去重
        for (auto edge : edges) {
            nbrs[edge[0]].insert(edge[1]);         // 坑:不是vector<pair<int,int>>不能用e.first
            nbrs[edge[1]].insert(edge[0]);
        }
        
        queue<int> q;
        for (int i = 0; i < n; ++i) {                   // 初始:度为1的点/叶子入队列
            if (nbrs[i].size() == 1) { q.push(i); }
        }
        while (n > 2) {                                 // 分层剥洋葱/叶子结点
            int cnt = q.size();                         
            n -= cnt;
            for (int i = 0; i < cnt; ++i) {
                int cur = q.front(); q.pop();
                for (auto nbr : nbrs[cur]) {
                    nbrs[nbr].erase(cur);               // 把叶子从其邻居的邻居集中删除 
                    if (nbrs[nbr].size() == 1) { q.push(nbr); }  // 新叶子入队列
                }
            }
        }
        
        vector<int> roots;
        while (!q.empty()) {  // 最后剩1个点则是中心/根, 或剩2个点则都可作为中心/根,所以全部返回
            roots.push_back(q.front());
            q.pop();
        }
        return roots;
    }
};
