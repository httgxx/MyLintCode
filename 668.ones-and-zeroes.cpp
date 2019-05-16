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
    int findMaxForm(vector<string> &strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (string str : strs) {
            int cnt0 = 0, cnt1 = 0;
            for (char ch : str) { (ch == '0') ? ++cnt0 : ++cnt1; }
            for (int i = m; i >= cnt0; --i) {  // 坑: 0的总数倒序(m~当前0总数) 
                for (int j = n; j >= cnt1; --j) {  // 坑: 1的总数倒序(n~当前1总数)
                    dp[i][j] = max(dp[i][j], 1 + dp[i - cnt0][j - cnt1]);  // 坑:别忘记+1
                }
            }
        }
        return dp[m][n];
    }
};
