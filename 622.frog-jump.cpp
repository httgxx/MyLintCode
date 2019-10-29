/*
 * @lc app=lintcode id=622 lang=cpp
 *
 * [622] Frog Jump
 *
 * https://www.lintcode.com/problem/frog-jump/description
 *
 * lintcode
 * Hard (34.00%)
 * Total Accepted:    3119
 * Total Submissions: 9006
 * Testcase Example:  '[0,1,3,5,6,8,12,17]\n'
 *
 * A frog is crossing a river. The river is divided into x units and at each
 * unit there may or may not exist a stone. The frog can jump on a stone, but
 * it must not jump into the water.
 * 
 * Given a list of stones' positions (in units) in sorted ascending order,
 * determine if the frog is able to cross the river by landing on the last
 * stone. Initially, the frog is on the first stone and assume the first jump
 * must be 1 unit.
 * 
 * If the frog's last jump was k units, then its next jump must be either `k -
 * 1`, `k`, or `k + 1` units. Note that the frog can only jump in the forward
 * direction.
 * 
 * Example 1: [0,1,3,5,6,8,12,17]
 * There are a total of 8 stones.
 * The first stone at the 0th unit, second stone at the 1st unit, 
 * third stone at the 3rd unit, and so on...
 * The last stone at the 17th unit.
 * Return true. 
 * The frog can jump to the last stone by jumping 
 * 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 
 * 2 units to the 4th stone, then 3 units to the 6th stone, 
 * 4 units to the 7th stone, and 5 units to the 8th stone.
 * 
 * Example 2: [0,1,2,3,4,8,9,11]
 * Return false. There is no way to jump to the last stone as 
 * the gap between the 5th and 6th stone is too large.
 * 
 * @Category DP or Recursion+MemorySearch
 * @Idea 动规 或 递归+记忆搜索
 * S1: 递归+记忆搜索
 * 
 * 
 * 
 * S2: 动规
 * 
 */
class Solution {
public:
    /**
     * @param stones: a list of stones' positions in sorted ascending order
     * @return: true if the frog is able to cross the river or false
     */
    // 递归+记忆搜索
    // 每到达一个位置,找出下一跳能跳到的所有石头,对每个新位置递归,直到绝路或已到(新位置>=终点),记忆结果并返回上层递归
    // T=O(n^2) S=O(n)
    bool canCross(vector<int> &stones) {
        unordered_map<int, bool> m;                         // 记忆搜索
        return helper(stones, 0, 0, m);                     // 递归
    }
    bool helper(vector<int>& stones, int pos, int jump,     // jump=上一跳(到当前位置pos)跳的距离
                unordered_map<int, bool>& m) {              //      这一跳只能jump-1,jump,或jump+1
        int n = stones.size(), key = pos | jump << 11;      // 巧:pos和jump值存到1个int里
        if (pos >= n - 1) { return true; }                  // 已达/超终点,返回true不用记忆(why?)
        if (m.count(key)) { return m[key]; }                // 以前到过当前位置,返回记忆结果
        for (int i = pos + 1; i < n; ++i) {                 // 首次到达当前位置,扫描剩下的每个石头
            int dist = stones[i] - stones[pos];             //     计算该石头到当前位置的距离(看是否能跳到)
            if (dist < jump - 1) { continue; }              //     石头太近跳不到,继续看下个石头
            if (dist > jump + 1) { return m[key] = false; } //     石头太远跳不到,绝路走不下去,返回false并记忆
            if (helper(stones, i, dist, m)) {               //     石头可跳到,递归表明可达终点,返回true并记忆
                return m[key] = true;
            }
        }
        return m[key] = false;                              //  从剩下的所有石头都没法到终点,绝路,返回false并记忆
    }
};
