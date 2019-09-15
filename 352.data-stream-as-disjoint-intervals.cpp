/*
 * @lc app=leetcode id=352 lang=cpp
 *
 * [352] Data Stream as Disjoint Intervals
 *
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/description/
 *
 * algorithms
 * Hard (44.20%)
 * Total Accepted:    26.5K
 * Total Submissions: 59.8K
 * Testcase Example:  '["SummaryRanges","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals"]\n[[],[1],[],[3],[],[7],[],[2],[],[6],[]]'
 *
 * Given a data stream input of non-negative integers a1, a2, ..., an, ...,
 * summarize the numbers seen so far as a list of disjoint intervals.
 * 
 * For example, suppose the integers from the data stream are 1, 3, 7, 2, 6,
 * ..., then the summary will be:
 * 
 * 
 * [1, 1]
 * [1, 1], [3, 3]
 * [1, 1], [3, 3], [7, 7]
 * [1, 3], [7, 7]
 * [1, 3], [6, 7]
 * 
 * Follow up:
 * What if there are lots of merges and the number of disjoint intervals are
 * small compared to the data stream's size?
 * 
 */
class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {}
    
    void addNum(int val) {
        vector<int> newInterval{val, val};
        int i = 0, overlap = 0, n = intervals.size();
        for (; i < n; ++i) {
            if (newInterval[1] + 1 < intervals[i][0]) { break; }        // 新末<当前始, [新]<[当前],不重叠,不用再继续比较  
            if (newInterval[0] <= intervals[i][1] + 1) {                // 新始<=当前末,当前始<=新末,有重叠,合并[当前]到[新]
                newInterval[0] = min(newInterval[0], intervals[i][0]);
                newInterval[1] = max(newInterval[1], intervals[i][1]);
                ++overlap;
            }
        }
        if (overlap > 0) {
            intervals.erase(intervals.begin() + i - overlap, intervals.begin() + i);    // 删除合并到[新]的区间
        }
        intervals.insert(intervals.begin() + i - overlap, newInterval);                 // 插入合并后的[新]
    }
    
    vector<vector<int>> getIntervals() {
        return intervals;
    }
private:
    vector<vector<int>> intervals;
};
