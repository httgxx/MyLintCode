/*
 * @lc app=lintcode id=442 lang=cpp
 *
 * [442] Implement Trie (Prefix Tree)
 *
 * https://www.lintcode.com/problem/implement-trie-prefix-tree/description
 *
 * lintcode
 * Medium (39.00%)
 * Total Accepted:    14065
 * Total Submissions: 35759
 * Testcase Example:  'insert("lintcode")\nsearch("lint")\nstartsWith("lint")\n'
 *
 * Implement a Trie with `insert`, `search`, and `startsWith` methods.
 * 
 * Example 1:
 * Input:
 *  insert("lintcode")
 *  search("lint")
 *  startsWith("lint")
 * Output:
 *  false
 *  true
 * 
 * Example 2:
 * Input:
 *  insert("lintcode")
 *  search("code")
 *  startsWith("lint")
 *  startsWith("linterror")
 *  insert("linterror")
 *  search("lintcode“)
 *  startsWith("linterror")
 * Output:
 *  false
 *  true
 *  false
 *  true
 *  true
 * 
 * @Category Trie
 * @Idea T=O(n) S=O(26n) n=word.max_length
 * class TrieNode  //不是TreeNode!!
 *   TrieNode * children[26]//初始化为all null
 *   bool isWord            //初始化为false
 * class Trie
 *   TrieNode* root //初始化为新TrieNode
 *   insert,search,startwith 模板:
 *      p=root
 *      for(c : word or prefix)
 *         i=c-'a'
 *         if(!p->child[i]) xxx //insert=new TrieNode(),search/startwith=return false
 *         p=p->child[i]
 *      yyy //insert=p->isWord=true, search=return p->isWord, startWith=return true
 * 
 * 坑: 明确初始化isWord为false, 明确for-loop初始化TrieNode* child[26]为全NULL 
 * 坑: for(auto & c : word)是word而不是p->child!!!
 *            
 */
class TrieNode {
public:
    TrieNode * child[26];
    bool isWord;
    TrieNode() : isWord(false) {            // 明确初始化为false
        for (auto &c : child) { c = NULL; } // 明确初始化为空指针
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();              // 初始化为新TrieNode
    }

    /*
     * @param word: a word
     * @return: nothing
     */
    void insert(string &word) {
        TrieNode *p = root;
        for (auto &c : word) {                  // 坑: 是word而不是p->child
            int i = c - 'a';
            if (!p->child[i]) { p->child[i] = new TrieNode(); }
            p = p->child[i];
        }
        p->isWord = true;
    }

    /*
     * @param word: A string
     * @return: if the word is in the trie.
     */
    bool search(string &word) {
        TrieNode *p = root;
        for (auto &c : word) {              // 坑: 是word而不是p->child
            int i = c - 'a';
            if (!p->child[i]) { return false; }
            p = p->child[i];
        }
        return p->isWord;
    }

    /*
     * @param prefix: A string
     * @return: if there is any word in the trie that starts with the given prefix.
     */
    bool startsWith(string &prefix) {
        TrieNode *p = root;
        for (auto &c : prefix) {            // 坑: 是word而不是p->child
            int i = c - 'a';
            if (!p->child[i]) { return false; }
            p = p->child[i];
        }
        return true;
    }
private:
    TrieNode* root;
};
