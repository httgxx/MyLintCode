/*
 * @lc app=lintcode id=120 lang=cpp
 *
 * [120] Word Ladder
 *
 * https://www.lintcode.com/problem/word-ladder/description
 *
 * lintcode
 * Hard (27.00%)
 * Total Accepted:    27603
 * Total Submissions: 100443
 * Testcase Example:  '"a"\n"c"\n["a","b","c"]'
 *
 * Given two words (*start* and *end*), and a dictionary, find the shortest
 * transformation sequence from *start* to *end*, output the length of the
 * sequence.
 * Transformation rule such that:
 * 
 * 1. Only one letter can be changed at a time
 * 2. Each intermediate word must exist in the dictionary. (Start and end words
 * do not need to appear in the dictionary )
 * 
 * Example 1:
 * Input：start = "a"，end = "c"，dict =["a","b","c"]
 * Output：2
 * Explanation："a"->"c"
 * 
 * Example 2:
 * Input：start ="hit"，end = "cog"，dict =["hot","dot","dog","lot","log"]
 * Output：5
 * Explanation："hit"->"hot"->"dot"->"dog"->"cog"
 * 
 * @Category 迷宫 BFS DFS
 * @Idea BFS queue+字典set + set.erase(访问过的词)
 * T=O(26*L)=O(L) S=O(nL)) L为单词长度, n为字典里单词数
 * 
 * 坑: 题说中间转换词须在dict中没说end一定也在,故end不在字典中则需加入!!!
 * 坑: set.erase(邻居) 邻居将不用再被访问了,剪枝!!!
 */
class Solution {
public:
    /*
     * @param start: a string
     * @param end: a string
     * @param dict: a set of string
     * @return: An integer
     */
    // 迷宫 BFS T=O(26*L)=O(L) S=O(nL)) L为单词长度, n为字典里单词数
    int ladderLength(string &start, string &end, unordered_set<string> &dict) {
        if (!dict.count(end)) { dict.insert(end); }          // 坑: 题说中间转换词须在dict中没说end一定也在,故end不在字典中则需加入!!!
        queue<string> q{{start}};
        int res = 0;
        while (!q.empty()) {
            for (int k = q.size(); k > 0; --k) {
                string word = q.front(); q.pop();
                if (word == end) { return res + 1; }        // 找到end返回长度 //坑: 须+1
                for (int i = 0; i < word.size(); ++i) {     // O(L*...) 为单词长度
                    string newWord = word;
                    for (char ch = 'a'; ch <= 'z'; ++ch) {  // 访问26个邻居 O(26*...) 
                        newWord[i] = ch;
                        if (dict.count(newWord) && newWord != word) { 
                            q.push(newWord);                // 邻居在字典里且未被访问过,入队列下层访问
                            dict.erase(newWord);            // 坑: 邻居不用再被访问了,剪枝!!!
                        }   
                    }
                }
            }
            ++res;
        }
        return 0;                                           // 坑: 此处才返回说明没法由start变为end
    }
};
