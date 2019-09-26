/*
 * @lc app=lintcode id=1002 lang=cpp
 *
 * [1002] Bus Routes
 *
 * https://www.lintcode.com/problem/bus-routes/description
 *
 * lintcode
 * Medium (44.00%)
 * Total Accepted:    583
 * Total Submissions: 1280
 * Testcase Example:  '[[1,2,7],[3,6,7]]\n1\n6'
 *
 * Given a list `routes`, and `routes[i]` is the circular route of the i-th
 * bus. For example, if `routes[0] = [1, 5, 7]`, the first bus travels in the
 * sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 ... forever.
 * 
 * Given `S` and `T`. Travelling by buses only, what is the least number of
 * buses we need take to reach `T` from `S` ? Return `-1` if it is not possible.
 * 
 * Example 1:
 * Input: routes = [[1, 2, 7], [3, 6, 7]], S = 1, T = 6
 * Output: 2
 * Explanation: Take the first bus to the bus stop 7, and then take the second bus to 6.
 * 
 * Example 2:
 * Input: routes = [[1], [15, 16, 18], [3, 4,12,14]], S = 3, T = 15
 * Output: -1
 * Explanation: There is no way to get 15 from 3.
 * 
 * Note:
 * 1 <= routes.length <= 500.
 * 1 <= routes[i].length <= 500.
 * 0 <= routes[i][j] < 10 ^ 6.
 * 
 * @Category 迷宫最短路径 BFS
 * @Idea
 * 图:点={站},边={站->站} 站=>站上能搭乘的公交=>公交能到的下1站
 * 求站S到站T要换乘的最少公交数 = 各种公交换乘方案中,公交换乘次数最少的那个(公交数最少而不是站最少!!)  
 * BFS分层遍历,每层从1个站通过换1个没坐过的公交(坐过表明从那车可直接达到当前站),到达目标站时终止遍历
 * 站->公交->站,所以既要公交->站的map(已给routes),也要站->公交的map(需要根据前者创建)
 */
class Solution {
public:
    /**
     * @param routes:  a list of bus routes
     * @param S: start
     * @param T: destination
     * @return: the least number of buses we must take to reach destination
     */
    // 图:点={站},边={站->站} 站=>站上能搭乘的公交=>公交能到的下1站
    // 求站S到站T要换乘的最少公交数 = 各种公交换乘方案中,公交换乘次数最少的那个(公交数最少而不是站最少!!)  
    // S1:BFS分层遍历,每层从1个站通过换1个没坐过的公交(坐过表明从那车可直接达到当前站),到达目标站时终止遍历
    int numBusesToDestination(vector<vector<int>> &routes, int S, int T) {
        if (S == T) { return 0; }                           // 特例
        unordered_map<int, vector<int>> stop2bus;           // 创建站->公交的map
        for (int bus = 0; bus < routes.size(); ++bus) {     // 根据公交线路->站的map创建站->公交的map
            for (int stop : routes[bus]) {
                stop2bus[stop].push_back(bus);
            }
        }
        int res = 0;
        unordered_set<int> visitedBus;                      // 重复访问同公交则不应该再继续走,说明该公交先头不换乘也能直接到达当前站,故
        queue<int> q{{S}};
        while (!q.empty()) {
            ++res;
            for (int i = q.size(); i > 0; --i) {            // 从当前层每个站通过换乘1个公交进入下一层
                int stop = q.front(); q.pop();
                for (int bus : stop2bus[stop]) {            // 站(当前层)->公交
                    if (visitedBus.count(bus)) { continue; }//   跳过已访问过的公交
                    visitedBus.insert(bus);                 //   标记公交为已访问过
                    for (int stop : routes[bus]) {          // 公交->站(下一层)
                        if (stop == T) { return res; }      //   若到达目标站,结束遍历
                        q.push(stop);                       //   否则站入队列作为下一层继续遍历
                    }
                }
            }
        }
        return -1;                                          // 坑:此处才返回说明没有办法到达终点T
    }
};
