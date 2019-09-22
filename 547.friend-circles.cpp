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
    // Union Find T=O(logn) S=O(n))
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size(), compCnt = n;              // 坑: 总模块数初始=n即个点各在一个模块
        vector<int> root(n);
        initRoots(root);                            // 初始化每个点的根为自己
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (M[i][j] == 1) {                 // 每对相连的点
                    connect(root, i, j, compCnt);   // 若不在同模块: 合并两点所在模块,总模块数-1
                }
            }
        }
        return compCnt;                                 // 返回最后总模块数
    }
private:
    void initRoots(vector<int>& root) {             // 初始化root[] // T=O(n), S=O(n)
        for (int i = 0; i < root.size(); ++i) {
            root[i] = i;                            // 各点的根为自己
        }
    }
    void connect(vector<int>& root, int i, int j, int& compCnt){ // 合并i和j所在的模块 // T=O(logn) S=O(1)
        int rooti = find(root, i);                  // 找到i的根
        int rootj = find(root, j);                  // 找到j的根
        if (rooti == rootj) { return; }             // 若同根/同模块,返回
        root[rootj] = rooti;                       // 否则合并两模块:让i的根成为j的根的父亲=>j的模块加入i的模块成为子模块
        --compCnt;                                  // 总模块数-1  // 下次find(j模块里的点)时再压缩路径
    }
    int find(vector<int>& root, int i) {            // 找i的根 // T=O(logn) S=O(1)
        while (i != root[i]) {                      // 将根的根设为根,直到根为自己(模块的根))
            root[i] = root[root[i]];                // 压缩i到根的路径
            i = root[i];
        }
        return i;                                   // 返回i的根
    }
};
