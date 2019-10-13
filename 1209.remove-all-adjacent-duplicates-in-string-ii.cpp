/*
 * @lc app=leetcode id=1209 lang=cpp
 *
 * [1209] Remove All Adjacent Duplicates in String II
 *
 * https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/description/
 *
 * algorithms
 * Medium (58.02%)
 * Total Accepted:    7.8K
 * Total Submissions: 13.4K
 * Testcase Example:  '"abcd"\n2'
 *
 * Given a string s, a k duplicate removal consists of choosing k adjacent and
 * equal letters from s and removing them causing the left and the right side
 * of the deleted substring to concatenate together.
 * 
 * We repeatedly make k duplicate removals on s until we no longer can.
 * 
 * Return the final string after all such duplicate removals have been made.
 * 
 * It is guaranteed that the answer is unique.
 * 
 * Example 1:
 * Input: s = "abcd", k = 2
 * Output: "abcd"
 * Explanation: There's nothing to delete.
 * 
 * Example 2:
 * Input: s = "deeedbbcccbdaa", k = 3
 * Output: "aa"
 * Explanation: 
 * First delete "eee" and "ccc", get "ddbbbdaa"
 * Then delete "bbb", get "dddaa"
 * Finally delete "ddd", get "aa"
 * 
 * Example 3: 
 * Input: s = "pbbcggttciiippooaais", k = 2
 * Output: "ps"
 * 
 * Constraints:
 * 1 <= s.length <= 10^5
 * 2 <= k <= 10^4
 * s only contains lower case English letters.
 */
class Solution {
public:
    // S1: vector as stack <char, count> : stack 同top 且count=k 则pop
    // T=O(n) S=O(n)
    string removeDuplicates(string S, int k) {
        vector<pair<char, int>> stack = {{'#', 0}};                     // vector做stack存<char,count>,加dummy'#'处理空串
        for (char& c : S) {
            if (stack.back().first != c) { stack.push_back({c, 1}); }   // 不同前则入栈
            else if (++stack.back().second == k) { stack.pop_back(); }  // 同前且k次则出栈
        }
        string res;
        for (auto &p : stack) {                                         // 重组去重后的串
            res += string(p.second, p.first);
        }
        return res;
    }
    // S2: 2 pointers + counter: i,j同向拷贝,若i同前且count=k则回退2
    // T=O(n) S=O(1)
    string removeDuplicates2(string s, int k) {
        int i = 0, n = s.length();
        vector<int> count(n);
        for (int j = 0; j < n; ++j, ++i) {
            s[i] = s[j];                                            // i,j同向拷贝
            count[i] = (i > 0 && s[i - 1] == s[j]) ? count[i - 1] + 1 : 1;
            if (count[i] == k) { i -= k; }                          // 若i同前k且出现次则i回退k
        }
        return s.substr(0, i);                                      // 坑:最后只取[0,i)
    }
};
