/*
 * @lc app=lintcode id=1592 lang=cpp
 *
 * [1592] Find and Replace Pattern
 *
 * https://www.lintcode.com/problem/find-and-replace-pattern/description
 *
 * lintcode
 * Medium (84.00%)
 * Total Accepted:    489
 * Total Submissions: 579
 * Testcase Example:  '["abc","deq","mee","aqq","dkd","ccc"]\n"abb"'
 *
 * You have a list of words and a pattern, and you want to know which words in
 * words matches the pattern.
 * 
 * A word matches the pattern if there exists a permutation of letters p so
 * that after replacing every letter x in the pattern with p(x), we get the
 * desired word.
 * 
 * (Recall that a permutation of letters is a bijection from letters to
 * letters: every letter maps to another letter, and no two letters map to the
 * same letter.)
 * 
 * Return a list of the words in words that match the given pattern. 
 * You may return the answer in any order.
 * 
 * Example 1:
 * Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
 * Output: ["aqq","mee"]
 * Explanation: 
 * "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
 * "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation,
 * since a and b map to the same letter.
 * 
 * Example 2:
 * Input: words = ["a","b","c"], pattern = "a"
 * Output: ["a","b","c"]
 * Explanation: 
 * All strings match.
 * 
 * @Category string pattern match
 * @Idea pattern match必须word[i]到pattern[i]的对应关系唯一
 * 例如:像mn=>aa,m和n都对应a说明mn不match pattern
 * 又如: pattern 体会出来了mm
 * 
 */
class Solution {
public:
    /**
     * @param words: word list
     * @param pattern: pattern string
     * @return: list of matching words
     */
    // 找字符串的字符出现规律, word和pattern的字符出现规律相同则算word匹配pattern
    // T=O(mn) S=O(mn)  m=word的个数, n=word/pattern的长度
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;
        for (string word : words) {                     // T=O(m*...) m=word个数
            if (helper(word) == helper(pattern)) {      // word和pattern的字符出现规律相同
                res.push_back(word);                    // 则word匹配pattern，加入结果集
            }
        }
        return res;
    }
    string helper(string word) {                    // 找word的字符出现规律 // T=O(n) S=O(n) n=word长度
        unordered_map<char, int> m;
        for (char c : word) {                       // 对每个字符,统计该字符首次出现之前所有出现过的字符种类数                               
            if (!m.count(c)) { m[c] = m.size(); }   // e.g. xyy=>011
        }
        for (int i = 0; i < word.size(); ++i) {     // 将字符种类数当作偏移量加+'a'编码成字符形成pattern
            word[i] = 'a' + m[word[i]];             // e.g. xyy=>011=>abb
        }
        return word;
    }
};
