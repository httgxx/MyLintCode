/*
 * @lc app=lintcode id=108 lang=cpp
 *
 * [108] Palindrome Partitioning II
 *
 * https://www.lintcode.com/problem/palindrome-partitioning-ii/description
 *
 * lintcode
 * Medium (24.00%)
 * Total Accepted:    14455
 * Total Submissions: 59332
 * Testcase Example:  '"a"\n'
 *
 * Given a string `s`, cut `s` into some substrings such that every substring
 * is a palindrome. 
 * 
 * Return the **minimum** cuts needed for a palindrome partitioning of *s*.
 * 
 * Example 1:
 *   Input: "a"
 *   Output: 0
 *   Explanation: "a" is already a palindrome, no need to split.
 * Example 2:
 *   Input: "aab"
 *   Output: 1
 *   Explanation: Split "aab" once, into "aa" and "b", both palindrome.
 * 
 * @Category DP
 * @Idea
 * DP T=O(n^2) S=O(n^2)
 * dp[i]表示前i个字符s[0~i-1]最少切几刀可以分回文串
 * dp[i]=min(dp[i],dp[j]+1|0<=j<=i-1且s[j~i-1]是回文串)
 * 初始 dp[0]=0
 * 坑 j=0~i-1
 * 坑 求划分次数而不是划分区间数,即返回dp[n]-1
 * 坑 :中心发散匹配两边 T=O(n^2) S=O(1))
 
 * 判断s[l~r]是否是回文串, T=O(n^2) S=O(n^2)
 * case1: l==r     x => s[l]==s[r] && r-l==0
 * case2: r=l+1   xx => s[l]==s[r] && r-l==1
 * case3: r>l+1 x..x => s[l]==s[r] && r-l>1 && isPal[l+1][r-1]
 *       合并判断条件 => s[i]==s[j] && (r-l<=1 || isPal[l+1][r-1])
 * 注: r-l>1时[r]和[l]之间还有字符,所以l+1和r-1都不会坐标越界
 */
class Solution {
public:
    /**
     * @param s: A string
     * @return: An integer
     */
    int minCut(string &s) {
        if (s.empty()) return 0;  // 特例
        int n = s.size();
        vector<vector<bool>> p(n, vector<bool>(n, false));  //存各子串是否回文
        vector<int> dp(n);  // dp[i]=[0~i]最少切几刀成回文串 //坑:几刀而非几段!
        for (int r = 0; r < n; ++r) {  // 尾 right
            dp[r] = r;  // 最多每个字符自成回文串,r为index则有r+1段,但只用切r刀
            for (int l = 0; l <= r; ++l) {  // 头 left
                if (s[l] == s[r] && (r - l < 2 || p[l + 1][r - 1])) {
                    p[l][r] = true;
                    dp[r] = (l == 0) ? 0 : min(dp[r], dp[l - 1] + 1);
                    // 坑: l为0时整个子串都回文不需切,但dp须赋0否则仍是初始值r 
                }
            }
        }
        return dp[n - 1];  // 坑：dp存几刀而不是存几段!
    }

    int minCut1(string s) {
        if (s.empty()) return 0;
        int n = s.size();
        vector<int> dp(n + 1, INT_MAX); //dp[i]=前i个字符s[0~i-1]的最少切几刀成回文区间
        dp[0] = -1;
        for (int i = 0; i < n; ++i) {
            for (int len = 0; i - len >= 0 && i + len < n && s[i - len] == s[i + len]; ++len) {
                dp[i + len + 1] = min(dp[i + len + 1], 1 + dp[i - len]);
            }
            for (int len = 0; i - len >= 0 && i + len + 1 < n && s[i - len] == s[i + len + 1]; ++len) {
                dp[i + len + 2] = min(dp[i + len + 2], 1 + dp[i - len]);
            }
        }
        return dp[n];
    }
};
