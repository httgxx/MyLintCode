/*
 * @lc app=lintcode id=396 lang=cpp
 *
 * [396] Coins in a Line III
 *
 * https://www.lintcode.com/problem/coins-in-a-line-iii/description
 *
 * lintcode
 * Hard (39.00%)
 * Total Accepted:    6724
 * Total Submissions: 16958
 * Testcase Example:  '[3,2,2]'
 *
 * There are `n` coins in a line, and value of `i-th` coin is `values[i]`. 
 * 
 * Two players take turns to take a coin from one of the ends of the line until
 * there are no more coins left. The player with the larger amount of money
 * wins.
 * 
 * Could you please decide **the first player** will win or lose?
 * 
 * Example 1:
 * Input: [3, 2, 2]
 * Output: true
 * Explanation: The first player takes 3 at first. Then they both take 2.
 * 
 * Example 2:
 * Input: [1, 20, 4]
 * Output: false
 * Explanation: The second player will take 20 whether the first player take 1 or 4.
 * 
 * 与Coins in a Line II 的区别
 * 只能拿1个硬币但是每次可以从最左边或最右边取
 * 
 * @Category DP(输赢比较型)
 * S1: DP // T=O(n^2) S=O(n^2)=>降维O(n)
 * dp[i,j]表示面对硬币区间[i,j]的当前选手最后比对手多的硬币值 
 * = 当前选手这一轮取的硬币值 + 下一轮开始当前选手比对手最后多的硬币值
 * = 当前选手这一轮取的硬币值 - 下一轮开始对手比当前选手最后多的硬币值
 * = 2种选择取最大:
 *   若当前选手取[i]: dp[i][j] = a[i] - dp[i+1][j] 
 *   若当前选手选[j]: dp[i][j] = a[j] - dp[i][j-1]
 * dp[i][j] = max(a[i] - dp[i+1][j], a[j] - dp[i][j-1])  
 * 
 * 初始
 * for i=0~n-1  // 初始化长度为1的区间
 *   dp[i][i] = a[i];
 * for i=0~n-2  // 初始化长度为2的区间
 *   dp[i][i+1] = a[i]>a[i+1] ? a[i]-a[i+1] : a[i+1]-a[i]; 
 * 顺序
*  for len = 3 ~ n-2  // 计算长度>2的区间
 *    for i = 0 ~ n-len  // j=i+len-1 <= n-1 => i <= n-len
 *        get_i = a[i] - dp[i+1][j]
 *        get_j = a[j] - dp[i][j-1]
 *        dp[i][j] = max(get_i, get_j)  
 * 返回
 * dp[0][n-1] > 0
 * 
 * 坑 区间型须从小区间到大区间计算
 * 
 * 
 * S2: DP // T=O(n^2) S=O(n^2)
 * dp[i,j]: 面对第i到j个硬币的选手最后能取得最大硬币总值
 * 若当前选手取[i],剩下硬币区间[i+1,j]
 *   若对手取[i+1],之后当前选手可最大得到dp(i+2,j)
 *   若对手取[j],之后当前选手可最大得到dp(i+1,j-1)
 *   => 当前选手能拿最大值为 a[i] + min(dp(i+1,j-1), dp(i+2,j))
 * 若当前选手取[j],剩下硬币区间[i,j-1]
 *   若对手取[i],之后当前选手可最大得到dp(i+1,j-1)
 *   若对手取[j-1],之后当前选手可最大得到dp(i,j-2)
 *   => 当前选手能拿最大值为 a[j] + min(dp(i+1,j-1),dp(i,j-2))
 * 当前选手选两种选择下最大值
 * => dp[i][j]= max(a[i] + min(dp(i+1,j-1), dp(i+2,j)), a[j] + min(dp(i+1,j-1),dp(i,j-2)))
 * 
 * 初始
 * for i=0~n-1
 *   dp[i][i] = a[i];  // 只有1个硬币时当前选手取的硬币价值a[i]
 * for i=0~n-2
 *   dp[i][i+1] = max(a[i], a[i+1]);  // 只有2个硬币时当前选手取的硬币价值选前后大的一个
 * 顺序
 * for len = 3 ~ n  // 按区间大小由小到大
 *    for i = 0 ~ n - len  // 确定区间起点   i
 *       j = i + len - 1;
 *       int get_i = a[i] - min(dp[i + 1][j - 1], dp[i + 2][j]);
 *       int get_j = a[j] - min(dp[i][j - 2], dp[i + 1][j - 1]);
 *       dp[i][j] = max(get_i, get_j)
 * 返回
 *    dp[0][n-1] > sum[i,j]/2
 */
class Solution {
public:
    /**
     * @param values: a vector of integers
     * @return: a boolean which equals to true if the first player will win
     */
    bool firstWillWin(vector<int> &values) {
        int n = values.size();
        if (n == 0) { return false; }
        if (n <= 2) { return true; }

        vector<vector<int> > dp(n, vector<int>(n, 0) );
        for (int i = 0; i < n; i++) {  // 初始化长度为1的区间对应的值
            dp[i][i] = values[i];
        }
        /*for (int i = 0; i < n - 1; i++) {  // 初始化长度为1的区间对应的值
            dp[i][i + 1] = max(values[i], values[i + 1]) - min(values[i], values[i + 1]);
        }*/ // 已经包含在下面的循环计算种

        for (int len = 2; len <= n; len++) {  // 计算长度>1的区间对应的值
            for (int i = 0; i <= n - len; i++) {  // j=i+len-1 <= n-1 => i <=n-len
                int j = i + len - 1;
                int get_i = values[i] - dp[i + 1][j];
                int get_j = values[j] - dp[i][j - 1];
                dp[i][j] = max(get_i, get_j);
            }
        }

        return dp[0][n - 1] > 0;
    }

    bool firstWillWin1(vector<int> &values) {
        int n = values.size();
        if (n == 0) { return false; }  // 题目要求返回啥？
        if (n <= 2) { return true; }

        int sum = 0;
        vector<vector<int> > dp(n, vector<int>(n, 0) );
        for (int i = 0; i < n; i++) {  // 初始化长度为1的区间对应的值
            dp[i][i] = values[i];
            sum += values[i];
        }
        for (int i = 0; i < n - 1; i++) {  // 初始化长度为2的区间对应的值
            dp[i][i + 1] = max(values[i], values[i + 1]);
        }
        for (int len = 3; len <= n; len++) {  // 计算长度>2的区间的值
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                int get_i = values[i] + min(dp[i + 1][j - 1], dp[i + 2][j]);
                int get_j = values[j] + min(dp[i][j - 2], dp[i + 1][j - 1]);
                dp[i][j] = max(get_i, get_j);
            }
        }

        return dp[0][n - 1]  * 2 > sum;
    }
};
