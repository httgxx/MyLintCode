/*
 * @lc app=lintcode id=114 lang=cpp
 *
 * [114] Unique Paths
 *
 * https://www.lintcode.com/problem/unique-paths/description
 *
 * lintcode
 * Easy (43.00%)
 * Total Accepted:    23429
 * Total Submissions: 53644
 * Testcase Example:  '1\n3'
 *
 * A robot is located at the top-left corner of a *m* x *n* grid.
 * The robot can only move either down or right at any point in time. The robot
 * is trying to reach the bottom-right corner of the grid.
 * 
 * How many possible unique paths are there?
 *
 * @Category DP(前构型),Combination
 * @Ideas
 * S1: DP T=O(mn) S=O(min(m,n))
 * 1维 只存当前行的每列 (或只存当前列的每行)
 * // 优化 以m和n中小的那个大小来存 大的那个做外循环
 * 新值=旧值/上一行当前列(左上角到上邻居的走法)+当前行前一列(左上角到到左邻居的走法)
 * dp[j]=从左上角到当前行的第j列有多少种走法
 * dp[j] += dp[j-1] //+=而不是=
 * 初始 all dp[i]=1
 * 顺序 上到下i=1->m-1,左到右j=1->n-1 
 * 返回 dp[n-1]
 * 坑: dp[j] += dp[j-1] +=而不是=
 * 坑: 初始化所有dp[i]=1, 且之后i和j从1而不是0开始循环
 * 
 * S2: DP T=O(mn) S=O(mn)
 * 2维 dp[i][j]=从左上角到第i行第j列有多少种走法
 * =到上邻居的走法+到左邻居的走法
 * =dp[i-1][j]+dp[i][j-1]
 * 初始 dp[0][j]=dp[i][0]=1 //i=0~m-1,j=0~n-1
 * 顺序 上到下i=0->m-1,左到右j=0->n-1 (也可以左到右,上到下)
 * 返回 dp[m-1][n-1]
 * 
 * S3: Combination T=O(min(m,n)) S=O(1)
 * 总共走m-1+n-1=m+n-2步 要么向下 要么向右 走法就是从m+n-2步中选取min(m,n)-1步的方法
 * 即求组和数C(m+n-2,min(m,n)-1)
 * // 排列公式P(n,k)=n*(n-1)*...*(n-k+1)
 * // 组和公式C(n,k)=P(n,k)/k!(无序)
 * // 坑: 要用double计算阶乘 现在已经通不过测试了 不够大？？
 * 
 * BF: T=O(?) S=O(stack?)
 * 递归 count(row,col) = count(row-1,col)+cont(row,col-1) 有重复计算
 */
class Solution {
public:
    /**
     * @param m: positive integer (1 <= m <= 100)
     * @param n: positive integer (1 <= n <= 100)
     * @return: An integer
     */
    int uniquePaths(int m, int n) {  // 降维 + min优化
        if (m < n) { return uniquePaths(n, m); }  // 优化:按min的大小存dp值

        // n <= m, 小的那个作为dp[]的大小,优化空间
        vector<int> dp(n, 1);  // 第1行初始:左上角到第1行每格都只有1种走法
        for (int i = 1; i < m; ++i) {  // 坑:第1行已赋值,从第2行开始
            for (int j = 1; j < n; ++j) {  // 第1列都是1,从第2列开始
                dp[j] += dp[j - 1];
            }
        }
        return dp[n-1];
    }

    int uniquePaths1(int m, int n) {  // 2维
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];
    }

    int uniquePaths2(int m, int n) {  // 组合
        int small = m < n ? m - 1 : n - 1;  // 优化:C(m+n-2,min(m-1,n-1))
        double num = 1, denom = 1;  // 坑:必须用double计算阶乘
        for (int i = 1; i <= small; ++i) {  // k=1~min(m-1,n-1)
            num *= m + n - 2 - small;  // 排列(m+n-2-1)*...*(m+n-2-k)
            denom *= i;  // 无序所以要除以k!
        }
        return static_cast<int>(num / denom);  // 坑:必须转换回int
    }
};
