/*
 * @lc app=lintcode id=669 lang=cpp
 *
 * [669] Coin Change
 *
 * https://www.lintcode.com/problem/coin-change/description
 *
 * lintcode
 * Medium (36.00%)
 * Total Accepted:    3620
 * Total Submissions: 9870
 * Testcase Example:  '[1,2,5]\n11\n'
 *
 * You are given coins of different denominations and a total amount of money
 * amount. Write a function to compute the fewest number of coins that you need
 * to make up that amount. If that amount of money cannot be made up by any
 * combination of the coins, return `-1`.
 *
 * @Category DP(按情况叠加比较型),DFS+Memo
 * @Ideas
 * S1: DP //T=O(nk) S=O(n)
 * dp[i]表示够成钱数i所需的最少硬币数目
 * 对钱数i,用每种面值<=i的硬币去更新所需最小硬币总数
 * dp[i]=min{dp[i-coins[j]]+1}|对于<i的硬币面值
 * 初始 dp[0]=0 dp[i>0]=amount+1(表示不能正好凑成)
 * 顺序 由0到amount
 * 返回 dp[amount]
 * 坑: 硬币面值从小到大排序,这样只要coins[k]>i则跳出内循环因为无法余下的面值都>i
 * 坑: 用amount+1代表INT_MAX因为有dp[x]+1的操作可能溢出
 * 坑: 最后要检查是否=amount+1来返回-1,因为有可能无法正好凑成amount
 * 
 * 实例: 面值[1,2,5] 钱数10
 * dp[0]=0 
 * i=1
 *  j=0 dp[1]=min(dp[1]=INT_MAX,dp[1-coins[0]=1-1=0]+1)=1    //1
 * i=2
 *   j=0 dp[2]=min(dp[2]=INT_MAX,dp[2-coins[0]=2-1=1]+1)=2    //1,1
 *   j=1 dp[2]=min(dp[2]=2,dp[2-coins[1]=2-2=0]+1)=1          //2
 * i=3
 *   j=0 dp[3]=min(dp[3]=INT_MAX,dp[3-coins[0]=3-1=3]+1)=3    //1,1,1
 *   j=1 dp[3]=min(dp[3]=3,dp[3-coins[1]=3-2=1]+1)=2          //2,1
 * i=4
 *   j=0 dp[4]=min(dp[4]=INT_MAX,dp[4-coins[0]=4-1=3]+1)=3    //2,1,1
 *   j=1 dp[4]=min(dp[4]=3,dp[4-coins[1]=4-2=2]+1)=2          //2,2
 * i=5
 *   j=0 dp[5]=min(dp[5]=INT_MAX,dp[5-coins[0]=5-1=4]+1)=3    //2,2,1
 *   j=1 dp[5]=min(dp[5]=3,dp[5-coins[1]=5-2=3]+1)=3          //2,1,2
 *   j=2 dp[5]=min(dp[5]=3,dp[5-coins[2]=5-5=0]+1)=1          //5
 * i=6
 *   j=0 dp[6]=min(dp[6]=INT_MAX,dp[6-coins[0]=6-1=5]+1)=2    //5,1
 *   j=1 dp[6]=min(dp[6]=2,dp[6-coins[1]=6-2=4]+1)=min(2,3)=2 //5,1
 *   j=2 dp[5]=min(dp[6]=2,dp[6-coins[2]=6-5=1]+1)=2          //1,5
 * i=7
 *   j=0 dp[7]=min(dp[7]=INT_MAX,dp[7-coins[0]=7-1=6]+1)=3    //5,1,1
 *   j=1 dp[7]=min(dp[7]=3,dp[7-coins[1]=7-2=5]+1)=min(3,2)=2 //2,5
 *   j=2 dp[7]=min(dp[7]=3,dp[7-coins[2]=7-5=2]+1)=2          //5,2
 * i=8
 *   j=0 dp[8]=min(dp[8]=INT_MAX,dp[8-coins[0]=8-1=7]+1)=3    //5,2,1
 *   j=1 dp[8]=min(dp[8]=3,dp[8-coins[1]=8-2=6]+1)=min(3,3)=3 //2,5,1
 *   j=2 dp[8]=min(dp[8]=3,dp[8-coins[2]=8-5=3]+1)=3          //5,2,1
 * i=9
 *   j=0 dp[9]=min(dp[9]=INT_MAX,dp[9-coins[0]=9-1=8]+1)=4    //1,5,2,1
 *   j=1 dp[9]=min(dp[9]=4,dp[9-coins[1]=9-2=7]+1)=min(4,3)=3 //2,5,2
 *   j=2 dp[9]=min(dp[9]=3,dp[9-coins[2]=9-5=4]+1)=min(3,3)=3 //5,2,2
 * i=10
 *   j=0 dp[10]=min(dp[10]=INT_MAX,dp[10-coins[0]=10-1=9]+1)=4//1,5,2,2
 *   j=1 dp[10]=min(dp[10]=4,dp[10-coins[1]=10-2=8]+1)=4      //2,5,2,1
 *   j=2 dp[10]=min(dp[10]=4,dp[10-coins[2]=10-5=5]+1)=2      //5,5
 * 注意并不是总是从最大面值来选能得到最少数目,组合[1,2,5]正好可以
 * 反例:[1,3,4]构成6: 6=4+1+1=>3 6=3+3=>2 最优方案并没有取最大面值4
 *
 * S2: DFS+剪枝 (amount太大会超时) T=? S=?
 * 硬币按面值由大到小排序,每次先用尽可能多个当前最大面值的硬币去凑
 * 正好凑足则更新res,但任然会依次减少最大面值硬币的数量,再用剩下的硬币面值去试
 * 直到所有面值都被用过才返回
 * // 问题:在没有试过所有面试硬币的情况下amount==0时就不去更新res么???
 */
class Solution {
public:
    /**
     * @param coins: a list of integer
     * @param amount: a total amount of money amount
     * @return: the fewest number of coins that you need to make up
     */
    // S1: DP T=O(amount*n) S=O(amount)
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);  // 坑: 用INT_MAX之后+1会溢出
                                                 // 故用不可能的值amount+1同效
        sort(coins.begin(), coins.end());  // 硬币面值按照从小到大排序
        dp[0] = 0;
        for (int i = coins[0]; i <= amount; ++i) {  // 从i=最小的面值开始
            // 用每种可用的面值(coins[k]<=i)都计算一下是否能用更少的硬币达到i
            // 坑: 因为面值已经从小到大排序,所以只要遇到硬币面值>i则终止内循环
            for (int k = 0; k < coins.size() && coins[k] <= i; // k>i终止内循环
                ++k) {
                dp[i] = min(dp[i], dp[i - coins[k]] + 1);  // 用INT_MAX溢出
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];  // 坑:有可能没法凑成
    }

    // S2: DFS+剪枝 amount太大会超时
    int coinChange2(vector<int>& coins, int amount) {
        sort(coins.rbegin(), coins.rend());  // 排序从大面值开始更快找到最小数目
        int res = INT_MAX;  // 或者res初始化成amount+1
        dfs(coins, 0, amount, 0, res);
        return (res == INT_MAX) ? -1 : res;  // 坑:有可能无法正好凑成amount
    }
    void dfs(const vector<int>& coins,
             int start, int amount, int count, int& res) {
        // 检查是否dfs已到底
        if (start == coins.size()) {
            // [问题]在没有试过所有面试硬币的情况下amount==0时我们不去更新res么???
            if (amount == 0) {  // 只有正好凑成amount才更新res
                res = min(res, count);
            }
            return;
        }
        // 剪枝: 新数目>res时停止dfs
        if (count >= res) {
            return;
        }
        // 有大到小枚举coin数目进行dfs. 特例:0面值的coin跳过否则引起除以0溢出
        for (int k = coins[start] ? amount / coins[start] : 0;
             k >= 0; --k) {
            dfs(coins, start + 1, amount - k * coins[start], count + k, res);
        }
    }
};
