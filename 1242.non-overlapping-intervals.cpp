/*
 * @lc app=lintcode id=1242 lang=cpp
 *
 * [1242] Non-overlapping Intervals
 *
 * https://www.lintcode.com/problem/non-overlapping-intervals/description
 *
 * lintcode
 * Medium (57.00%)
 * Total Accepted:    413
 * Total Submissions: 713
 * Testcase Example:  '[(1,2),(2,3),(3,4),(1,3)]'
 *
 * Given a collection of intervals, find the minimum number of intervals you
 * need to remove to make the rest of the intervals non-overlapping.
 * 
 * Example 1:
 * Input: [ [1,2], [2,3], [3,4], [1,3] ]
 * Output: 1
 * Explanation: [1,3] can be removed and the rest of intervals are non-overlapping
 * 
 * Example 2:
 * Input: [ [1,2], [1,2], [1,2] ]
 * Output: 2
 * Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
 * 
 * Example 3:
 * Input: [ [1,2], [2,3] ]
 * Output: 0
 * Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
 * 
 * @Category Interval greedy 
 * @Idea 空间问题 贪婪法
 * 先按开始时间升序排序,新start<旧end来找重叠,每遇重叠则删除区间数+1,且删end大的使删的区间数最少
 * 不真删只记录当前最后区间index,用来继续找重叠和决定删哪个
 * T=O(n) S=O(1)
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
    /**
     * @param intervals: a collection of intervals
     * @return: the minimum number of intervals you need to remove
     */
    // 先按开始时间升序排序,新start<旧end来找重叠,每遇重叠则删除区间数+1,且删end大的使删的区间数最少
    // 不真删只记录当前最后区间index,用来继续找重叠和决定删哪个
    // T=O(nlogn) S=O(1)
    struct lessThan {
        inline bool operator() (const Interval & a, const Interval & b) {
            return a.start < b.start;
        }
    };
    int eraseOverlapIntervals(vector<Interval> &intervals) {
        if (intervals.empty()) { return 0; }                    // 无区间特例:快速返回   
        int res = 0, n = intervals.size(), last = 0;            // last=当前最后区间index
        sort(intervals.begin(), intervals.end(), lessThan());   // 先按start先后排序 O(nlogn)
        for (int i = 1; i < n; ++i) {                           // 坑: 跳过i=0从i=1开始,可处理无区间的特例
            if (intervals[i].start < intervals[last].end) {     // 若遇到重叠:新start<旧end
                ++res;                                          //   需删区间数+1
                if (intervals[i].end < intervals[last].end) {   //   需删end大的,若新end<last.end需删last改新区间为last,否则跳过新区间last不动
                    last = i;                                   //   不用真删,只用记录留下的区间index
                }
            }
            else { last = i; }                                  // 若未遇重叠:更新last
        }
        return res;
    }
};
