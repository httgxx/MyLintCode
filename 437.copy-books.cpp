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
    // DP: T=O(k*n*n) S=O(k*n)
    // n本书划分成<=k段使得各段书总页数的最大值最小 => 枚举最后一段起点p
    // dp[i][j]表示前i个人抄写前j本书的最少时间 => 枚举最后一个人从第p本书开始抄
    // = min{ max(dp[i-1][p]), A[p]+...+A[j-1]) | 0<=p<=j } 
    int copyBooks(vector<int> &pages, int k) {
        int n = pages.size();
        if (n == 0) { return 0; }
        if (k > n) { k = n; }  // 人比书多,最多只用1人抄1本,即只需计算n个人

        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INT_MAX));
        dp[0][0] = 0;  // 0本书0个人花0时间
                       // 除此之外对所有i=0: dp[0][j>0]=INT_MAX 因为0个人无法抄完任何>1本书
        // DP计算k个人抄n本书的最少时间
        for (int i = 1; i <= k; ++i) {    // 前i个人 1<=i<=k
            dp[i][0] = 0;  // 0本书花时间0
            for (int j = 1; j <= n; ++j){ // 前j本书 1<=j<=n
                int s = 0; 
                for (int p = j; p >= 0; --p) {  // 最后1个人从第p本书开始抄到第j本书
                    if (dp[i - 1][p] != INT_MAX) {  //坑:i-1=0个人抄p>0本书花无限时间不实用与max(x,s)
                        dp[i][j] = min(dp[i][j], max(dp[i - 1][p], s));
                    }
                    if (p > 0) {  // 坑: p可为0, 即最后1个人可不抄书,此时s将不变
                        s += pages[p - 1]; // 为下一论做准备,即最后1个人从第p-1本开始抄要抄的总页数
                    }
                }
            }
        }
        return dp[k][n];
    }
};
