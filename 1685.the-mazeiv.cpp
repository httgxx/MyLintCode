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
    // BFS + 
    int theMazeIV1(vector<vector<char>> &maps) {
        int m = maps.size(), n = maps[0].size();
        int startX, startY, endX, endY;
        for(int i = 0; i < m; i++) {                                            // 题目没给,故得找S和T的坐标
            for(int j = 0; j < maps[i].size(); j++) {
                if(maps[i][j] == 'S') {
                    startX = i;
                    startY = j;
                }
            	else if (maps[i][j] == 'T') {
                    endX = i;
                    endY = j;
                }
            }
        }
        vector<vector<bool>> visited(m, vector<bool>(n, false));                // 记录到达各点的时间
        visited[startX][startY] = true;                                         // 设S为已访问过
        vector<vector<int>> time(m, vector<int>(n, 0));                         // 记录到达各点的时间
        time[startX][startY] = 0;                                               // 到达S的时间=0
        vector<vector<int>> dirs{{0,1},{0,-1},{-1,0},{1,0}};
        queue<pair<int, int>> q;                                                // q{<x,y>}
        q.push({startX, startY});                                               // T入队列
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            int tx = t.first, ty = t.second, tTime = time[tx][ty];
            if (tx == endX && ty == endY) { return tTime; }          // 若到达终点,结束返回
            for (auto d : dirs) {                                               // 否则访问邻居 
                int x = tx + d[0], y = ty + d[1], curTime = tTime + 1;
                if(x < 0 || x >= n || y < 0|| y >= m) continue;
                if(visited[x][y] == 1) continue;
                if(maps[x][y] == '#') continue;
                visited[x][y] = true;
                q.push({x, y});
            }
        }
    }
    struct node
    {
        int x,y,t;
    }S,T;
    int theMazeIV(vector<vector<char>> &maps) {
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
