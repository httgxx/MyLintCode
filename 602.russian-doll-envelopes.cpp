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
 * @Category DP,LIS
 * @Ideas
 * DP //T=O(nlogn) S=O(n)
 * 按照长度从小到大排O(nlog),注意相同长度则按宽度从大到小排(因为同长时小宽仍放不进大宽)
 * 找宽度的LIS的长度
 * dp[i]
 * 
 */
class Solution {
public:
    static bool cmp(const pair<int, int> &x, const pair<int, int> &y) {
        // 按宽度从小到大排,同宽时按高度从大到小排,因为同宽时矮的仍然放不进高的
        return x.first != y.first ? x.first < y.first : x.second > y.second;
    }
    /*
     * @param envelopes: a number of envelopes with widths and heights
     * @return: the maximum number of envelopes
     */
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        int n = envelopes.size();
        if (n < 2) { return n; }

        sort(envelopes.begin(), envelopes.end(), cmp);  // 按宽度升序排的信封
        vector<int> dp;  // 坑:不能初始化时设dp[]的大小,因为长度会不断增大
        for (int i = 0; i < n; ++i) {  // 找基于高度的LIS
            int left = 0, right = dp.size(), h = envelopes[i].second;
            while (left < right) {  // 二分找到第1个高度>=height的信封
                int mid = left + (right - left) / 2;
                if (dp[mid] < h) { left = mid + 1; }
                else { right = mid; }  // dp[mid]>=h但还继续往左找最左边>=h的数
            }
            if (right >= dp.size()) {
                dp.push_back(h);  // 没找到即height是目前最高的,增长LIS
            }
            else {
                dp[right] = h;  // 找到了这样的高度,用height替换降低它
            }
        }
        return dp.size();
    }
};
