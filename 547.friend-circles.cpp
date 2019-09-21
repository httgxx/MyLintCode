/*
 * @lc app=leetcode id=547 lang=cpp
 *
 * [547] Friend Circles
 *
 * https://leetcode.com/problems/friend-circles/description/
 *
 * algorithms
 * Medium (55.00%)
 * Total Accepted:    104.9K
 * Total Submissions: 190.4K
 * Testcase Example:  '[[1,1,0],[1,1,0],[0,0,1]]'
 * 
 * There are N students in a class. Some of them are friends, while some are
 * not. Their friendship is transitive in nature. For example, if A is a direct
 * friend of B, and B is a direct friend of C, then A is an indirect friend of
 * C. And we defined a friend circle is a group of students who are direct or
 * indirect friends.
 * 
 * Given a N*N matrix M representing the friend relationship between students
 * in the class. If M[i][j] = 1, then the ith and jth students are direct
 * friends with each other, otherwise not. And you have to output the total
 * number of friend circles among all the students.
 * 
 * Example 1:
 * Input: 
 * [[1,1,0],
 * ⁠[1,1,0],
 * ⁠[0,0,1]]
 * Output: 2
 * Explanation:The 0th and 1st students are direct friends, so they are in a
 * friend circle. The 2nd student himself is in a friend circle. So return 2.
 * 
 * Example 2:
 * Input: 
 * [[1,1,0],
 * ⁠[1,1,1],
 * ⁠[0,1,1]]
 * Output: 1
 * Explanation:The 0th and 1st students are direct friends, the 1st and 2nd
 * students are direct friends, so the 0th and 2nd students are indirect
 * friends. All of them are in the same friend circle, so return 1.
 * 
 * Note:
 * N is in range [1,200].
 * M[i][i] = 1 for all students.
 * If M[i][j] = 1, then M[j][i] = 1.
 * 
 * @Category Graph, Connected Components, Union Find
 * @Idea
 * S1: Union Find 联合查找 // T=O(logN) S=O(n)
 * 注:DFS和BFS也能检查2点间是否有路径,但复杂度更高: T=O(n)
 * - Union:联通2点 T=O(logN)
 * - Find: 检查2点是否联通(有path/有共同祖先) T=O(logn)
 */
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size(), res = n;                  // 坑:初始化孤岛数为n,即所有点单独为孤岛
        vector<int> root(n);
        for (int i = 0; i < n; ++i) { root[i] = i; }// 初始化:各点的根设为自身 
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {       // 对于每条边(顶点为i,j)
                if (M[i][j] == 1) {                 
                    int p1 = findFoot(root, i);     // Find: 找i的根
                    int p2 = findFoot(root, j);     // Find: 找j的根
                    if (p1 != p2) {                 // 两根不同则连通两根 // 坑:连通的不是“边的顶点"而是“边的顶点的祖先"
                        root[p2] = p1;
                        --res;                      // -1: 2点联通后少了一个孤岛
                    }
                }
            }   
        }
        return res;
    }
    int findFoot(vector<int>& root, int i) {        // 找i的根
        while (i != root[i]) {                      // 找当前祖先的父亲,直到发现其父亲是其自己(根)
            root[i] = root[root[i]];                // 压缩路径
            i = root[i];
        }
        return i;                                   // 返回根
    }
};
