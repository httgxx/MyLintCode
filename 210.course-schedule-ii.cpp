/*
 * @lc app=leetcode id=210 lang=cpp
 *
 * [210] Course Schedule II
 *
 * https://leetcode.com/problems/course-schedule-ii/description/
 *
 * algorithms
 * Medium (36.23%)
 * Total Accepted:    172.8K
 * Total Submissions: 476.4K
 * Testcase Example:  '2\n[[1,0]]'
 *
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 * 
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 * 
 * Given the total number of courses and a list of prerequisite pairs, return
 * the ordering of courses you should take to finish all courses.
 * 
 * There may be multiple correct orders, you just need to return one of them.
 * If it is impossible to finish all courses, return an empty array.
 * 
 * Example 1:
 * Input: 2, [[1,0]] 
 * Output: [0,1]
 * Explanation: There are a total of 2 courses to take. To take course 1 you
 * should have finished   
 * course 0. So the correct course order is [0,1] .
 * 
 * Example 2:
 * Input: 4, [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,1,2,3] or [0,2,1,3]
 * Explanation: There are a total of 4 courses to take. To take course 3 you
 * should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you
 * finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is
 * [0,2,1,3] .
 * 
 * Note:
 * The input prerequisites is a graph represented by a list of edges, not
 * adjacency matrices. Read more about how a graph is represented.
 * You may assume that there are no duplicate edges in the input
 * prerequisites.
 * 
 * @Category Topologic Sort
 * @Idea
 * 所有入度为0的点入队列,依次取出各点并将依赖该点的邻居点入度-1,若邻居入度变为0则也入队列
 * 入度为0的点出队列时入res, 最后检查是否res.size()==总点数
 */
class Solution {
public:
    // S1: 拓扑排序 T=O(|V|+|E|), S=O(|V|)
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses, vector<int>());
        vector<int> in(numCourses);
        for (vector<int> p : prerequisites) {       // O(|E|)
            graph[p[1]].push_back(p[0]);            // 创建有向图graph邻接表:p[1]->p[0]
            ++in[p[0]];                             // 统计入度:p[0]的预备课是p[1],p[1]须早于p[0],p[1]->p[0],p[0]入度+1
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {      // O(|V|)
            if (in[i] == 0) { q.push(i); }          // 入度为0的点入队列
        }
        
        vector<int> res;
        while (!q.empty()) {                        // 拓扑排序 O(|V|+|E|)
            int cur = q.front(); q.pop();
            res.push_back(cur);                     // 坑: 这里入结果集最省code
            for (auto nbr : graph[cur]) {           // 去掉cur之后将所有依赖cur的neighbor的入度-1
                --in[nbr];
                if (in[nbr] == 0) { q.push(nbr); }  // 入度减为0则入队列
            }
        }
        
        vector<int> empty{};
        return res.size() == numCourses ? res : empty; // 若所有点都入了结果集则可以完成所有课程
    }
};
