/*
 * @lc app=lintcode id=132 lang=cpp
 *
 * [132] Word Search II
 *
 * https://www.lintcode.com/problem/word-search-ii/description
 *
 * lintcode
 * Hard (30.00%)
 * Total Accepted:    16372
 * Total Submissions: 54448
 * Testcase Example:  '["doaf","agai","dcan"]\n["dog","dad","dgdg","can","again"]\n'
 *
 * Given a matrix of lower alphabets and a dictionary. Find all words in the
 * dictionary that can be found in the matrix. A word can start from any
 * position in the matrix and go left/right/up/down to the adjacent position.
 * One character only be used once in one word. No same word in dictionary
 * 
 * Example 1:
 * Input：["doaf","agai","dcan"]，["dog","dad","dgdg","can","again"]
 * Output：["again","can","dad","dog"]
 * Explanation：
 *  d o a f
 *  a g a i
 *  d c a n
 * search in Matrix，so return ["again","can","dad","dog"].
 * 
 * Example 2:
 * Input：["a"]，["b"]
 * Output：[]
 * Explanation
 * a 
 * search in Matrix，return [].
 * Challenge: Using trie to implement your algorithm.
 *
 * @Category: DFS(Visited+回溯) + Trie 
 * @Idea Trie + DFS
 * 根据words建立Trie,DFS检查每个词是否在Trie中
 * T=O(m*n*n) S=O(m*n) m=字典中单词数, n=字典中单词平均长度
 */
class Solution {
public:
    /**
     * @param board: A list of lists of character
     * @param words: A list of string
     * @return: A list of string
     */
    // DFS(Visited+回溯) + Trie 
    // T=O(m*n*n) S=O(m*n) m=字典中单词数, n=字典中单词平均长度
    vector<string> wordSearchII(vector<vector<char>>& board, vector<string>& words) {
        if (words.empty() || board.empty() || board[0].empty()) { return {}; }          // 特例空board
        
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        Trie T;
        for (auto &word : words) { T.insert(word); }                                    // 按字典建Trie T=O(mn)) S=O(mn)
        vector<string> res;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {                                               // T=O(mn*...)
                if (T.root->child[board[i][j] - 'a']) {                                 // 若Trie有[i,j]开头的前缀
                    search(board, T.root->child[board[i][j] - 'a'], i, j, visit, res);  // DFS在Trie中找match的词 T=O(n)
                }
            }
        }
        return res;
    }
private:
    struct TrieNode {
        TrieNode *child[26];
        string word;
        TrieNode() : word("") {                                                         // 初始:以当前结点结尾的单词为空
            for (auto &a : child) { a = NULL; }                                         // 初始:26儿子都为空
        }
    };

    struct Trie {
        TrieNode *root;
        Trie() : root(new TrieNode()) {}                                                // 初始:根结点
        void insert(string s) {                                                         // 加词:每个字符加1层
            TrieNode *p = root;
            for (auto &a : s) {
                int i = a - 'a';
                if (!p->child[i]) { p->child[i] = new TrieNode(); }
                p = p->child[i];
            }
            p->word = s;                                                                // 记录以当前结点结尾的单词
        }
    };
    
    void search(vector<vector<char>>& board, TrieNode* p, int i, int j,                 // 从Trie结点p看字符[i][j]是否配词
                vector<vector<bool>>& visit, vector<string>& res) {
        if (!p->word.empty()) {                                                         // 若词在字典中,则加入res
            res.push_back(p->word);
            p->word.clear();                                                            // 坑:加后清空当前词标记,可能之后别词
        }
        visit[i][j] = true;                                                             // 标记board[i][j]已被访问过
        int dists[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto &dist : dists) {                                                      // DFS访问board[i][j]的4个邻居
            int nx = dist[0] + i, ny = dist[1] + j;
            if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() &&      // 若邻居没出界
                !visit[nx][ny] && p->child[board[nx][ny] - 'a']) {                      // 且没访问过且是某个词的前缀
                search(board, p->child[board[nx][ny] - 'a'], nx, ny, visit, res);       // 则递归查看那邻居是否匹配到词
            }
        }
        visit[i][j] = false;                                                            // 坑: 回溯,[i][j]未访问,可在别词中用
    }
};
