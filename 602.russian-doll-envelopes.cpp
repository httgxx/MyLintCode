/*
 * @lc app=lintcode id=602 lang=cpp
 *
 * [602] Russian Doll Envelopes
 *
 * https://www.lintcode.com/problem/russian-doll-envelopes/description
 *
 * lintcode
 * Hard (21.00%)
 * Total Accepted:    3061
 * Total Submissions: 14477
 * Testcase Example:  '[[5,4],[6,4],[6,7],[2,3]]\n'
 *
 * Give a number of envelopes with widths and heights given as a pair of
 * integers `(w, h)`. One envelope can fit into another if and only if both the
 * width and height of one envelope is greater than the width and height of the
 * other envelope.
 * Find the maximum number of nested layers of envelopes.
 * 
 * @Category DP,贪心?
 * @Ideas
 * dp[i]表示第i个信封能套的最高的信封高度
 * 
 */
class Solution {
public:
    /*
     * @param envelopes: a number of envelopes with widths and heights
     * @return: the maximum number of envelopes
     */
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        vector<int> dp;
        sort(envelopes.begin(), envelopes.end(), 
            [](const pair<int, int> &a, const pair<int, int> &b) {
                // 同样宽度则按高度从大到小排 这样才能保证同宽的就算高度高也不能套
                if (a.first == b.first) return a.second > b.second; 
                return a.first < b.first;  // 先按宽度从小到大排
        });
        for (int i = 0; i < envelopes.size(); ++i) {
            int left = 0, right = dp.size(), height = envelopes[i].second;
            while (left < right) {  // 二分找到第一个高度>=信封[i]的信封
                int mid = left + (right - left) / 2;
                if (dp[mid] < height) left = mid + 1;
                else right = mid;
            }
            if (right >= dp.size()) dp.push_back(height);  // 找不到则高度入栈
            else dp[right] = height;  // 找到了则用更新能套的信封的最高高度
        }
        return dp.size();
    }
};
