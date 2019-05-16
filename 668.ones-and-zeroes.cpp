/*
 * @lc app=lintcode id=668 lang=cpp
 *
 * [668] Ones and Zeroes
 *
 * https://www.lintcode.com/problem/ones-and-zeroes/description
 *
 * lintcode
 * Medium (45.00%)
 * Total Accepted:    1230
 * Total Submissions: 2716
 * Testcase Example:  '["10","0001","111001","1","0"]\n5\n3\n'
 *
 * In the computer world, use restricted resource you have to generate maximum
 * benefit is what we always want to pursue.
 * 
 * For now, suppose you are a dominator of m `0s` and n `1s` respectively. On
 * the other hand, there is an array with strings consisting of only `0s` and
 * `1s`.
 * 
 * Now your task is to find the maximum number of strings that you can form
 * with given m `0s` and n `1s`. Each `0` and `1` can be used at most once.
 * 
 * Example:
 * Input: ["10", "0001", "111001", "1", "0"] 5 3
 * Output: 4
 * Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, 
 * which are "10", "0001", "1", "0"
 * 
 * @Category DP (2维01背包+物品个数有限)
 * DP // T=O(mn) S=O(mn)
 * dp[i][j]表示由i个0和j个1构成的给定字符串的最大个数
 * dp[i][j]=max(dp[i][j], 1 + dp[i-当前串中0的个数][j-当前串中1的个数])
 * 初始 dp[0][0]=0
 * 顺序
 * for (str:strs) // 当前串
 *    for(c:str)c=='0' ? ++cnt0 : ++cnt1; // 计算当前串str中0的个数cnt0和1的个数cnt1
 *    for(i= m ~ cnt0)  // 倒序0总数(m ~ 当前串0总数)    // 正序降维得到的.否则如何解释?
 *      for(j= n ~ cnt1)  // 倒序0总数(n ~ 当前串1总数)  // 正序降维得到的.否则如何解释?
 * 	    dp[i][j]=max(dp[i][j], 1 + dp[i-cnt0][j-cnt1])  //max(不选str, 1+选str) 
 * 返回 dp[m][n]
 * 
 * 坑 for(i= m ~ cnt0)  // 倒序0总数(m ~ 当前串0总数)    正序降维得到的.否则如何解释?
 *      for(j= n ~ cnt1)  // 倒序0总数(n ~ 当前串1总数)  正序降维得到的.否则如何解释?
 * 坑 dp[i][j]=max(dp[i][j], 1 + dp[i-cnt0][j-cnt1]) 选当前串别忘+1
 */
class Solution {
public:
    /**
     * @param strs: an array with strings include only 0 and 1
     * @param m: An integer
     * @param n: An integer
     * @return: find the maximum number of strings
     */
    int findMaxForm2(vector<string> &strs, int m, int n) {
        // dp[t][i][j]表示任意选字符串使0的个数<=i和1的个数<=j的最大字符串个数
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));  // i个0j个1可以构成的最大字符串个数
        for (string str : strs) {
            int cnt0 = 0, cnt1 = 0;
            for (char ch : str) { (ch == '0') ? ++cnt0 : ++cnt1; }
            for (int i = m; i >= cnt0; --i) {  // 坑: 0的总数倒序(m~当前0总数) 不是m~1也不是cnt0~1
                for (int j = n; j >= cnt1; --j) {  // 坑: 1的总数倒序(n~当前1总数) 不是n~1也不是cnt1~1
                    dp[i][j] = max(dp[i][j], 1 + dp[i - cnt0][j - cnt1]);  // 坑:别忘记+1
                }
            }
        }
        return dp[m][n];
    }

    int findMaxForm0(vector<string> &strs, int m, int n) {  //TLE !!!必须降维
        int k = strs.size();
        // dp[t][i][j]表示前t个串任意选字符串使0的个数<=i和1的个数<=j的最大字符串个数
        vector<vector<vector<int>>> dp(k + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        // dp[0][i][j]=0; // 前0个串只能构成0个串
        for (int t = 1; t <= k; ++k) {  // 前k个串 坑:t从1开始因为t=0已经初始化过
            int cnt0 = 0, cnt1 = 0;
            for (char ch : strs[t - 1]) { (ch == '0') ? ++cnt0 : ++cnt1; }  // 坑: str[t-1]不是str[t]
            for (int i = cnt0; i <= m; ++i) {
                for (int j = cnt1; j <= n; ++j) {
                    dp[t][i][j] = max(dp[t - 1][i][j], 1 + dp[t - 1][i - cnt0][j - cnt1]);
                }
            }
        }
        return dp[k][m][n];
    }
    
    // 降维 1
    int findMaxForm1(vector<string> &strs, int m, int n) {  // 任然TLE!!!
        int k = strs.size();
        // dp[t][i][j]表示任意选字符串使0的个数<=i和1的个数<=j的最大字符串个数
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        // dp[0][i][j]=0; // 前0个串只能构成0个串
        int cur = 0, old = 0;
        for (int t = 1; t <= 2; ++k) {  // 前k个串 坑:t从1开始因为t=0已经初始化过
            int cnt0 = 0, cnt1 = 0;
            for (char ch : strs[t - 1]) { (ch == '0') ? ++cnt0 : ++cnt1; }  // 坑: str[t-1]不是str[t]
            old = cur;
            cur = 1 - cur;
            for (int i = cnt0; i <= m; ++i) {
                for (int j = cnt1; j <= n; ++j) {
                    dp[cur][i][j] = max(dp[old][i][j], 1 + dp[old][i - cnt0][j - cnt1]);
                }
            }
        }
        return dp[cur][m][n];  // 坑 dp[cur][m][n]不是dp[k][m][n]
    }

    // 降维 2
    int findMaxForm(vector<string> &strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int t = 1; t <= strs.size(); ++t) {
            int cnt0 = 0, cnt1 = 0;
            for (char ch : strs[t - 1]) { (ch == '0') ? ++cnt0 : ++cnt1; }  // 坑: str[t-1]不是str[t]
            for (int i = m; i >= cnt0; --i) {  // 降维后须倒序
                for (int j = n; j >= cnt1; --j) {  // 降维后须倒序
                    dp[i][j] = max(dp[i][j], 1 + dp[i - cnt0][j - cnt1]);  // 坑: 别忘+1
                }
            }
        }
        return dp[m][n];
    }
};
