/*
 * @lc app=lintcode id=696 lang=cpp
 *
 * [696] Course Schedule III
 *
 * https://www.lintcode.com/problem/course-schedule-iii/description
 *
 * lintcode
 * Hard (29.00%)
 * Total Accepted:    426
 * Total Submissions: 1432
 * Testcase Example:  '[]'
 *
 * There are ·n· different online courses numbered from `1` to `n`. Each course
 * has some `duration(course length) t` and closed on `dth` day. A course
 * should be taken continuously for t days and must be finished before or on
 * the `dth` day. You will start at the `1st` day.
 * 
 * Given `n` online courses represented by pairs `(t,d)`, your task is to find
 * the maximal number of courses that can be taken.
 * 
 * Example 1
 * Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
 * Output: 3
 * Explanation:
 * There're totally 4 courses, but you can take 3 courses at most:
 * First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the `101st` day.
 * Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
 * Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
 * The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
 * 
 * Example 2
 * Input: [[100,50]]
 * Output: 0
 * 
 * @Category 优先队列(最大堆)
 * @Idea T=O(nlogn) S=O(n)
 * [[课程持续时间,课程结束时间]]
 * 先按结束时间排序,然后依次将每门课入最大堆,且更新curTime+=该课程持续时间, 若curTime>该课程结束时间,
 * 为了腾出时间上最多的课,取出最大堆顶(持续时间最长的一门课),且更新curTime-=该课程持续时间,
 * 最后最大堆大小即为能完成的课程数目
 */
class Solution {
public:
    /**
     * @param courses: duration and close day of each course
     * @return: the maximal number of courses that can be taken
     */
    // S1: 优先队列(最大堆) T=O(nlogn) S=O(n)
    int scheduleCourse(vector<vector<int>> &courses) {
        sort(courses.begin(), courses.end(),    // 按结束时间先后排序 // 坑:比较器
            [](vector<int> & a, vector<int> & b) { return a[1] < b[1]; });
            
        int curTime = 0;
        priority_queue<int> q;
        for (auto course : courses) {
            q.push(course[0]);                  // 课程耗时入堆,来找最耗时的课
            curTime += course[0];               // 啥时能上完
            if (curTime > course[1]) {          // 没上完课就结束了
                curTime -= q.top(); q.pop();    // 取消当前最耗时的课,腾时间上更多别的课
            }
        }
        return q.size();                        // 坑:不出堆的都能上完
    }
};
