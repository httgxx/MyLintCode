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
 * S0: DP // T=O(kmn) S=O(kmn) k=strs.size() => TLE!!!
 * dp[t][i][j]表示前k个串任意选使得0的总个数<=i且1的总个数<=j的最大字符串个数
 * dp[t][i][j]=max(dp[t-1][i][j], 1 + dp[t-1][i-当前串中0的个数][j-当前串中1的个数])
 * 初始 dp[0][i][j]=0
 * 顺序
 * int k = strs.size();
 * for (t=1~k) // 前t个串
 *    for(c:strs[t-1])c=='0' ? ++cnt0 : ++cnt1; // 计算当前串str中0的个数cnt0和1的个数cnt1
 *    for(i= cnt0~m)  // 正序0总数(当前串0总数 ~ m)
 *      for(j= cnt1~n)  // 正序0总数(当前串1总数 ~ n)
 * 	    dp[t][i][j]=max(dp[t-1][i][j], 1 + dp[t-1][i-cnt0][j-cnt1])  //max(不选str, 1+选str) 
 * 返回 dp[k][m][n]
 * 
 * 坑: strs[t-1]不是strs[t]!!!
 * 
 * S1: 滚动数组降维1 T=O(kmn) S=O(2mn) => 任然TLE!!!
 * int cur=0,old=0;
 * for (t=1~k) // 前t个串
 *    for(c:strs[t-1])c=='0' ? ++cnt0 : ++cnt1; // 计算当前串str中0的个数cnt0和1的个数cnt1
 *    old=cur;cur=1-cur;
 *    for(i= cnt0~m)  // 正序0总数(当前串0总数 ~ m)
 *      for(j= cnt1~n)  // 正序0总数(当前串1总数 ~ n)
 * 	        dp[cur][i][j]=max(dp[old][i][j], 1 + dp[old][i-cnt0][j-cnt1])  //max(不选str, 1+选str) 
 * 返回 dp[cur][m][n]
 * 
 * S2: 倒序降维2 T=O(kmn) S=O(mn)
 * for (str : strs) // 前t个串
 *    for(c:str)c=='0' ? ++cnt0 : ++cnt1; // 计算当前串str中0的个数cnt0和1的个数cnt1
 *    for(i= m~cnt0)  // 倒序0总数(m~当前串0总数)
 *      for(j= n~cnt1)  // 倒序0总数(n~当前串1总数)
 * 	        dp[i][j]=max(dp[i][j], 1 + dp[i-cnt0][j-cnt1])  //max(不选str, 1+选str) 
 * 返回 dp[m][n]
 * 
 * 坑 计算每个串的0总数和1总数不用strs数组坐标 用for(str:strs){for(ch : str){...}}以免弄错坐标
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
    // 降维 2 T=O(kmn) S=O(mn)
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

    // T=O(kmn) S=O(kmn) => TLE
    int findMaxForm0(vector<string> &strs, int m, int n) {
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
    
    // 降维 1  T=O(kmn) S=O(2mn) => TLE
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
};
