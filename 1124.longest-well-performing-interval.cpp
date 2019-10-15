/*
 * @lc app=leetcode id=1124 lang=cpp
 *
 * [1124] Longest Well-Performing Interval
 *
 * https://leetcode.com/problems/longest-well-performing-interval/description/
 *
 * algorithms
 * Medium (31.68%)
 * Total Accepted:    6.6K
 * Total Submissions: 20.9K
 * Testcase Example:  '[9,9,6,0,6,6,9]'
 *
 * We are given hours, a list of the number of hours worked per day for a given employee.
 * A day is considered to be a tiring day if and only if the number of hours worked is 
 * (strictly) greater than 8.
 * A well-performing interval is an interval of days for which the number of
 * tiring days is strictly larger than the number of non-tiring days.
 * 
 * Return the length of the longest well-performing interval.
 * 
 * Example 1:
 * Input: hours = [9,9,6,0,6,6,9]
 * Output: 3
 * Explanation: The longest well-performing interval is [9,9,6].
 * 
 * Constraints:
 * 1 <= hours.length <= 10000
 * 0 <= hours[i] <= 16
 * 
 * @Category longest subarray with target sum=1
 * @Idea 转换成找和为1的最长连续子串
 * 9>8=>1, 6<8=>-1, 96串=>1,-1串
 * 求sum=1的最长连续子串
 */
class Solution {
public:
    // 求sum=1的最长连续子串 S=O(n)  T=O(n)
    int longestWPI(vector<int>& hours) {
        unordered_map<int, int> idx;    
        int s = 0, res = 0;
        for (int i = 0; i < hours.size(); ++i) {
            s += hours[i] > 8 ? 1 : -1;             // 9,6串转换成1,-1串,计算前缀和
            if (s > 0) { res = i + 1; }             // [0,i]是合法子串
            else {
                if (!idx.count(s)) { idx[s] = i; }  // 若preSum没出现过,则记录preSum=s首次出现的prefix结束位置i
                if (idx.count(s - 1)) {             // 若preSum出现过
                    res = max(res, i - idx[s - 1]); //   则找到preSum=s-1首次出现的prefix'结束位置x, 则[0,i-x]的sum=s-(s-1)=1
                }
            }
        }
        return res;
    }
};
