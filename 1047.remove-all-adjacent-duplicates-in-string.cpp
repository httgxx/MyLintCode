/*
 * @lc app=leetcode id=1047 lang=cpp
 *
 * [1047] Remove All Adjacent Duplicates In String
 *
 * https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/description/
 *
 * algorithms
 * Easy (64.71%)
 * Total Accepted:    31.9K
 * Total Submissions: 49.4K
 * Testcase Example:  '"abbaca"'
 *
 * Given a string S of lowercase letters, a duplicate removal consists of
 * choosing two adjacent and equal letters, and removing them.
 * 
 * We repeatedly make duplicate removals on S until we no longer can.
 * 
 * Return the final string after all such duplicate removals have been made.
 * It is guaranteed the answer is unique.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: "abbaca"
 * Output: "ca"
 * Explanation: 
 * For example, in "abbaca" we could remove "bb" since the letters are adjacent
 * and equal, and this is the only possible move.  The result of this move is
 * that the string is "aaca", of which only "aa" is possible, so the final
 * string is "ca".
 * 
 * 
 * 
 * 
 * Note:
 * 
 * 
 * 1 <= S.length <= 20000
 * S consists only of English lowercase letters.
 * 
 * 
 * @Category stack 2Pointer
 * @Idea
 * S1: stack 同top则pop T=O(n) S=O(n)
 * S2: i,j 同向拷贝 若同前则退i-=2,最后只取[0,i) T=O(n) S=O(1)
 * 
 */
class Solution {
public:
    // S2: 2 pointers i,j同向拷贝,若i同前则回退2
    string removeDuplicates(string s) {
        int i = 0;
        for (int j = 0; j < s.length(); ++j, ++i) {
            s[i] = s[j];                                            // i,j同向拷贝
            if (i > 0 && s[i - 1] == s[i]) { i -= 2; }              // 若i同前则回退2
        }
        return s.substr(0, i);                                      // 坑:最后只取[0,i)
    }
};
