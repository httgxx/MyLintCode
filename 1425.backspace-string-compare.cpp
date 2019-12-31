/*
 * @lc app=lintcode id=1425 lang=cpp
 *
 * [1425] Backspace String Compare
 *
 * https://www.lintcode.com/problem/backspace-string-compare/description
 *
 * lintcode
 * Easy (49.00%)
 * Total Accepted:    208
 * Total Submissions: 423
 * Testcase Example:  '"ab#c"\n"ad#c"'
 *
 * Given two strings `S` and `T`, return if they are equal when both are typed
 * into empty text editors. `#` means a backspace character.
 * 
 * Example 1:
 * Input: S = "ab#c", T = "ad#c"
 * Output: true
 * Explanation: Both S and T become "ac".
 * 
 * Example 2:
 * Input: S = "ab##", T = "c#d#"
 * Output: true
 * Explanation: Both S and T become "".
 * 
 * Example 3:
 * Input: S = "a##c", T = "#a#c"
 * Output: true
 * Explanation: Both S and T become "c".
 * 
 * Example 4:
 * Input: S = "a#c", T = "b"
 * Output: false
 * Explanation: S becomes "c" while T becomes "b".
 * 
 * Challenge
 * Can you solve it in O(N) time and O(1) space?
 * 
 * @Category string compare
 * @Idea
 * S1: 不用额外空间,指针反向扫 T=O(n) S=O(1)
 * 坑: 必须记录连续#的个数来跳过多个不用比较的字符 
 * 坑: 必须考虑一个串比另一个串先结束的情况
 *
 * S2: 比较转换后的结果字符串 T=O(n) S=(n)
 * 巧: 巧用?:和用void() 
 * 
 * S3:比较转换后的结果字符串 T=O(n) S=(n)
 * 坑:不用stack或vector,因为string可当vector<char>用可push_back,pop_back
 * 坑:str1==str2可比较值而不是比较指针
 * 坑:须初始化string res=""
 */
class Solution {
public:
    // S1: 不用额外空间,指针反向扫 T=O(n) S=O(1)
    // 坑: 必须记录连续#的个数来跳过多个不用比较的字符 
    // 坑: 必须考虑一个串比另一个串先结束的情况
    bool backspaceCompare(string &S, string &T) {
        int sid = S.size() - 1, tid = T.size() - 1, sbps = 0, tbps = 0;                             // 记录连续#的个数
        while (sid >= 0 || tid >= 0) {
            while (sid >= 0 && (S[sid] == '#' || sbps > 0)) { S[sid--] == '#' ? ++sbps : --sbps; }  // 连续#连续倒退跳过不用比较
            while (tid >= 0 && (T[tid] == '#' || tbps > 0)) { T[tid--] == '#' ? ++tbps : --tbps; }
            if (sid < 0 || tid < 0) { return sid == tid; }                                          // 坑: sid或tid可能<0得先处理再比较S[sid]和T[tid]
            if (S[sid--] != T[tid--]) { return false; }                                             // S[sid]和T[tid]即当前非#字符须匹配
        }
        return sid == tid;                                                                          
    }
    
    // S2: 比较转换后的结果字符串 T=O(n) S=(n)
    // 巧: 巧用?:和用void()
    bool backspaceCompare2(string &S, string &T) {
        string s = "", t = "";
        for (char c : S) { c == '#' ? (s.empty() ? void() : s.pop_back()) : s.push_back(c); }
        for (char c : T) { c == '#' ? (t.empty() ? void() : t.pop_back()) : t.push_back(c); }
        return s == t;
    }
    
    // S3:比较转换后的结果字符串 T=O(n) S=(n)
    // 坑:不用stack或vector,因为string可当vector<char>用可push_back,pop_back
    // 坑:str1==str2可比较值而不是比较指针
    // 坑:须初始化string res=""
    bool backspaceCompare3(string &S, string &T) {
        return helper(S) == helper(T);
    }
    string helper(string & str) {
        string res = "";
        for(char c : str) {
            if (c == '#' && !res.empty()) { res.pop_back(); }
            else { res.push_back(c); }
        }
        return res;
    }
};
