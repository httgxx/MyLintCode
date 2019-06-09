/*
 * @lc app=lintcode id=430 lang=cpp
 *
 * [430] Scramble String
 *
 * https://www.lintcode.com/problem/scramble-string/description
 *
 * lintcode
 * Hard (37.00%)
 * Total Accepted:    6879
 * Total Submissions: 18366
 * Testcase Example:  '"great"\n"rgeat"'
 *
 * Given a string `s1`, we may represent it as a binary tree by partitioning it
 * to two non-empty substrings recursively.
 * 
 * Below is one possible representation of `s1 = "great"`:
 * 
 * ⁠       great
 * ⁠      /    \
 * ⁠     gr    eat
 * ⁠    / \    /  \
 * ⁠   g   r  e   at
 * ⁠              / \
 * ⁠             a   t
 * 
 * To scramble the string, we may choose any non-leaf node and swap its two
 * children.
 * 
 * For example, if we choose the node `"gr"` and swap its two children, it
 * produces a scrambled string `"rgeat"`.
 * 
 * ⁠       rgeat
 * ⁠      /    \
 * ⁠     rg    eat
 * ⁠    / \    /  \
 * ⁠   r   g  e   at
 * ⁠              / \
 * ⁠             a   t
 * 
 * We say that `"rgeat"` is a scrambled string of `"great"`.
 * 
 * Similarly, if we continue to swap the children of nodes `"eat"` and `"at"`,
 * it produces a scrambled string `"rgtae"`.
 * 
 * ⁠       rgtae
 * ⁠      /    \
 * ⁠     rg    tae
 * ⁠    / \    /  \
 * ⁠   r   g  ta  e
 * ⁠          / \
 * ⁠         t   a
 * 
 * We say that `"rgtae"` is a scrambled string of `"great"`.
 * 
 * Given two strings `s1` and `s2` of the same length, determine if `s2` is a
 * scrambled string of `s1`.
 * 
 * @Category DP 区间型
 * @Idea
 * S1: DP //T=O(mn) S=O(mn)
 * 1. 比较长度 if(s1.len!=s2.len) => false
 * 2. 直接比较整个串 if(s1==s2)   => true
 * dp[i][j]表示s1[i,i+k-1]和s2[j,j+k-1]是否是scramble
 * s1和s2是scramble => s1=s11|s12, s2=s21|s22 使得
 *    s11和s21是scramble && s12和s22是scramble 
 * 或 s11和s22是scramble && s12和s21是scramble
 * dp[i][j]=
 * 
 * S2: Recursion //T=O(nlogn) S=(1) n=max(s1.len,s2.len)
 * 1. 比较长度 if(s1.len!=s2.len) => false
 * 2. 直接比较整个串 if(s1==s2)    => true
 * 2. 排序 sort(s1.begin(), s1.end()); sort(s2.begin(), s2.end())
 * 3. 排序后比较整个串 if(s1!=s2)  => false
 * 4. 枚举每个i位置劈开s1=>s11|s12, s2=>s21|s22
 *    如果 case1: s11和s21是Scambled && s12和s22是Scambled => 对(s11,s21)递归 对(s12,s22)递归
 *      或 case2: s11和s22是Scambled && s12和s21是Scambled => 对(s11,s22)递归 对(s12,s21)递归
 */
class Solution {
public:
    /**
     * @param s1: A string
     * @param s2: Another string
     * @return: whether s2 is a scrambled string of s1
     */
    // DP T=O(mn) S=O(mn)
    bool isScramble(string &s1, string &s2) {
        if (s1.size() != s2.size()) return false;
        if (s1 == s2) return true;
        int n = s1.size();

        // dp[i][j][k]表示"s1以第i个字符为起点且长为k的子串"是否和
        // "s2中以第j个字符为起点且长为k的子串"互为scramble
        vector<vector<vector<bool>>> dp (
            n,
            vector<vector<bool>>(n, vector<bool>(n + 1, false)));  // 坑 第3维是长度所以大小是n+1
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j][1] = s1[i] == s2[j];  // 初始化长度为1的区间
            }
        }

        for (int len = 2; len <= n; ++len) {  // 按子串长度从小到大(2~n)来计算对应的dp值
            for (int i = 0; i <= n - len; ++i) {  // s1子串起点
                for (int j = 0; j <= n - len; ++j) {  // s2子串起点
                    for (int k = 1; k < len; ++k) {  // 在k处劈s1成2段
                        if ((dp[i][j][k] && dp[i + k][j + k][len - k]) ||  // s11和s21互为scramble且s12和s22互为scramble
                            (dp[i + k][j][len - k] && dp[i][j + len - k][k])) {  // s12和s21互为scramble且s11和s22互为scramble
                            dp[i][j][len] = true;
                        }
                    }
                }
            }
        }

        return dp[0][0][n];  // 坑 两串起点都为0 长度都为n
    }

    // Recursion T=O(nlogn + mlogm + n!)? 
    bool isScramble1(string &s1, string &s2) {
        if (s1.size() != s2.size()) return false;  // length mismatch
        if (s1 == s2) return true;  // exact match
        
        string str1 = s1, str2 = s2;
        sort(str1.begin(), str1.end());  // sort T=O(nlogn)
        sort(str2.begin(), str2.end());
        if (str1 != str2) return false;  // mismatch after sort
        
        for (int i = 1; i < s1.size(); ++i) {
            string s11 = s1.substr(0, i), s12 = s1.substr(i);
            string s21 = s2.substr(0, i), s22 = s2.substr(i);
            if (isScramble(s11, s21) && isScramble(s12, s22)) return true;
            
            s21 = s2.substr(s1.size() - i);
            s22 = s2.substr(0, s1.size() - i);
            if (isScramble(s11, s21) && isScramble(s12, s22)) return true;
        }
        return false;
    }

};
