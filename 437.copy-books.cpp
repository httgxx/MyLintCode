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
 * @Categories DP (划分比较型) or 二分
 * @Idea 
 * S1: DP T=O(k*n*n) S=O(n*k) => 滚动数组降维 => O(n)
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
 * 大坑: 只有1个人时每本书都得抄,所以直接付成当前sumPages,否则用INT_MAX缺省值计算会出错
 * 
 * S2: 二分法 T=O(n*log(sumPages))
 * 在max(pages)~sum(pages)之间二分,每次mid用贪心法从左到右扫描所有书看需要多少人才能抄完
 * 若需要<=k个人,说明大家花的时间可能可以再少一些,去左半边区间
 * 若需要>k个人,则说明人数不够需要提高工作量,去右半边区间
 * 每次检查若按给定最大个人工作量,能否由<=k个人抄完所有书 => T=O(n)
 * 二分次数 log(sumPages-maxPages)
 * 总时间复杂度 T= O(n*log(sumPages))
 * 
 * S3: T=O(nk)
 * https://massivealgorithms.blogspot.com/2015/11/copy-books-walking-dad.html
 *  
 */
class Solution {
public:
    /**
     * @param pages: an array of integers
     * @param k: An integer
     * @return: an integer
     */
    // S1: DP: T=O(k*n*n) S=O(k*n)
    // n本书划分成<=k段使得各段书总页数的最大值最小 => 枚举最后一段起点p
    // dp[i][j]表示前i本书由j个人来抄所需的最少时间 => 枚举最后一个人从第p本书开始抄
    // = min(dp[i][j], max(dp[p][j-1]), A[p]+...+A[i-1]) | 0<=p<=i } 
    int copyBooks(vector<int> &pages, int k) {
        int n = pages.size();
        if (n == 0) { return 0; }
        if (k > n) { k = n; }  // 人比书多,最多只用1人抄1本,即只需计算n个人

        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX));  // n本书 k个人
        for (int j = 0; j <= k; ++j) { dp[0][j] = 0; } // 0本书不花时间

        // DP计算n本书k个人抄需要的最少时间
        // 对i=0已经初始化dp[0][j]=0
        for (int i = 1; i <= n; ++i) { // i本书
            // 对j=0已初始化dp[0][0]=0, dp[i>0][0]=INT_MAX因为0个人抄不完>0本书
            for (int j = 1; j <= k; ++j){ // j个人
                int sum = 0;
                for (int p = i; p >= 0; --p) {  // 最后1个人从第p本书开始抄到第i本书
                    if (j == 1) { // 坑: 只1个人时所有书都抄故直接=sum,否则用INT_MAX缺省值计算会出错
                        dp[i][j] = sum;
                    }
                    else {
                        dp[i][j] = min(dp[i][j], max(dp[p][j - 1], sum));
                    }
                    if (p > 0) {  // 坑: p可为0, 即最后1个人可不抄书,此时s将不变
                        sum += pages[p - 1]; // 为下一轮做准备,即最后1个人从第p-1本开始抄要抄的总页数
                    }
                }
            }
        }
        return dp[n][k];
    }

    // S2: 二分法来找能由<=k个人抄完所有书的最大个人工作量的最小值
    int copyBooks2(vector<int> &pages, int k) {
        int n = pages.size();
        if (n == 0) { return 0; }
        
        // 计算抄一本书的最大工作量, 以及抄所有书的总工作量 T=O(n)
        int maxPage = 0, sum = 0;
        for (int i = 0; i < n; ++i) {
            maxPage = max(maxPage, pages[i]);
            sum += pages[i];
        }
        
        // 在[maxPages,sum]二分查找能完成任务的个人最大工作量的最小值 T=O(n*log(sum-maxPages))
        int left = maxPage, right = sum;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (canComplete(pages, mid, k)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        if (canComplete(pages, left, k)) return left;
        return right;
    }

    // 检查若按给定最大个人工作量,能否由<=k个人抄完所有书 T=O(n) 
    bool canComplete(vector<int> &pages, int perCopierPageLimit, int maxCopierCnt) {
        int copierCnt = 1, sum = 0, bookCnt = pages.size();
        for (int i = 0; i < bookCnt; ++i) {  // 贪心法: 每人在个人最大工作量内抄尽可能多的书
            if (pages[i] > perCopierPageLimit) return false;
            if (pages[i] + sum > perCopierPageLimit) {  // 超过个人最大工作量, 需要加人
                copierCnt++;
                sum = pages[i];
            } else {
                sum += pages[i];
            }
            if (copierCnt > maxCopierCnt) { return false; }
        }
        return true;
    }
};
