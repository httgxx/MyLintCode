/*
 * @lc app=lintcode id=1710 lang=cpp
 *
 * [1710] Beautiful Array
 *
 * https://www.lintcode.com/problem/beautiful-array/description
 *
 * lintcode
 * Medium (62.00%)
 * Total Accepted:    59
 * Total Submissions: 93
 * Testcase Example:  '4'
 *
 * For some fixed N, an array A is beautiful if it is a permutation of the integers 1, 2, ..., N, such that:
 * For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].
 * Given N, return any beautiful array A.  (It is guaranteed that one exists.)
 * 
 * Example 1:
 * Input: N = 4
 * Output: [1,3,2,4]
 * 
 * Example 2:
 * Input: N = 5
 * Output: [1,5,3,2,4]
 * 
 * @Category: 数学
 * @Idea 数学 奇偶性
 * 每个i<j都不存在i<k<j使A[k]*2=A[i]+A[j]
 * 若数组X是漂亮数组则有
 *   2X(每个元素乘以2)也是漂亮数组
 *   2X-1(每个元素乘以2减一)也是漂亮数组
 * 由于
 *   奇数+偶数=奇数
 *   2*[奇数或偶数]=偶数
 * 因此
 *   首先奇偶数分开成两部分,这两部分就满足这个条件,奇数部分为X,偶数部分为Y,然后
 *   对X进行拆分,将X的所有位向右移动一位,然后拆分奇偶
 *   对Y进行拆分,将Y的所有位向右移动一位,然后拆分奇偶
 */
class Solution {
public:
    /**
     * @param N: an integer
     * @return: return any beautiful array A
     */
    /* 数学 奇偶性
     * 每个i<j都不存在i<k<j使A[k]*2=A[i]+A[j]
     * 若数组X是漂亮数组则有
     *   2X(每个元素乘以2)也是漂亮数组
     *   2X-1(每个元素乘以2减一)也是漂亮数组
     * 由于
     *   奇数+偶数=奇数
     *   2*[奇数或偶数]=偶数
     * 因此
     *   首先奇偶数分开成两部分,这两部分就满足这个条件,奇数部分为X,偶数部分为Y,然后
     *   对X进行拆分,将X的所有位向右移动一位,然后拆分奇偶
     *   对Y进行拆分,将Y的所有位向右移动一位,然后拆分奇偶
     */
    map<int, vector<int>> memo;
    vector<int> beautifulArray(int N) {
        return f(N);
    }
    vector<int> f(int N){
        if(memo[N].size()) { return memo[N]; }
        vector<int> ans;
        if(N == 1) { ans.push_back(1); }
        else{
            for(int x : f((N+1)/2)) { ans.push_back(2 * x - 1); }
            for(int x : f(N/2)) { ans.push_back(2 * x); }
        }
        memo[N] = ans;
        return ans;
    }
};
