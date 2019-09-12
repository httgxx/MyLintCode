/*
 * @lc app=lintcode id=362 lang=cpp
 *
 * [362] Sliding Window Maximum
 *
 * https://www.lintcode.com/problem/sliding-window-maximum/description
 *
 * lintcode
 * Hard (31.00%)
 * Total Accepted:    12304
 * Total Submissions: 39271
 * Testcase Example:  '[1,2,7,7,2]\n3\n'
 *
 * Given an array of n integer with duplicate number, and a moving window(size
 * k), move the window at each iteration from the start of the array, find the
 * maximum number inside the window at each moving.
 */
class Solution {
public:
    /**
     * @param nums: A list of integers.
     * @param k: An integer
     * @return: The maximum number inside the window at each moving.
     */
     // Sliding window deque
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        vector<int> res;
        deque<int> q;                                               // 双端队列:可以从头和尾加减
        for (int i = 0; i < nums.size(); ++i) {
            if (!q.empty() && q.front() == i - k) { q.pop_front(); }// 窗满,窗口左边界内缩
            while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back(); // 窗口右边界内缩,吐出<=新元素的
            q.push_back(i);                                         // 新元素进窗
            if (i >= k - 1) res.push_back(nums[q.front()]);         // 窗满,窗口(队头)即为窗口max存到res
        }
        return res;
    }
};
