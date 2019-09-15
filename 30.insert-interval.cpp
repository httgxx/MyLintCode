/*
 * @lc app=lintcode id=30 lang=cpp
 *
 * [30] Insert Interval
 *
 * https://www.lintcode.com/problem/insert-interval/description
 *
 * lintcode
 * Medium (26.00%)
 * Total Accepted:    15359
 * Total Submissions: 57309
 * Testcase Example:  '[(1,2),(5,9)]\n(2,5)'
 *
 * Given a non-overlapping interval list which is sorted by start point.
 * 
 * Insert a new interval into it, make sure the list is still in order and
 * `non-overlapping` (merge intervals if necessary).
 * 
 * Example 1:
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 * 
 * Example 2:
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 * Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 * 
 * @Category Interval
 * @Idea 
 * 扫描一遍,不重叠则直接加入结果集(若在新区间前则更新插入新区间的位置),重叠则合并到新区间,最后再插入新区间
 *    if [当前]<[新],不重叠,加[当前]到res,且插入[新]的位置后移
 *    else if [新]<[当前],不重叠,加[当前]到res,但插入[新]的位置不变
 *    else 有重叠,合并[当前]到[新],暂时不加入res
 * 最后再在要插[新]的地方插入[新]
 */
/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    // T=O(n) S=O(n)若不计结果集则O(1)
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> res;
        int n = intervals.size(), cur = 0;
        for (int i = 0; i < n; ++i) {
            if (intervals[i].end < newInterval.start) {         // [当前]<[新],不重叠,加[当前]到res,且插入[新]的位置后移
                res.push_back(intervals[i]);
                ++cur;
            } else if (intervals[i].start > newInterval.end) {  // [新]<[当前],不重叠,加[当前]到res,但插入[新]的位置不变
                res.push_back(intervals[i]);
            } else {                                            // 有重叠,合并[当前]到[新],暂时不加入res
                newInterval.start = min(newInterval.start, intervals[i].start);  
                newInterval.end = max(newInterval.end, intervals[i].end);
            }
        }
        res.insert(res.begin() + cur, newInterval);             // 在要插[新]的地方插入[新]
        return res;
    }
};