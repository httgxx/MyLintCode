/*
 * @lc app=leetcode id=916 lang=cpp
 *
 * [916] Word Subsets
 *
 * https://leetcode.com/problems/word-subsets/description/
 *
 * algorithms
 * Medium (45.92%)
 * Total Accepted:    13.7K
 * Total Submissions: 29.8K
 * Testcase Example:  '["amazon","apple","facebook","google","leetcode"]\n["e","o"]'
 *
 * We are given two arrays A and B of words.  Each word is a string of lowercase letters.
 * 
 * Now, say that word b is a subset of word a if every letter in b occurs in a, including multiplicity.  
 * For example, "wrr" is a subset of "warrior", but is not a subset of "world".
 * 
 * Now say a word a from A is universal if for every b in B, b is a subset of a. 
 * 
 * Return a list of all universal words in A.  You can return the words in any order.
 * 
 * Example 1: 
 * Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
 * Output: ["facebook","google","leetcode"]
 * 
 * Example 2:
 * Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["l","e"]
 * Output: ["apple","google","leetcode"]
 * 
 * Example 3:
 * Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","oo"]
 * Output: ["facebook","google"]
 *
 * Example 4: 
 * Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["lo","eo"]
 * Output: ["google","leetcode"]
 * 
 * Example 5:
 * Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["ec","oc","ceo"]
 * Output: ["facebook","leetcode"]
 * 
 * Note:
 * 1 <= A.length, B.length <= 10000
 * 1 <= A[i].length, B[i].length <= 10
 * A[i] and B[i] consist only of lowercase letters.
 * All words in A[i] are unique: there isn't i != j with A[i] == A[j].
 * 
 * @Category string
 * @Idea string char-count
 * 串b是串a的subset的条件: 串b中所有字符在串a中都出现过
 * 串a是universal的条件是: 集合B中所有词都是a的subset
 * 求集合A中所有universal: 找集合A中的所有串a满足:集合B中所有串b都是a的subset,即a包含集合B中出现过的所有字符
 * 1. 扫描B中所有串b,统计每个出现的字符在单个串中出现的最大次数 charCntMax[char]=count
 * 2. 扫描A中所有串a,查看B中出现过的所有字符都在a中出现,且在a中出现的次数>=在B中单个串中出现的最大次数 
 */
class Solution {
public:
    /* 串b是串a的subset的条件: 串b中所有字符在串a中都出现过
    * 串a是universal的条件是: 集合B中所有词都是a的subset
    * 求集合A中所有universal: 找集合A中的所有串a满足:集合B中所有串b都是a的subset,即a包含集合B中出现过的所有字符
    * 1. 扫描B中所有串b,统计每个出现的字符在单个串中出现的最大次数 charCntMax[char]=count
    * 2. 扫描A中所有串a,查看B中出现过的所有字符都在a中出现,且在a中出现的次数>=在B中单个串中出现的最大次数 
    * T=O(m1+n1 + m2*n2) S=O(1)
    */
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        vector<string> res;
        vector<int> charCntMax(26, 0);
        for (string &b : B) {                               // 扫描集合B中所有串b
            vector<int> t = getCharCnt(b);                  // 统计串b中各字符的出现次数 T=O(m2*n2)
            for (int i = 0; i < 26; ++i) {                  // 更新B中各字符的单串出现最大次数 T=O(1)
                charCntMax[i] = max(charCntMax[i], t[i]);
            }
        }
        for (string &a : A) {                               // 扫描集合A中所有串a T=O(m1*n1)
            vector<int> t = getCharCnt(a);                  // 统计串a中各字符的出现次数 T=O(m1*n1)
            int i = 0;
            for (; i < 26; ++i) {                           // T=O(1)
                if (t[i] < charCntMax[i]) { break; }        // 若某字符B中单串出现次数>在串a中出现次数,a不是universal
            }
            if (i == 26) res.push_back(a);                  // 若B中每个字符的单串出现次数<=a中出现次数,则a是universal
        }
        return res;
    }
    vector<int> getCharCnt(string& word) {                  // 统计word中字符频率
        vector<int> res(26);
        for (char c : word) { ++res[c - 'a']; }
        return res;
    }
};
