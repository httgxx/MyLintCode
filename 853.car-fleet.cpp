/*
 * @lc app=leetcode id=853 lang=cpp
 *
 * [853] Car Fleet
 *
 * https://leetcode.com/problems/car-fleet/description/
 *
 * algorithms
 * Medium (41.48%)
 * Total Accepted:    20.9K
 * Total Submissions: 50.3K
 * Testcase Example:  '12\n[10,8,0,5,3]\n[2,4,1,1,3]'
 *
 * N cars are going to the same destination along a one lane road.  The
 * destination is target miles away.
 * 
 * Each car i has a constant speed speed[i] (in miles per hour), and initial
 * position position[i] miles towards the target along the road.
 * 
 * A car can never pass another car ahead of it, but it can catch up to it, and
 * drive bumper to bumper at the same speed.
 * 
 * The distance between these two cars is ignored - they are assumed to have
 * the same position.
 * 
 * A car fleet is some non-empty set of cars driving at the same position and
 * same speed.  Note that a single car is also a car fleet.
 * 
 * If a car catches up to a car fleet right at the destination point, it will
 * still be considered as one car fleet.
 * 
 * How many car fleets will arrive at the destination?
 * 
 * Example 1:
 * Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
 * Output: 3
 * Explanation:
 * The cars starting at 10 and 8 become a fleet, meeting each other at 12.
 * The car starting at 0 doesn't catch up to any other car, so it is a fleet by
 * itself.
 * The cars starting at 5 and 3 become a fleet, meeting each other at 6.
 * Note that no other cars meet these fleets before the destination, so the
 * answer is 3.
 * 
 * Note:
 * 0 <= N <= 10 ^ 4
 * 0 < target <= 10 ^ 6
 * 0 < speed[i] <= 10 ^ 6
 * 0 <= position[i] < target
 * All initial positions are different.
 * 
 * @Category pq 
 * @Idea 追赶问题
 * 各车按排位出发,快车追上慢车后将和慢车同速作为一个车队过终点,求过终点的车队数
 * A追上B的条件:单独跑完所需时间A<B(不考虑A追上B后会减到与B同速)
 * 最大堆(堆顶=距离最短,速度最快的车)
 * 每次取堆顶计算该车单独跑完所需时间,若>当前最长耗时,则追不上前面车而自成一个新车队
 */
class Solution {
public:
    // 最大堆(堆顶=距离最短,速度最快的车)
    // 每次取堆顶计算该车单独跑完所需时间,若>当前最长耗时,则追不上前面车而自成一个新车队
    // T=O(nlogn) S=O(n)
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        priority_queue<pair<int, int>> pq;                  // 最大堆
        for (int i = 0; i < position.size(); ++i) {
            pq.push({position[i], speed[i]});               // 堆顶=堆中距离终点(target-position)最近,速度最快的车
        }
        int res = 0;
        double curMaxTime = 0;
        while (!pq.empty()) {
            auto t = pq.top(); pq.pop();                    // 取剩下车中离终点最近最快的车
            double newTime = (double)(target - t.first) / t.second;
            if (newTime <= curMaxTime) { continue; }        // 若该车追得上前面某车(耗时<当前最长耗时),则会在前面某个车队
            curMaxTime = newTime;                           // 若该车追不上前面任何,自成一个新车队
            ++res;                                          // 车队总数+1
        }
        return res;
    }
};
