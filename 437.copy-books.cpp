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
 * 题意:求某种划分方式,将n本书分成<=K段(抄写员),使得所有段(各个抄写员抄的书)的数字和(页数和)的最大值(最大耗时)最小
 * 思路:若最后一段的起点是第j本书(0<=j<=n-1),则k个人抄n本书的时间t(k,n)=max(t(k-1,j),sum(A[j]~A[i-1]) 
 * j越小则sum(A[j]~A[i-1])越大,但可能t(k-1,j)更小使得两者的max更小,不确定,所以需要枚举j来求max的min
 * t(k-1,j)是t(k,n)的子问题 => 用DP
 * 
 * dp[i][j]表示前i(0<=i<=K)个人抄j(0<=j<=n)本书的最少时间
 * 枚举最后一段起点p,即最后1个人从第p本书开始抄
 * 公式 dp[i][j] = min( max(dp[i-1][p],sum(A[p]~A[j-1])) )|0<=p<=j 注: p=j要包括,指最后一个人抄0本书
 * 初始 dp[0~K][0]=0       // 0本书花0时间
 *      dp[0][1~n]=INT_MAX // 0个人无法抄完>0本书     
 * 返回 dp[K][n]
 * 
 * 时间 T=O(K*n*n) //K本书*n个人*(枚举0<=p<=j<=n) 
 * 空间 S=O(K*n) => 滚动数组降维 => O(n)
 * 
 * 坑 0<=p<=j而不是0<=p<=j-1, 0本书=>起始j>j-1,j本书=>起始0
 * 坑 特例K>n即人数>书数时 => 按照K=n求
 * 坑 min(max(...))所以初始化成无穷大INT_MAX
 * 坑 倒着循环枚举t因为总是要抄最后几本书
 * 坑 先求min(max)在算sum因为要包括不抄1本书的情况
 */
class Solution {
public:
    /**
     * @param pages: an array of integers
     * @param k: An integer
     * @return: an integer
     */
    // DP
    int copyBooks(vector<int> &pages, int K) {  // K个人
        int n = pages.size();
        if (n == 0) { return 0; }

        if (K > n) { K = n; }  // 坑: 人多于书,每个人条件一样,所以忽略多余的不抄书的人

        vector<vector<int>> dp(K + 1, vector<int>(n + 1, INT_MAX));  // 坑: 求min(...)故初始为INT_MAX
        dp[0][0] = 0;  // 0个人抄0本书不花时间
                       // 首行dp[0][j]除了[0][0]=0之外都为INT_MAX: 0个人抄>0本书都做不到
        // 前i个人抄前j本书
        for (int i = 1; i <= K; ++i) {       // 前i个人[1~K] //i=0在之前dp[0][0]=0和缺省值INT_MAX已设
            dp[i][0] = 0; // 抄0本书只花0时间
            for (int j = 1; j <= n; ++j ) {  // 前j本书[1~n] //j=0在之前dp[i][0]=0中已设
                int s = 0; // 最后一个人抄写的总页数A[k]+...+A[j-1]
                for (int k = j; k >= 0; --k) {  // 坑: 倒着循环
                    if (dp[i - 1][k] != INT_MAX) {  // 坑: i-1=0时dp[0][k]=初始值INT_MAX不能用于计算min
                        dp[i][j] = min(dp[i][j], max(dp[i - 1][k], s));
                    }
                    // 为下一次计算准备s
                    if (k > 0) { s += pages[k - 1]; }  // 坑: 先求dp再计算s 因为不抄书k=0时还是要计算dp
                }
            }
        }

        return dp[K][n];
    }
};
