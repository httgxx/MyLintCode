/*
 * @lc app=lintcode id=473 lang=cpp
 *
 * [473] Add and Search Word - Data structure design
 *
 * https://www.lintcode.com/problem/add-and-search-word-data-structure-design/description
 *
 * lintcode
 * Medium (28.00%)
 * Total Accepted:    11396
 * Total Submissions: 40332
 * Testcase Example:  'addWord("a")\nsearch(".")\n'
 *
 * Design a data structure that supports the following two operations:
 * `addWord(word)` and `search(word)`
 * 
 * `search(word)` can search a literal word or a regular expression string
 * containing only letters `a-z` or `.`.
 * 
 * A `.` means it can represent any one letter.
 * 
 * Example 1:
 * Input:
 *  addWord("a")
 *  search(".")
 * Output:
 *  true
 * 
 * Example 2:
 * Input:
 *  addWord("bad")
 *  addWord("dad")
 *  addWord("mad")
 *  search("pad")  
 *  search("bad")  
 *  search(".ad")  
 *  search("b..")  
 * Output:
 *  false
 *  true
 *  true
 *  true
 * 
 * @Category Trie + "."
 * @Idea T=O(n) S=O(n)
 * addWord不变
 * search要递归处理"."
 *  若'.'则递归search每个child 
 *  否则只递归search某个child
 * bool searchHelper(word, parent, idx)要在parent的child中找w[idx]
 * 必须传parent而不能传child
 * 
 * 坑:别忘WordDictionary()初始化root!!!
 * 坑:for(auto &c:child) 勿忘&不然不改变!!!
 * 
 */
class WordDictionary {
public:
    struct TrieNode {
    public:
        TrieNode *child[26];
        bool isWord;
        TrieNode() : isWord(false) {
            for (auto &c : child) { c = NULL; }  // 手动全赋NULL // 坑: 勿忘&不然不改变!!!
        }
    };

    WordDictionary() {
        root = new TrieNode();                  // 坑:别忘初始化root!!!
    }

    /*
     * @param word: Adds a word into the data structure.
     * @return: nothing
     */
    void addWord(string &word) {
        TrieNode *p = root;
        for (auto c : word) {
            int i = c - 'a';
            if (!p->child[i]) { p->child[i] = new TrieNode(); }
            p = p->child[i];
        }
        p->isWord = true;
    }

    /*
     * @param word: A word could contain the dot character '.' to represent any one letter.
     * @return: if the word is in the data structure.
     */
    bool search(string &word) {
        return searchHelper(word, root, 0);                     // search(w,parent,idx)在parent的儿子里找w[idx]
    }

    bool searchHelper(string &word, TrieNode *parent, int i) {  // i是当前word中待match的字符的index
        if (i == word.length()) { return parent->isWord; }      // 整个word都match完
        if (word[i] == '.') {                                   // 遇到'.'
            for (auto &c : parent->child) {                     // 在每个儿子的儿子中找word的下个字符
                if (c && searchHelper(word, c, i + 1)) {        // 递归匹配下个字符
                    return true;                                // 从递归最底层返回true,继续返回true
                }
            }
            return false;                                       // 每个儿子的支路都匹配失败,返回false
        }
        else {
            TrieNode *t = parent->child[word[i] - 'a'];
            return t && searchHelper(word, t, i + 1);           // 在当前匹配的儿子的儿子中找word的下个字符
                                                                // 从递归最底层返回的结果直接返回上1层
        }
    }
private:
    TrieNode *root;
};
