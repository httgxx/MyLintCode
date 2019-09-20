/*
 * @lc app=lintcode id=796 lang=cpp
 *
 * [796] Open the Lock
 *
 * https://www.lintcode.com/problem/open-the-lock/description
 *
 * lintcode
 * Hard (44.00%)
 * Total Accepted:    1304
 * Total Submissions: 2942
 * Testcase Example:  '["0201","0101","0102","1212","2002"]\n"0202"'
 *
 * You have a lock in front of you with 4 circular wheels. Each wheel has 10
 * slots: `'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'`. The wheels can
 * rotate freely and wrap around: for example we can turn `'9'` to be `'0'`, or
 * `'0'` to be `'9'`. Each move consists of turning one wheel one slot.
 * 
 * The lock initially starts at `'0000'`, a string representing the state of
 * the 4 wheels.
 * 
 * You are given a list of `deadends` dead ends, meaning if the lock displays
 * any of these codes, the wheels of the lock will stop turning and you will be
 * unable to open it.
 * 
 * Given a `target` representing the value of the wheels that will unlock the
 * lock, return the minimum total number of turns required to open the lock, or
 * -1 if it is impossible.
 * 
 * Example 1:
 * Given deadends = ["0201","0101","0102","1212","2002"], target = "0202"
 * Return 6
 * Explanation:
 * A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
 * Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
 * because the wheels of the lock become stuck after the display becomes the dead end "0102".
 * 
 * Example 2:
 * Given deadends = ["8888"], target = "0009"
 * Return 1
 * Explanation: We can turn the last wheel in reverse to move from "0000" -> "0009".
 * 
 * Note:
 * The length of deadends will be in the range [1, 500].
 * target will not be in the list deadends.
 * Every string in deadends and the string target will be a string of 4 digits from the 10,000 possibilities 
 * '0000' to '9999'.
 * 
 * @Category 迷宫最短路径+障碍物 BFS
 * @Idea
 * 原型: 4位数字每位分别加1减1=>共8个邻居
 * 难点: 如何处理9+1=>0和0-1=>9? +10后+1或-1再对10取模,即第i位变为t[i]=((s[i]-'0')+10+d)%10 + '0';
 * 思路: BFS + deadlock_set + visited_set //T=O(n) S=O(n)
 * - 首先检查是否在deadlock_set,是则返回-1
 * - 然后起始值'0000'入队列+入visited_set
 *     ++layer
 *     for 队列中每个元素
 *         for 每一位作加1或者减1的一步变换(4位*2=8个邻居)
 *             if(变换后的值==target) 返回 layer
 *             if(没被访问过&&不是deadlock) 变换后的值入队列
 *             变换后的值加入visited_set 
 * - 结束BFS后还没返回,说明没找到target,返回-1
 * 
 * // 坑: 最后结束BFS后还未返回,则返回-1而不是layer
 *    
 */
class Solution {
public:
    /**
     * @param deadends: the list of deadends
     * @param target: the value of the wheels that will unlock the lock
     * @return: the minimum total number of turns 
     */
    // BFS 迷宫最短路径+障碍物
    int openLock(vector<string> &deadends, string &target) {
        unordered_set<string> deadlock(deadends.begin(), deadends.end());
        if (deadlock.count("0000")) { return -1; }                 
        int res = 0;
        unordered_set<string> visited{{"0000"}};
        queue<string> q{{"0000"}};
        while (!q.empty()) {
            ++res;
            for (int k = q.size(); k > 0; --k) {
                auto t = q.front(); q.pop();
                for (int i = 0; i < t.size(); ++i) {
                    for (int j = -1; j <= 1; ++j) {                     // 4位数字每位分别加1减1=>共8个邻居
                        if (j == 0) { continue; }                       // 须+1或-1,跳过+0
                        string str = t;
                        str[i] = ((t[i] - '0') + 10 + j) % 10 + '0';    // 变换后的值,处理9+1=>0和0-1=>9的情况
                        if (str == target) { return res; }              // 变成目标值,返回路径长(最短)
                        if (!visited.count(str) && !deadlock.count(str)) { q.push(str); } // 未访问非死锁的值入队列
                        visited.insert(str);                            // 标记访问以去重
                    }
                }
            }
        }
        return -1;                                                      // 坑: 返回-1而不是res
    }
};
