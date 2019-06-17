/*
 * @lc app=lintcode id=623 lang=cpp
 *
 * [623] K Edit Distance
 *
 * https://www.lintcode.com/problem/k-edit-distance/description
 *
 * lintcode
 * Hard (33.00%)
 * Total Accepted:    3378
 * Total Submissions: 10062
 * Testcase Example:  '["abc","abd","abcd","adc"]\n"ac"\n1\n'
 *
 * Given a set of strings which just has lower case letters and a target
 * string, output all the strings for each the edit distance with the target no
 * greater than `k`.
 * 
 * You have the following 3 operations permitted on a word:
 * - Insert a character
 * - Delete a character
 * - Replace a character
 * 
 * Example 1:
 * Given words = `["abc", "abd", "abcd", "adc"]` and target = `"ac"`, k = `1`
 * Return `["abc", "adc"]`
 * Input:["abc", "abd", "abcd", "adc"]  "ac"  1
 * Output:["abc","adc"]
 * Explanation:
 * "abc" remove "b"
 * "adc" remove "d"
 * 
 * Example 2:
 * Input:["acc","abcd","ade","abbcd"]  "abc"  2
 * Output:["acc","abcd","ade","abbcd"]
 * Explanation:
 * "acc" turns "c" into "b"
 * "abcd" remove "d"
 * "ade" turns "d" into "b" turns "e" into "c"
 * "abbcd" gets rid of "b" and "d"
 * 
 * @Category Trie + DFS 
 * 滚动数组,用字典树对dfs进行优化。
 */

class Solution {
public:
    class TrieNode {
    public:
        TrieNode() {
            for (int i = 0; i < 26; ++i)
                children[i] = NULL;

            hasWord = false;
        }
        TrieNode* children[26];
        bool hasWord;
        string str;

        // Inserts a word into the trie.
        static void addWord(TrieNode* root, string& word) {
            TrieNode *p = root;
            for(int i = 0; i < word.size(); i++){
                if (p->children[word[i] - 'a'] == NULL) {
                    p->children[word[i] - 'a'] = new TrieNode();
                }
                p = p->children[word[i] - 'a'];
            }
            p->hasWord = true;
            p->str = word;
        }
    
    };
    /**
     * @param words a set of stirngs
     * @param target a target string
     * @param k an integer
     * @return output all the strings that meet the requirements
     */
    vector<string> kDistance(vector<string>& words, string& target, int k) {
        TrieNode* root = new TrieNode();
        int n = words.size();
        for (int i = 0; i < n; i++) {
            TrieNode::addWord(root, words[i]);
        }

        vector<string> result;
        n = target.size();
        vector<int> dp(n + 1, 0);
        for (int i = 0; i <= n; ++i)
            dp[i] = i;

        find(root, result, k, target, dp);
        return result;
    }

    void find(TrieNode* node, vector<string>& result, int k, string& target, vector<int>& dp) {
        int n = target.size();
        if (node->hasWord && dp[n] <= k) {
            result.push_back(node->str);
        }
        vector<int> next(n + 1, 0);
        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != NULL) {
                next[0] = dp[0] + 1;
                for (int j = 1; j <= n; j++) {
                    if (target[j - 1] - 'a' == i) {
                        next[j] = min(dp[j - 1], min(next[j - 1] + 1, dp[j] + 1));
                    } else {
                        next[j] = min(dp[j - 1] + 1, min(next[j - 1] + 1, dp[j] + 1));
                    }
                }
                find(node->children[i], result, k, target, next);
            }
        }
    }
};
