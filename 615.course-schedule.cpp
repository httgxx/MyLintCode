/*
 * @lc app=lintcode id=615 lang=cpp
 *
 * [615] Course Schedule
 *
 * https://www.lintcode.com/problem/course-schedule/description
 *
 * lintcode
 * Medium (33.00%)
 * Total Accepted:    14399
 * Total Submissions: 43393
 * Testcase Example:  '2\n[[1,0]]\n'
 *
 * There are a total of n courses you have to take, labeled from `0` to `n -
 * 1`.
 * 
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 * 
 * Given the total number of courses and a list of prerequisite pairs, is it
 * possible for you to finish all courses?
 * 
 * Example 1:
 * Input: n = 2, prerequisites = [[1,0]] 
 * Output: true
 * 
 * Example 2:
 * Input: n = 2, prerequisites = [[1,0],[0,1]] 
 * Output: false
 * 
 * @Category Topologic Sort
 * @Idea 拓扑排序 T=O(|V|+|E|), S=O(|V|)
 * 所有入度为0的点入队列,依次取出各点并将依赖该点的邻居点入度-1,若邻居入度变为0则也入队列
 * 用一个counter同步统计入度为0的点的个数, 最后检查是否counter==总点数
 */
class Solution {
public:
    /*
     * @param numCourses: a total of n courses
     * @param prerequisites: a list of prerequisite pairs
     * @return: true if can finish all courses or false
     */
    // S1: 拓扑排序 T=O(|V|+|E|), S=O(|V|)
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> graph(numCourses, vector<int>());
        vector<int> in(numCourses);
        for (pair<int, int> p : prerequisites) {    // O(|E|)
            graph[p.second].push_back(p.first);     // 创建有向图graph邻接表:p[1]->p[0]
            ++in[p.first];                           // 统计入度:p[0]的预备课是p[1],p[1]须早于p[0],p[1]->p[0],p[0]入度+1
        }
        int zeroInCnt = 0;
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {      // O(|V|)
            if (in[i] == 0) {
                q.push(i);                          // 入度为0的点入队列, 且统计个数
                ++zeroInCnt;
            }
        }
        while (!q.empty()) {                        // 拓扑排序 O(|V|+|E|)
            int cur = q.front(); q.pop();
            for (auto nbr : graph[cur]) {           // 去掉cur之后将所有依赖cur的neighbor的入度-1
                --in[nbr];
                if (in[nbr] == 0) {
                    q.push(nbr);
                    ++zeroInCnt;                    // 入度减为0则入队列, 且统计个数
                }
            }
        }
        return zeroInCnt == numCourses;             // 若所有点入度都为0则可以完成所有课程
    }
};
