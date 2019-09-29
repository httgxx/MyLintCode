/*
 * @lc app=lintcode id=1685 lang=cpp
 *
 * [1685] The mazeIV
 *
 * https://www.lintcode.com/problem/the-mazeiv/description
 *
 * lintcode
 * Medium (55.00%)
 * Total Accepted:    49
 * Total Submissions: 87
 * Testcase Example:  '["S.","#T"]'
 *
 * Give you a map where ‘S’ indicates the starting point and 'T' indicates the
 * ending point. ‘#’ means that the wall is unable to pass, and '.’ means that
 * the road can take a minute to pass. Please find the minimum time it takes to
 * get from the start point to the end point. If the end point cannot be
 * reached, please output -1.
 * 
 * Example
 * input:map=[['S','.'],['#','T']]
 * output:t=2
 * 
 * @Category Maze DFS BFS
 * @Idea
 * 
 * 
 */
class Solution {
public:
    /**
     * @param maps: 
     * @return: nothing
     */
    // BFS + 2维id1维化 + 记录time
    int theMazeIV(vector<vector<char>> &maps) {
        int m = maps.size(), n = maps[0].size();
        int startId = -1, endId = -1;
        for(int i = 0; i < m; i++) {                                // 题目没给,故得找S和T的坐标
            for(int j = 0; j < maps[i].size(); j++) {
                if(maps[i][j] == 'S') { startId = n * i + j; }      // 2维id1维化 // 坑: n*i不是m*i
            	else if (maps[i][j] == 'T') { endId = n * i + j; }
                if (startId >= 0 && endId >= 0) { break; }
            }
        }
        vector<vector<int>> dirs{{0,1},{0,-1},{-1,0},{1,0}};
        unordered_map<int, int> time;                               // 记录时间以及是否访问过
        time[startId] = 0;
        queue<int> q;                                               // q{<x,y>}
        q.push(startId);                                            // S入队列
        while (!q.empty()) {
            auto id = q.front(); q.pop();
            int x = id / n, y = id % n, t = time[id];               // 1维id2维化 // 坑: i/n不是i/n
            if (id == endId) { return t;}                           // 若到达终点,结束返回
            for (auto d : dirs) {                                   // 否则访问邻居 
                int nx = x + d[0], ny = y + d[1];
                int nid = nx * n + ny;                              // 2维id1维化 // 坑: n*nx不是m*nx
                if((nx >= 0 && nx < m && ny >= 0 && ny < n) &&      // 未出界/被访问/撞墙,更新t且入队
                   time.count(nid) == 0 && maps[nx][ny] != '#') {
                    time[nid] = t + 1;
                    q.push(nid);
                }
            }
        }
        return -1;
    }

    struct node
    {
        int x,y,t;
    }S,T;
    int theMazeIV2(vector<vector<char>> &maps) {
        int n=maps.size(), m=maps[0].size();
        for(int i=0;i<maps.size();i++)
            for(int j=0;j<maps[i].size();j++)
                if(maps[i][j]=='S') S.x=i,S.y=j,S.t=0;
            	else  if(maps[i][j]=='T') T.x=i,T.y=j,T.t=0;
        vector<vector<int>> dirs{{0,1},{0,-1},{-1,0},{1,0}};
        unordered_set<int> visited;
        queue<node>q;
        q.push(S);
        while(!q.empty())
        {
            node now=q.front();q.pop();
            if(now.x==T.x&&now.y==T.y) {return now.t;}
            for (auto d : dirs) {  
                node next;
                next.x=now.x+d[0];
                next.y=now.y+d[1];
                next.t=now.t+1;
                if(next.x<0||next.x>=n||next.y<0||next.y>=m) continue;
                if(visited.count(m * next.x + next.y)) continue;
                if(maps[next.x][next.y]=='#') continue;
                visited.insert(m * next.x + next.y);
                q.push(next);
            }
        }
        return -1;
    }
};
