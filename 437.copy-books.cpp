/*
 * @lc app=lintcode id=437 lang=cpp
 *
 * [437] Copy Books
 *
 * https://www.lintcode.com/problem/copy-books/description
 *
 * lintcode
 * Hard (32.00%)
 * Total Accepted:    11598
 * Total Submissions: 35598
 * Testcase Example:  '[3,2,4]\n2\n'
 *
 * Given `n` books and the `i-th` book has `pages[i]` pages. There are `k`
 * persons to copy these books.
 * 
 * These books list in a row and each person can claim a continous range of
 * books. For example, one copier can copy the books from `i-th` to `j-th`
 * continously, but he can not copy the 1st book, 2nd book and 4th book
 * (without 3rd book).
 * 
 * They start copying books at the same time and they all cost 1 minute to copy
 * 1 page of a book. What's the best strategy to assign books so that the
 * slowest copier can finish at earliest time? 
 * 
 * Return the shortest time that the slowest copier spends.
 * 
 * Example 1:
 * Input: pages = [3, 2, 4], k = 2
 * Output: 5
 * Explanation: 
 * First person spends 5 minutes to copy book 1 and book 2.
 * Second person spends 4 minutes to copy book 3.
 * 
 * @Categories DP (划分比较型)
 * @Idea
 * S1: DP // T=O(kn^2) S=O(kn)=>降维O(n) k个人n本书
 * dp[i][j]表示前i个人(0~i-1)抄j本书(0~j-1)的最少时间
 * 枚举p:最后一段起点即最后1个人(第i-1个人)抄书起点,即抄写第p到j-1本书
 * dp[i][j]=min(dp[i][j], max(dp[i-1][p],a[p]+a[p+1]+...+dp[j-1])|0<=p<=j) //p=j表明抄0本书
 * 初始 0个人:dp[0][0~n]=INT_MAX, 0本书:dp[0~k][0]=0
 * 返回 dp[k][n]
 * 
 * 坑 0<=p<=j而不是0<=p<=j-1,枚举最后1个人抄0~j本书的起始,0本书=>起始j>j-1,j本书=>起始0
 * 坑 特例k>n即人数>书数时=>k=n
 * 坑 min(max(...))所以初始化成无穷大INT_MAX
 * 坑 倒着循环枚举t因为总是要抄最后几本书
 * 坑 先求min(max)在算sum因为要包括不抄1本书的情况
 * 
 * S2: 二分法??
 */
class Solution {
public:
    /**
     * @param pages: an array of integers
     * @param k: An integer
     * @return: an integer
     */
    int copyBooks(vector<int> &pages, int K) {
        int n = pages.size();
        if (n == 0) { return 0; }

        if (K > n) { K = n; }  // 坑: 人多于书,每个人条件一样,所以去除多余人

        vector<vector<int>> dp(K + 1, vector<int>(n + 1, INT_MAX));  // 坑: min(max(..))初始为INT_MAX
        dp[0][0] = 0;  // 0个人抄0本书不花时间
                       // 首行dp[0][j]除了[0][0]=0之外都为INT_MAX: 0个人抄>0本书都做不到
        for (int i = 1; i <= K; ++i) {  // 前i个人[0~i-1]
            dp[i][0] = 0;  // 初始化首列: 抄0本书任何人数都不花时间
            for (int j = 1; j <= n; ++j ) {  // 前j本书[0~j-1]
                int s = 0;  // sum(a[t~j-1])
                for (int k = j; k >= 0; --k) {  // 坑: 倒着循环因为总是要抄最后几本书
                    if (dp[i - 1][k] != INT_MAX) {  // 坑: ???
                        dp[i][j] = min(dp[i][j], max(dp[i - 1][k], s));
                    }
                    if (k > 0) { s += pages[k - 1]; }  // 坑: 先算后加因为要考虑一本都不抄的情况
                }
            }
        }

        return dp[K][n];
    }
};
