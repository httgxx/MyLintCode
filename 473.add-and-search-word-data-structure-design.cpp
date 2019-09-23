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
 * 坑:别忘初始化root!!!
 * 
 */

class WordDictionary {
public:
    struct TrieNode {
    public:
        TrieNode *child[26];
        bool isWord;
        TrieNode() : isWord(false) {
            for (auto &a : child) a = NULL;
        }
    };
    
    WordDictionary() {
        root = new TrieNode();
    }
    
    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode *p = root;
        for (auto &a : word) {
            int i = a - 'a';
            if (!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->isWord = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return searchWord(word, root, 0);
    }
    
    bool searchWord(string &word, TrieNode *p, int i) {
        if (i == word.size()) return p->isWord;
        if (word[i] == '.') {
            for (auto &a : p->child) {
                if (a && searchWord(word, a, i + 1)) return true;
            }
            return false;
        } else {
            return p->child[word[i] - 'a'] && searchWord(word, p->child[word[i] - 'a'], i + 1);
        }
    }
    
private:
    TrieNode *root;
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");

