/*
 * @lc app=lintcode id=1189 lang=cpp
 *
 * [1189] Minesweeper
 *
 * https://www.lintcode.com/problem/minesweeper/description
 *
 * lintcode
 * Medium (45.00%)
 * Total Accepted:    147
 * Total Submissions: 259
 * Testcase Example:  '["EEEEE","EEMEE","EEEEE","EEEEE"]\n[3,0]'
 *
 * Let's play the minesweeper game (Wikipedia, online game)!
 * 
 * You are given a 2D char matrix representing the game board. **'M'**
 * represents an **unrevealed** mine, **'E'** represents an **unrevealed**
 * empty square, **'B'** represents a **revealed** blank square that has no
 * adjacent (above, below, left, right, and all 4 diagonals) mines, **digit**
 * ('1' to '8') represents how many mines are adjacent to this **revealed**
 * square, and finally **'X'** represents a **revealed** mine.
 * 
 * Now given the next click position (row and column indices) among all the
 * **unrevealed** squares ('M' or 'E'), return the board after revealing this
 * position according to the following rules:
 * 
 * 1. If a mine ('M') is revealed, then the game is over - change it to
 * **'X'**.
 * 2. If an empty square ('E') with **no adjacent mines** is revealed, then
 * change it to revealed blank ('B') and all of its adjacent **unrevealed**
 * squares should be revealed recursively.
 * 3. If an empty square ('E') with **at least one adjacent mine** is revealed,
 * then change it to a digit ('1' to '8') representing the number of adjacent
 * mines.
 * 4. Return the board when no more squares will be revealed.
 * 
 * @Category 迷宫 DFS/BFS 
 * @Ideas
 * BFS/DFS T=O(n) S=O(n)
 * - corner case: 若空board: 返回board
 * - case1 触雷: board[row][col]='X' 返回board
 * - case2 空格: 
 *   step1:访问所有邻居: 是M则雷邻居数+1,是E(没访问过)则加邻居到unvisitedEmptyNeighbors[],是B或1~8(访问过)则跳过
 *   step2:更新当前空格: if(雷邻居数>0):空格值=雷邻居数 else:空格值=B 
 *   step3:if(雷邻居数==0):
 *         3.1 更新每个没访问过的空格邻居(for each in unvisitedEmptyNeighbors)值为'B',即设成访问过的空格
 *         3.2 访问该空格邻居 //BFS:入队列   //DFS:递归
 *   返回board
 * 
 */
class Solution {
public:
    /**
     * @param board: a board
     * @param click: the position
     * @return: the new board
     */
    // Sol 2: BFS
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        // corner case: empty board
        if (board.empty() || board[0].empty()) { return {}; }
        int rowCnt = board.size(), colCnt = board[0].size();
        
        queue<pair<int, int>> q({{click[0], click[1]}});
        while(!q.empty()) {
            int row = q.front().first, col = q.front().second, mineCount = 0;
            q.pop();
            // case 1: click mine
            if (board[row][col] == 'M') {
                board[row][col] = 'X';
                return board;
            }
            // case 2: click empty
            // step 1: visit unvisited neighbors
            vector<pair<int, int>> unvisitedEmptyNeighbors;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int newRow = row + i, newCol = col + j;
                    // skip if self or out of board
                    if ((i == 0 && j == 0) ||
                        newRow < 0 || newRow >= rowCnt || newCol < 0 || newCol >= colCnt) {
                        continue;
                    }
                    // count mine neighbors
                    if (board[newRow][newCol] == 'M') { ++mineCount; }
                    // track unvisited empty neighbors //optim: no need to track if found mine neighbor
                    else if (mineCount == 0 && board[newRow][newCol] == 'E') {
                        unvisitedEmptyNeighbors.push_back({newRow, newCol});
                    }
                }
            }
            // step 2: update current empty
            board[row][col] = mineCount == 0 ? 'B' : (mineCount + '0');
            // step 3: if no mine neighbors, enqueue unvisited empty neighbors
            if (mineCount == 0) {
                for (auto neighbor : unvisitedEmptyNeighbors) {
                    board[neighbor.first][neighbor.second] = 'B'; //mark 'E' as 'B' to avoid re-visit
                    q.push(neighbor);
                }
            }
        }
        
        return board;
    }

    // Sol 2: DFS
    vector<vector<char>> updateBoard2(vector<vector<char>>& board, vector<int>& click) {
        // corner case: empty board
        if (board.empty() || board[0].empty()) { return {}; }
        int rowCnt = board.size(), colCnt = board[0].size(), row = click[0], col = click[1], mineCnt = 0;
        
        // case 1: click mine
        if (board[row][col] == 'M') {
            board[row][col] = 'X';
            return board;
        }
        
        // case 2: click empty
        // step 1: visit unvisited neighbors
        vector<vector<int>> unvisitedEmptyNeighbors;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i, newCol = col + j;
                
                // skip if itself or out of board
                if ((i == 0 && j == 0) || newRow < 0 || newRow >= rowCnt ||
                    newCol < 0 || newCol >= colCnt) { continue; }
                
                // count mine neighbors
                if (board[newRow][newCol] == 'M') { ++mineCnt; }
                
                // track unvisited empty neighbor (optim: no need to track if find mine neighbor)
                else if (mineCnt == 0 && board[newRow][newCol] == 'E') { 
                    unvisitedEmptyNeighbors.push_back({newRow, newCol});
                }
                
                // skip revealed/visited neighbors('X','B' or 1~8)
            }
        }
        // step 2: update current empty
        board[row][col] = mineCnt == 0 ? 'B' : (mineCnt + '0');
        // step 3: if no mine neighbors(i.e. all empty), DFS to each unvisited empty neighbor
        if (mineCnt == 0) {
            for (auto neighbor : unvisitedEmptyNeighbors) {
                board[neighbor[0]][neighbor[1]] = 'B'; // Optim!!! Mark as 'B' to avoid re-visit
                updateBoard(board, neighbor);
            }
        }
        return board;
    }
};
