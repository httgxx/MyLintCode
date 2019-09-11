/*
 * @lc app=lintcode id=941 lang=cpp
 *
 * [941] Sliding Puzzle
 *
 * https://www.lintcode.com/problem/sliding-puzzle/description
 *
 * lintcode
 * Hard (49.00%)
 * Total Accepted:    622
 * Total Submissions: 1244
 * Testcase Example:  '[[1,2,3],[4,0,5]]'
 *
 * On a `2x3 board`, there are `5` tiles represented by the integers `1`
 * through `5`, and an empty square represented by `0`.
 * 
 * A move consists of choosing 0 and a 4-directionally adjacent number and
 * swapping it.
 * 
 * The state of the board is solved if and only if the `board` is
 * `[[1,2,3],[4,5,0]].`
 * 
 * Given a puzzle board, return the least number of moves required so that the
 * state of the board is solved. If it is impossible for the state of the board
 * to be solved, return `-1`.
 * 
 * Example 1:
 * Given board = `[[1,2,3],[4,0,5]]`, return `1`.
 * Explanation: Swap the 0 and the 5 in one move.
 * 
 * Example 2：
 * Given board = `[[1,2,3],[5,4,0]]`, return `-1`.
 * Explanation: No number of moves will make the board solved.
 * 
 * Example 3:
 * Given board = `[[4,1,2],[5,0,3]]`, return `5`.
 * Explanation: 5 is the smallest number of moves that solves the board.
 * An example path:
 * After move 0: [[4,1,2],[5,0,3]]
 * After move 1: [[4,1,2],[0,5,3]]
 * After move 2: [[0,1,2],[4,5,3]]
 * After move 3: [[1,0,2],[4,5,3]]
 * After move 4: [[1,2,0],[4,5,3]]
 * After move 5: [[1,2,3],[4,5,0]]
 * 
 * Example 4:
 * Given board = `[[3,2,4],[1,5,0]]`, return `14`.
 * 
 * @Category BFS + 状态编码
 * dirs[当前0的位置]={当前0可移到的所有可能位置}
 * 状态编码=按行扫描
 * unordered_set<string> visited记录访问过的状态编码
 * 
 * 坑: 每层++res,在for()之外但是while之内
 * 坑: 最后(while之外)return -1而不是return res
 */
class Solution {
public:
    /**
     * @param board: the given board
     * @return:  the least number of moves required so that the state of the board is solved
     */
    // BFS + 状态编码 T=O(n) S=O(n)
    int slidingPuzzle(vector<vector<int>> &board) {
        int res = 0, m = board.size(), n = board[0].size();
        // 0 1 2
        // 3 4 5 
        // dirs[index=0所在位置]={0可以移动到的位置}, e.g. 0在位置2,可移动到位置1和5
        vector<vector<int>> dirs = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};
        string start = "", target = "123450";               // 设立目标状态
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                start += to_string(board[i][j]);            // 编码初始状态
            }
        }
        unordered_set<string> visited {start};              // 记录访问过的状态集用以避重
        queue<string> q{{start}};
        while (!q.empty()) {
            for (int i = q.size() - 1; i >=0; --i) {
                string curState = q.front(); q.pop();
                if (curState == target) { return res; }     // 已达目标,立即退出
                int curZeroPos = curState.find("0");        // 找到当前"0"的位置
                for (auto nextZeroPos : dirs[curZeroPos]) { // 找"0"可移到的位置
                    string nextState = curState;
                    swap(nextState[nextZeroPos], nextState[curZeroPos]);// 移"0"到新位置
                    if (visited.count(nextState)) continue; // 若访问过改状态则跳过
                    visited.insert(nextState);
                    q.push(nextState);                      // 若没访问过入队新状态
                }
            }
            ++res;                                          // 必须在for之外才是一层
        }
        return -1;
    }
};
