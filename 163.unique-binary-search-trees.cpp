/*
 * @lc app=lintcode id=163 lang=cpp
 *
 * [163] Unique Binary Search Trees
 *
 * https://www.lintcode.com/problem/unique-binary-search-trees/description
 *
 * lintcode
 * Medium (38.00%)
 * Total Accepted:    9053
 * Total Submissions: 23778
 * Testcase Example:  '0\n'
 *
 * Given *n*, how many structurally unique **BST**s (binary search trees) that
 * store values 1...*n*?
 * 
 * Example 1:
 * Input:n = 3, Output: 5
 * Explanation:there are a total of 5 unique BST's.
 * 1           3    3       2      1
 *  \         /    /       / \      \
 *   3      2     1       1   3      2
 *  /      /       \                  \
 * 2     1          2                  3
 * 
 * @Category DP, Catalan Number
 * @Idea 动态规划 卡特兰数
 * when n = 0: 0个数字可以组成的BST数目=1(空树算1棵)
 * => dp[0]=1
 * when n = 1: 1个数字可以组成的BST数目=cnt(左子树方案)*cnt(右子树方案)=1(0个数字可组成的BST数目)*1(0个数字可组成的BST数目)
 * 1
 * => dp[1]=1
 * when n = 2: 2个数字可以组成的BST数目=以1为根的树木方案(= 0个数字可以组成的BST数目 * 1个数字可以组成的BST数目)
 *                                   +以2为根的树木方案(= 1个数字可以组成的BST数目 * 0个数字可以组成的BST数目)
 *                                   =1*1+1*1=2
 * => dp[2]=dp[0]*dp[1](1为根的情况，则左子树只能为空，右子树可以有一个数字)
　　　　   + dp[1]*dp[0](2为根的情况，则左子树可以有一个数字，右子树只能为空)
 * 1
 *  \ 
 *   2
 *   2
 *  / 
 * 1  
 * when n = 3:cnt=2 =以1为根的树木方案(= 0个数字可以组成的BST数目 * 2个数字可以组成的BST数目 = 1*2=2)
 *                  +以2为根的树木方案(= 1个数字可以组成的BST数目 * 1个数字可以组成的BST数目 = 1*1=1)
 *                  +以3为根的树木方案(= 2个数字可以组成的BST数目 * 0个数字可以组成的BST数目 = 2*1=2)
 *                  =2+1+2=5
 * dp[3]=dp[0]*dp[2](1为根的情况，则左子树0个数字，右子树2个数字)
 *      +dp[1]*dp[1](2为根的情况，则左右子树都各1个数字)
 *     + dp[2]*dp[0](3为根的情况，则左子树2个数字，右子树0个数字)
 * 1
 *  \
 *   2
 *    \
 *     3
 * 1 
 *  \ 
 *   3
 *  /
 * 2
 *   2
 *  / \
 * 1   3
 *   3
 *  /
 * 1
 *  \
 *   2
 *     3
 *    /
 *   2
 *  /
 * 1
 * 
 * dp[0]=1
 * dp[1]=1
 * dp[2]=dp[0]*dp[1]+dp[1]*dp[0]
 * dp[3]=dp[0]*dp[2]+dp[1]*dp[1]+dp[2]*dp[0] 
 * => DP 公式
 * dp[0]=dp[1]=1
 * i>=2: dp[i]=dp[0]*dp[i-1]+dp[1]*dp[i-2]+...+dp[i-2]*dp[1]+dp[i-1]*dp[0]
 *            =sum{dp[j]dp[i-1-j]|j=0~i-1}
 * 结果=dp[n]
 * 
 */
class Solution {
public:
    /**
     * @param n: An integer
     * @return: An integer
     */
    // DP, Catalan Number 
    // dp[i]表示由i个数字组成的不同BST的个数
    // dp[i]=sum{以[0]~[i-1]每个数为根的BST方案数}
    //      =cnt(左子树0个数且右子树i-1个数//根1个) + cnt(左子树1个数且右子树i-2个数) + ... + cnt(左子树i-1个数且右子树0个数)
    //      =dp[0]*dp[i-1]+dp[1]*dp[i-2]+...+dp[i-2]*dp[1]+dp[i-1]*dp[0]
    //      =sum{dp[j]dp[i-1-j] | j=0~i-1}
    // T=O(n) S=O(n)
    int numTrees(int n) {
        vector<int> dp(n + 1);          
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] += dp[j] * dp[i - j - 1];
            }
        }
        return dp[n];
    }
};
