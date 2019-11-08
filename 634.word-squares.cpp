/*
 * @lc app=lintcode id=634 lang=cpp
 *
 * [634] Word Squares
 *
 * https://www.lintcode.com/problem/word-squares/description
 *
 * lintcode
 * Hard (41.00%)
 * Total Accepted:    5200
 * Total Submissions: 12333
 * Testcase Example:  '["area","lead","wall","lady","ball"]\n'
 *
 * Given a set of words **without duplicates**, find all [`word
 * squares`](https://en.wikipedia.org/wiki/Word_square "Word square") you can
 * build from them.
 * 
 * A sequence of words forms a valid word square if the kth row and column read
 * the exact same string, where 0 ≤ k < max(numRows, numColumns).
 * 
 * For example, the word sequence `["ball","area","lead","lady"]` forms a word
 * square because each word reads the same both horizontally and vertically.
 * ```
 * b a l l
 * a r e a
 * l e a d
 * l a d y
 * ```
 * Note:
 * There are at least 1 and at most 1000 words.
 * All words will have the exact same length.
 * Word length is at least 1 and at most 5.
 * Each word contains only lowercase English alphabet a-z.
 * 
 * Example 1:
 * Input: ["area","lead","wall","lady","ball"]
 * Output:[["wall","area","lead","lady"],["ball","area","lead","lady"]]
 * Explanation: The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
 * 
 * Example 2:
 * Input: ["abat","baba","atan","atal"]
 * Output:[["baba","abat","baba","atan"],["baba","abat","baba","atal"]]
 * 
 * @Category Trie+递归DFS
 * @Idea 
 * 枚举每个单词为第1行
 *   再枚举含有第2列前1行的前缀的所有单词填入第2行
 *     递归给第3行找单词填(即枚举含有第3列前2行的前缀的所有单词填入第3行)
 *       ...
 *       直到第word.length行被填完,即找到符合条件的word square加入结果集
 * 返回所有满足条件的word sqaure
 */
class Solution {
public:
    /*
     * @param words: a set of words without duplicates
     * @return: all word squares
     */
    // Trie + 递归
    // T=O(mn) S=O(mn) m=单词个数 n=单词长度
    struct TrieNode {                                               // TrieNode
        vector<int> indexs;                                         // 每个结点保存含有当前结点对应前缀的所有单词的index
        vector<TrieNode*> children;
        TrieNode(): children(26, nullptr) {}
    };
    TrieNode* buildTrie(vector<string>& words) {                    // 字典=>Trie T=O(mn) S=O(mn)
        TrieNode *root = new TrieNode();
        for (int i = 0; i < words.size(); ++i) {
            TrieNode *t = root;
            for (int j = 0; j < words[i].size(); ++j) {
                int c = words[i][j] - 'a';
                if (!t->children[c]) {
                    t->children[c] = new TrieNode();
                }
                t = t->children[c];
                t->indexs.push_back(i);
            }
        }
        return root;
    }
    vector<vector<string>> wordSquares(vector<string>& words) {
        if (words.empty() || words[0].empty()) { return {}; }       // 处理特例空串

        TrieNode *root = buildTrie(words);
        vector<string> out(words[0].size());                        // 长=宽=单词长度
        vector<vector<string>> res;
        for (string word : words) {                                 // 枚举每个单词为第一行 // T=O(m*...)
            out[0] = word;
            helper(words, 1, root, out, res);                       // 从第2列长为1的前缀开始,递归找是否有满足条件的word sqare
        }
        return res;
    }
    void helper(vector<string>& words, int level, TrieNode* root,   // 看第level列的前缀[0~level-1]是否在Trie中且lead to新单词可填入第level行
                vector<string>& out, vector<vector<string>>& res) {
        if (level >= words[0].size()) {                             // level=word长,即已经找到一个word sqaure,加如结果集
            res.push_back(out);
            return;
        }
        string str = "";
        for (int i = 0; i < level; ++i) { str += out[i][level]; }   // 先得到第level列的前缀[0~level-1] // T=O(level))
        TrieNode *t = root;
        for (int i = 0; i < str.size(); ++i) {                      // 再看Trie中是否有此前缀 // T=O(level*...)
            int c = str[i] - 'a';
            if (!t->children[c]) { return; }                        // 若无则直接返回
            t = t->children[c];
        }
        for (int idx : t->indexs) {                                 // 若有则枚举含有该前缀的每个单词 // T=O(26*...)
            out[level] = words[idx];                                // 将该单词填到第level行
            helper(words, level + 1, root, out, res);               // 看第level+1列的前缀[0~level]是否在Trie中且lead to新单词可填入第level+1行
        }
    }
};
