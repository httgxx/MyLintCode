/*
 * @lc app=lintcode id=438 lang=cpp
 *
 * [438] Copy Books II
 *
 * https://www.lintcode.com/problem/copy-books-ii/description
 *
 * lintcode
 * Hard (25.00%)
 * Total Accepted:    1537
 * Total Submissions: 6094
 * Testcase Example:  '4\n[3,2,4]\n'
 *
 * Given `n` books and each book has the same number of pages. There are `k`
 * persons to copy these books and the `i-th` person needs `times[i]` minutes
 * to copy a book.
 * 
 * Each person can copy any number of books and they start copying at the same
 * time. What's the best strategy to assign books so that the job can be
 * finished at the earliest time? 
 * 
 * Return the shortest time.
 * Example 1:
 * Input: n = 4, times = [3, 2, 4]
 * Output: 4
 * Explanation: 
 * First person spends 3 minutes to copy 1 book.
 * Second person spends 4 minutes to copy 2 books.
 * Third person spends 4 minutes to copy 1 book.
 * 
 * Example 2:
 * Input: n = 4, times = [3, 2, 4, 5]
 * Output: 4
 * Explanation: Use the same strategy as example 1 and the forth person does nothing.
 * 
 * 可以使用二分或者动态规划解决这道题目. 
 * 不过更推荐二分答案的写法, 它更节省空间, 思路简洁, 容易编码.
 * 对于假定的时间上限tm我们可使用贪心的思想判断这k个人能否完成复印n本书的任务: 
 * 每个人都在规定时间内尽可能多地复印, 判断他们复印的总数是否不小于n即可.
 * 而时间上限tm与可否完成任务(0或1)这两个量之间具有单调性关系, 所以可以对tm进行二分查找最小的tm使得任务可以完成.
 */
class Solution {
public:
    /**
     * @param n: An integer
     * @param times: an array of integers
     * @return: an integer
     */
    int copyBooksII(int n, vector<int> &times) {
        if (n == 0) { return 0; }
        int l = 0, r = times[0] * n;
        while (l < r) {
            int mid = (l + r) / 2;
            if (ok(n, times, mid)) { r = mid; }
            else { l = mid + 1;}
        }
        return l;
    }
    bool ok(int n, vector<int> &times, int tm) {
        int num = 0;
        for (int i : times) { num += tm / i; }
        return n <= num;
    } 
};
