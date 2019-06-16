/*
 * @lc app=lintcode id=119 lang=cpp
 *
 * [119] Edit Distance
 *
 * https://www.lintcode.com/problem/edit-distance/description
 *
 * lintcode
 * Medium (33.00%)
 * Total Accepted:    16868
 * Total Submissions: 50823
 * Testcase Example:  '"horse"\n"ros"'
 *
 * Given two words *word1* and *word2*, find the minimum number of steps
 * required to convert word1 to word2. (each operation is counted as 1 step.)
 * 
 * You have the following 3 operations permitted on a word:
 * 
 * - Insert a character
 * - Delete a character
 * - Replace a character
 * 
 * * Example 1:
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation: 
 * horse -> rorse (replace 'h' with 'r')
 * rorse -> rose (remove 'r')
 * rose -> ros (remove 'e')
 *
 *  Example 2:
 * Input: word1 = "intention", word2 = "execution"
 * Output: 5
 * Explanation: 
 * intention -> inention (remove 't')
 * inention -> enention (replace 'i' with 'e')
 * enention -> exention (replace 'n' with 'x')
 * exention -> exection (replace 'n' with 'c')
 * exection -> execution (insert 'u')
 * 
 * * @Category DP 双序列型
 * @Idea
 * DP T=O(mn) S=O(mn)
 * dp[i][j]表示S[0,i)到T[0,j)的edit distance
 * dp[i][j]=
 * 1) if s[i]==t[j]: dp[i][j]=dp[i-1][j-1]
 * 2) if s[i]!=t[j]: min(dp[i-1][j], min(dp[i-1][j-1], dp[i][j-1])) + 1
 * Explanation:
 * Let's say we have 2 words "abcde" and "fghij", and we already know the min distance from "abcd" to "fgh".
 * a b c d
 * f g h
 * Now we would like to go a step further and convert "abcde" to "fghi".
 * a b c d e
 * f g h i
 * There're 3 ways to accomplish it:
 * 1. If we know the min distance from "abcd" to "fgh", then we just need to replace "e" by "i".
 * a b c d       a b c d e(replace "e" by "i") 
 *           ->                           ->  dp[i-1][j-1] + 1 (for replacement)
 * f g h         f g h i
 * 2. If we know the min distance from "abcd" to "fghi", then for "abcde", we just need to delete "e".
 * a b c d        a b c d e(delete)
 *           ->                           ->  dp[i-1][j] + 1 (for deletion)
 * f g h i        f g h i
 * 3. If we know the min distance from "abcde" to "fgh", then we need to add an "i" to "abcde"
 * a b c d e      a b c d e(add an "i")
 *           ->                           ->  dp[i][j-1] + 1 (for insertion)
 * f g h          f g h i
 * 
 * 坑 dp[m+1][n+1]不是dp[m][n]
 * 坑 初始化 dp[0][j]=j, dp[i][0]=i
 * 坑 初始化后i和j都从1开始
 * 坑 s[i-1]==t[j-1] 而不是s[i]==t[j]!!!
 * 坑 1+min(s[i-1][j-1],min(s[i-1][j],s[i][j-1])) 别忘+1!!!
 */
class Solution {
public:
    /**
     * @param word1: A string
     * @param word2: A string
     * @return: The minimum number of steps.
     */
    int minDistance(string &word1, string &word2) {
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= m; ++i) { dp[i][0] = i; }
        for (int j = 0; j <= n; ++j) { dp[0][j] = j; }
        for (int i = 1; i <= m; ++i) {  // 坑 i从1开始
            for (int j = 1; j <= n; ++j) {  // 坑 j从1开始
                if (word1[i - 1] == word2[j - 1]) {  // 坑 s[i-1]而不是s[i], t[j-1]而不是t[j]!!!
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i- 1][j], dp[i][j - 1]));  // 坑 +1!!!
                }
            }
        }
        return dp[m][n];
    }
};
