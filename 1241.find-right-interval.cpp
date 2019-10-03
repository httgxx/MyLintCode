/*
 * @lc app=lintcode id=1241 lang=cpp
 *
 * [1241] Find Right Interval
 *
 * https://www.lintcode.com/problem/find-right-interval/description
 *
 * lintcode
 * Medium (39.00%)
 * Total Accepted:    191
 * Total Submissions: 424
 * Testcase Example:  '[(1,2)]'
 *
 * Given a set of intervals, for each of the interval i, check if there exists
 * an interval j whose start point is bigger than or equal to the end point of
 * the interval i, which can be called that j is on the "right" of i.
 * 
 * For any interval i, you need to store the minimum interval j's index, which
 * means that the interval j has the minimum start point to build the "right"
 * relationship for interval i. If the interval j doesn't exist, store -1 for
 * the interval i. Finally, you need output the stored value of each interval
 * as an array.
 * 
 * Example 1:
 * Input: [ [1,2] ]
 * Output: [-1]
 * Explanation: There is only one interval in the collection, so it outputs -1.
 * 
 * Example 2:
 * Input: [ [3,4], [2,3], [1,2] ]
 * Output: [-1, 0, 1]
 * 
 * Explanation: There is no satisfied "right" interval for [3,4].
 * For [2,3], the interval [3,4] has minimum-"right" start point;
 * For [1,2], the interval [2,3] has minimum-"right" start point.
 * 
 * Example 3:
 * Input: [ [1,4], [2,3], [3,4] ]
 * Output: [-1, 2, -1]
 * Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
 * For [2,3], the interval [3,4] has minimum-"right" start point.
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
     * @param intervals: a list of intervals
     * @return: return a list of integers
     */
    // Intervals: T=O(n^2) S=O(n)
    vector<int> findRightInterval1(vector<Interval> &intervals) {
        vector<int> res, starts;
        unordered_map<int, int> m;
        for (int i = 0; i < intervals.size(); ++i) {
            m[intervals[i].start] = i;                      // m[start]=i
            starts.push_back(intervals[i].start);
        }
        sort(starts.rbegin(), starts.rend());               // 所有区间按start倒排序
        for (auto interval : intervals) {                   
            int i = 0;
            for (; i < starts.size(); ++i) {
                if (starts[i] < interval.end) { break; }    // 遍历区间找start[i]]第1个<当前end的start    
            }
            res.push_back((i > 0) ? m[starts[i - 1]] : -1); // start[i-1]就是第1个>=当前end的start,入结果集
        }
        return res;
    }
    // T=O(nlogn) S=O(n)
    vector<int> findRightInterval(vector<Interval>& intervals) {
        vector<int> res;
        map<int, int> m;
        for (int i = 0; i < intervals.size(); ++i) {
            m[intervals[i].start] = i;              // m[start]=i
        }
        for (auto interval : intervals) {
            auto it = m.lower_bound(interval.end);  // 遍历区间找m中第1个>=当前end的start 
            if (it == m.end()) res.push_back(-1);   // 找不到,当前区间没有右区间,返回-1
            else res.push_back(it->second);         // 找到,区间index加入结果集
        }
        return res;
    }
};
