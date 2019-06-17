/*
 * @lc app=lintcode id=435 lang=cpp
 *
 * [435] Post Office Problem
 *
 * https://www.lintcode.com/problem/post-office-problem/description
 *
 * lintcode
 * Hard (27.00%)
 * Total Accepted:    1987
 * Total Submissions: 7184
 * Testcase Example:  '[1,2,3,4,5]\n2\n'
 *
 * There are `n` houses on a line. Given an array `A` and `A[i]` represents the
 * position of `i-th` house. Now you need to pick `k` position to build `k`
 * post offices.
 * 
 * What is the minimum sum distance from these `n` houses to the nearest post
 * office?
 * 
 * Example 1:
 * Input: A = [1, 2, 3, 4, 5], k = 2
 * Output: 3
 * Explanation: Build post offices on position 2 and 4.
 * Example 2:
 * Input: A = [1, 2], k = 1
 * Output: 1
 * Explanation: Build post office on position 1 or 2.
 * 
 * 可以按照每个房子最近的邮局, 把 n 个房子分成 k 段, 而我们要决定的就是这 k 段分别是多长. 为了处理方便我们先对房子的位置排序.
 * 设定 f[i][j] 表示前 j 栋房子建立 i 个邮局时的最优解. 对于这个状态我们需要决策的就是 j 之前有多少栋房子共用第 i 个邮局, 故有:
 * f[i][j] = min{f[i - 1][j - x] + sumdis[j - x][j - 1]}
 * 其中 sumdis[l][r] 表示下标范围为 [l, r] 的房子之间建立一个邮局, 这些房子与该邮局的最短距离
 * (注意f[i][j]中的j表示的第j栋房子从1计数, sumdis从0计数)
 * sumdis数组可以实现预处理出来, 具体算法与中位数的性质有关. 即对于 sumdis[l][r], 直接选择这 r - l + 1 栋房子中, 中间的那一栋建立邮局(如果是偶数栋, 中间的两栋任选一栋), 这时这些房子与邮局的距离之和是最短的.
 * 至于dp的边界: f[i][0] = 0, f[0][j] = INF, 以及 i >= j 时 f[i][j] = 0
 * 另外, 这样的状态定义可以用滚动数组优化空间.
 */
class Solution {
public:
    /**
     * @param A: an integer array
     * @param k: An integer
     * @return: an integer
     */
    int postOffice(vector<int> &A, int k) {
        int n = A.size();
        if (n == 0 || k >= n) { return 0; }
        
        sort(A.begin(), A.end());
        
        vector<vector<int>> dis(n + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; ++j) {
                int mid = (i + j) / 2;
                for (int k = i; k <= j; ++k)
                    dis[i][j] += abs(A[k - 1] - A[mid - 1]);
            }
        }

        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));  // dp[n+1][k+1]
        for (int i = 0; i <= n; ++i) {
            dp[i][1] = dis[1][i];
        }
        for (int nk = 2; nk <= k; nk++) {
            for (int i = nk; i <= n; i++) {
                dp[i][nk] = INT_MAX;
                for (int j = 0; j < i; j++) {
                    if (dp[i][nk] == INT_MAX || dp[i][nk] > dp[j][nk - 1] + dis[j + 1][i])
                        dp[i][nk] = dp[j][nk - 1] + dis[j + 1][i];
                }
            }
        }
        return dp[n][k];
    }
};
