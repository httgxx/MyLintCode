/*
 * @lc app=lintcode id=647 lang=cpp
 *
 * [647] Find All Anagrams in a String
 *
 * https://www.lintcode.com/problem/find-all-anagrams-in-a-string/description
 *
 * lintcode
 * Easy (31.00%)
 * Total Accepted:    5890
 * Total Submissions: 18783
 * Testcase Example:  '"abab"\n"ab"\n'
 *
 * Given a string `s` and a **non-empty** string `p`, find all the start
 * indices of `p`'s anagrams in `s`.
 * 
 * Strings consists of lowercase English letters only and the length of both
 * strings **s** and **p** will not be larger than 40,000.
 * 
 * The order of output does not matter.
 */
class Solution {
public:
    /**
     * @param s: a string
     * @param p: a string
     * @return: a list of index
     */
    // 滑动窗口 + int[256]字符计数 + cnt(p中要匹配的字符总数)
    // T=O(n) S=(n)
    vector<int> findAnagrams(string &s, string &p) {
        if (s.empty()) return {};                               // 特例空串
        vector<int> res, m(256, 0);                             // 结果集,字符计数器
        for (char c : p) { ++m[c]; }                            // 统计p中各字符出现次数
        int left = 0, right = 0, cnt = p.size(), n = s.size();  // cnt=p中需匹配的字符总数(重复字符重复计数)
        while (right < n) {                     
            if (m[s[right++]]-- >= 1) { --cnt; }                // 若右边界出现过(次数>=1)则p中需匹配字符总数-1,该字符次数-1,右边界进1
            if (cnt == 0) { res.push_back(left); }              // 若p中字符全匹配,则左边界(start)入结果集
            if (right - left == p.size() &&                     // 若右-左=窗口长,左边界须进1,若左边界出现次数>=0则表明左边界在p中(否则应该会>=1)
                m[s[left++]]++ >= 0) { ++cnt; }                 // 左进,即左边界+1,则p中字符少匹配1个字符,即需要多匹配一个cnt+1
        }
        return res;
    }
};
