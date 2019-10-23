/*
 * @lc app=lintcode id=213 lang=cpp
 *
 * [213] String Compression
 *
 * https://www.lintcode.com/problem/string-compression/description
 *
 * lintcode
 * Easy (38.00%)
 * Total Accepted:    3228
 * Total Submissions: 8354
 * Testcase Example:  '"aabcccccaaa"\n'
 *
 * Implement a method to perform basic string compression using the counts of
 * repeated characters. For example, the string `aabcccccaaa` would become
 * `a2b1c5a3`.
 * 
 * If the "compressed" string would not become smaller than the original
 * string, your method should return the original string.
 * 
 * You can assume the string has only upper and lower case letters (a-z).
 * Example 1:
 * Input: str = "aabcccccaaa" Output: "a2b1c5a3"
 * Example 2:
 * Input: str = "aabbcc" Output: "aabbcc"
 * 
 * @Category 2 pointers
 * @Idea 双指针 不适用hashmap因为须保持原有字符顺序
 * 
 * 
 */
class Solution {
public:
    /**
     * @param originalString: a string
     * @return: a compressed string
     */
    // 2 pointers毛虫拷贝 + cur记录压缩串结尾
    // T=O(n) S=O(1)
    // 注:因为1也要写所以inplace修改加1会覆盖下一个未读字符,故新生成字符串比较好处理
    string compress(string &chars) {
        int n = chars.size(), cur = 0;
        char newChars[n] = "";                                      // 新生成一个串输出
        for (int i = 0, j = 0; i < n; i = j) {                      // 左指针跟进右指针(毛虫弓背)
            while (j < n && chars[j] == chars[i]) { ++j; }          // 右指针跳过重复(毛虫伸长)
            newChars[cur++] = chars[i];                             // 只拷不重复字符
            for (char c : to_string(j - i)) { newChars[cur++] = c;} // 有重复加重复个数(j-1) 
                                                                    // 坑:数字转字符串to-string(i))
        }
        string res(newChars);
        return cur < n ? res.substr(0, cur) : chars; // 缩写并没比原串短则返回原串
    }
};
