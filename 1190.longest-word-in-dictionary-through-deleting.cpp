/*
 * @lc app=lintcode id=1190 lang=cpp
 *
 * [1190] Longest Word in Dictionary through Deleting
 *
 * https://www.lintcode.com/problem/longest-word-in-dictionary-through-deleting/description
 *
 * lintcode
 * Medium (45.00%)
 * Total Accepted:    535
 * Total Submissions: 1162
 * Testcase Example:  '""\n[]'
 *
 * Given a string and a string dictionary, find the longest string in the
 * dictionary that can be formed by deleting some characters of the given
 * string. If there are more than one possible results, return the longest word
 * with the smallest lexicographical order. If there is no possible result,
 * return the empty string.
 * 
 * Example 1:
 * Input: s = "abpcplea", d = ["ale","apple","monkey","plea"
 * Output: "apple"
 * 
 * Example 2:
 * Input: s = "abpcplea", d = ["a","b","c"]
 * Output: "a"
 * 
 * @Category String
 * @Idea String 
 * S1: 先排序字典,再每个字典词去串中找匹配,第一个有匹配的词即是
 * 先排序字典:按长度由大到小,再按字母顺序由小到大(输出字符顺序不能变所以不能排).
 * 对字典中每个词,从头扫描给定串,若词中每个字符都能在串中找到匹配,说明串包含该词.
 * 因为字典中的词已经排序,所以第一个匹配的词就是能匹配的最长词.
 * T=O(m*logm*(n1*logn1) + m*n2)=O(m*n1*log(m+n1) + m*n2) S=O(1) 
 * m=字典中词的数量,n1=字典中词的平均长度,n2=给定串长度
 * [注]适合字典中词不多(m小)很长(n1大=>logn1好)的情况
 *
 * S2:
 *   
 * 
 */
class Solution {
public:
    /**
     * @param s: a string
     * @param d: List[str]
     * @return: return a string
     * S1: 先排序字典,再每个字典词去串中找匹配,第一个有匹配的词即是
     * 先排序字典:按长度由大到小,再按字母顺序由小到大(输出字符顺序不能变所以不能排).
     * 对字典中每个词,从头扫描给定串,若词中每个字符都能在串中找到匹配,说明串包含该词.
     * 因为字典中的词已经排序,所以第一个匹配的词就是能匹配的最长词.
     * T=O(m*logm*(n1*logn1) + m*n2)=O(m*n1*log(m+n1) + m*n2) S=O(1) 
     * m=字典中词的数量,n1=字典中词的平均长度,n2=给定串长度
     * [注]适合字典中词不多(m小)很长(n1大=>logn1好)的情况
     */
     string findLongestWord1(string &s, vector<string> &d) {
        sort(d.begin(), d.end(), [](string a, string b) {   // 字典按从长到短,同长则按字目先后排序
            if (a.size() == b.size()) return a < b;
            return a.size() > b.size();
        });
        for (string str : d) {                              // 对字典中每个词
            int i = 0;
            for (char c : s) {                              // 从头扫描给定串
                if (i < str.size() && c == str[i]) { ++i; } // 若词的字符在给定串中找到匹配,则继续扫串 
            }
            if (i == str.size()) { return str; }            // 若词的所有字符都在给定串中,返回词
        }
        return "";                                          // 若字典中的每个词都不在给定串中,返回空
    }

    /* S2: 不用排序字典,所有字典词都去串中找匹配,每次发现匹配到的词就更新结果
     * 对字典中每个词,从头扫描给定串,若词中每个字符都能在串中找到匹配,说明串包含该词.
     * 每找到匹配的词就看是否更长和字典顺序更前,是则更新结果.
     * T=O(m*n1*n2) S=O(1)
     * [注]适合字典中词多(m大)且短(n1小)的情况
     */
    string findLongestWord(string s, vector<string>& d) {
        string res = "";
        for (string str : d) {                              // 对字典中每个词
            int i = 0;                                      // 从头扫描给定串
            for (char c : s) {                              // 若词的字符在给定串中找到匹配,则继续扫串
                if (i < str.size() && c == str[i]) { ++i; }
            }
            if (i == str.size() &&                          // 若词的所有字符都在给定串中
                (str.size() > res.size() ||                 // 且找到比当前结果更长
                (str.size() == res.size() && str < res))) { //   或跟当前结果等长但字典顺序更前
                    res = str;                              // 则更新结果
            }
        }
        return res;                                         // 返回结果(可能为""")
    }
};
