/*
 * @lc app=lintcode id=156 lang=cpp
 *
 * [156] Merge Intervals
 *
 * https://www.lintcode.com/problem/merge-intervals/description
 *
 * lintcode
 * Easy (27.00%)
 * Total Accepted:    17898
 * Total Submissions: 65632
 * Testcase Example:  '[(1,3)]\n'
 *
 * Given a collection of intervals, merge all overlapping intervals.
 * 
 * Example 1:
 * Input: [(1,3)]
 * Output: [(1,3)]
 * 
 * Example 2:
 * Input:  [(1,3),(2,6),(8,10),(15,18)]
 * Output: [(1,6),(8,10),(15,18)]
 * Challenge
 * O(n log n) time and O(1) extra space.
 * 
 * @Category Intervals
 * @Idea 
 * T=O(n) S=(n)出结果外额外S=O(1)
 * 第1个区间入res,后面依次和当前最后一个区间比较
 *   若和最后区间无重叠(当前最后末<新始) 则加到最后成为新的最后
 *   若和最后区间有重叠(当前最后末>=新始)则合并到最后(新最后末=max(旧最后末,新末))
 * 
 * 坑: vector初始化用{}而不是(): vector<Interval> res {intervals[0]}
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
     * @param intervals: interval list.
     * @return: A new interval list.
     */
    // T=O(n) S=O(n)
    static bool cmp(Interval i1, Interval i2) 
    { 
        return (i1.start < i2.start); 
    } 
    vector<Interval> merge(vector<Interval> &intervals) {
        if (intervals.empty()) return {};
        sort(intervals.begin(), intervals.end(), cmp);  // 先按照start排序
        vector<Interval> res {intervals[0]};            // 第1个区间入结果集 //坑初始化用{}而不是()
        for (int i = 1; i < intervals.size(); ++i) {    // 从第2个区间开始
            if (res.back().end < intervals[i].start) {  // 和当前最后区间比
                res.push_back(intervals[i]);            // 无重叠则加到最后
            }
            else {                                      // 有重叠则并入最后
                res.back().end = max(res.back().end, intervals[i].end);
            }
        }
        return res;
    }
};
