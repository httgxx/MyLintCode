/*
 * @lc app=lintcode id=394 lang=cpp
 *
 * [394] Coins in a Line
 *
 * https://www.lintcode.com/problem/coins-in-a-line/description
 *
 * lintcode
 * Medium (45.00%)
 * Total Accepted:    15014
 * Total Submissions: 32850
 * Testcase Example:  '1\n'
 *
 * There are `n` coins in a line. Two players take turns to take one or two
 * coins from right side until there are no more coins left. The player who
 * take the last coin wins.
 * 
 * Could you please decide the **first** player will win or lose?
 * If the first player wins, return `true`, otherwise return `false`.
 * 
 * Example 1:
 * Input: 1
 * Output: true
 * 
 * Example 2:
 * Input: 4
 * Output: true
 * Explanation:
 * The first player takes 1 coin at first. Then there are 3 coins left.
 * Whether the second player takes 1 coin or two, then the first player can take all coin(s) left.
 *
 * 条件:
 * 每个硬币值没关系
 * 拿走最后一枚硬币的选手获胜
 * 
 * @Category DP
 * DP // T=O(n) S=O(n) => 可降维到O(1)
 * dp[i]表示当前选手(不一定是先手!)面对第i个硬币时最后是否会赢 
 * 当前选手面对i个硬币时可取1个或2个
 * 若当前选手取1个, 则对手面对第i+1个则是否会赢=dp[i+1]
 * 若当前选手取2个, 则对手面对第i+2个则是否会赢=dp[i+2]
 * 当前选手要赢只需两种选法中至少1种让对手输,即dp[i+1]==false或dp[i+2]==false
 * dp[i] = !dp[i+1] || !dp[i+2]
 * 初始 dp[n-1]=dp[n-2]=true => 倒推出dp[0]
 * 坑 特例 n=0=>false, n=1,2=>true
 * 坑 由dp[n-1]=dp[n-2]=true倒推dp[0]
 * 
 * S2: 数学推导
 * 若可以拿1~n个则总数为(n+1)的整数m倍时一定会输,因为
 * 当m=1,即有n+1个时,不管先手取1~n中任一个数k,后手都可以取(n+1-k)一次取完使得先手输掉.
 * 当m>1,即有m*(n+1)时,不管先手先取1~n中任一个数k,后手都可以取(n+1-k)使总数少(n+1)直到剩n+1变情况1
 * 
 */
class Solution {
public:
    /**
     * @param n: An integer
     * @return: A boolean which equals to true if the first player will win
     */
    bool firstWillWin(int n) {
        if (n == 0) return false;
        if (n <= 2) return true;

        vector<bool> dp(n, false);
        dp[n - 1] = dp[n - 2] = true;
        for (int i = n - 3; i >= 0; --i) {
            dp[i] = !dp[i + 1] || !dp[i + 2];
        }

        return dp[0];
    }

    bool firstWillWin1(int n) {
	    return n % 3 != 0;
    }
};
