/*
 * @lc app=lintcode id=1428 lang=cpp
 *
 * [1428] Keys and Rooms
 *
 * https://www.lintcode.com/problem/keys-and-rooms/description
 *
 * lintcode
 * Medium (66.00%)
 * Total Accepted:    146
 * Total Submissions: 218
 * Testcase Example:  '[[1],[2],[3],[]]'
 *
 * There are `N` rooms and you start in room `0`.  Each room has a distinct
 * number in `0, 1, 2, ..., N-1`, and each room may have some keys to access
 * the next room. 
 * 
 * Formally, each room `i` has a list of keys `rooms[i]`, and each key
 * `rooms[i][j]` is an integer in `[0, 1, ..., N-1]` where N = rooms.length.  A
 * key rooms[i][j] = v opens the room with number v.
 * 
 * Initially, all the rooms start locked (except for room 0). 
 * 
 * You can walk back and forth between rooms freely.
 * 
 * Return `true` if and only if you can enter every room.
 * 
 * Example 1:
 * Input: rooms = [[1],[2],[3],[]]
 * Output: true
 * Explanation:  
 * We start in room 0, and pick up key 1.
 * We then go to room 1, and pick up key 2.
 * We then go to room 2, and pick up key 3.
 * We then go to room 3.  Since we were able to go to every room, we return true.
 * 
 * Example 2:
 * Input: rooms = [[1,3],[3,0,1],[2],[0]]
 * Output: false
 * Explanation: We can't enter the room with number 2.
 * 
 * @Category Graph DFS BFS
 * S1: BFS + visited set
 * S2: DFS
 * 
 * 坑: 最后一定别忘检查是否有孤岛!!! return visited.size() == rooms.size(); 
 * 
 */
class Solution {
public:
    /**
     * @param rooms: a list of keys rooms[i]
     * @return: can you enter every room
     */
    // S1: BFS + visited set
    // T=O(n) S=O(n) n为总结点数
    bool canVisitAllRooms(vector<vector<int>> &rooms) {
        unordered_set<int> visited{{0}};
        queue<int> q{{0}};                                          // 从起始点出发
        while (!q.empty()) {
            int t = q.front(); q.pop();                             // 从当前层每个点
            for (int key : rooms[t]) {                              // 扩展到下一层
                if (visited.count(key)) { continue; }               // 跳过访问过的
                visited.insert(key);                                // 标记为访问过
                if (visited.size() == rooms.size()) { return true; }// 全部访问完,完结
                q.push(key);                                        // 没全访问完,继续
            }
        }
        return visited.size() == rooms.size();                      // 坑: 检查是否有孤岛!!!
    }
    // S2: BFS + visited set
    // T=O(n) S=O(n) n为总结点数
    bool canVisitAllRoomsDFS(vector<vector<int>>& rooms) {
        unordered_set<int> visited;
        dfs(rooms, 0, visited);
        return visited.size() == rooms.size();  // 坑: 检查是否有孤岛!!!
    }
    void dfs(vector<vector<int>>& rooms, int cur, unordered_set<int>& visited) {
        visited.insert(cur);                    // 先标记为访问过
        for (int key : rooms[cur]) {            // 再扩展到下一层
            if (!visited.count(key)) {          // 没访问过就递归
                dfs(rooms, key, visited);       // 扩展到的新起点
            }
        }
    }
};
