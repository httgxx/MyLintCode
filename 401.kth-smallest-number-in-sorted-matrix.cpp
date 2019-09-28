/*
 * @lc app=lintcode id=401 lang=cpp
 *
 * [401] Kth Smallest Number in Sorted Matrix
 *
 * https://www.lintcode.com/problem/kth-smallest-number-in-sorted-matrix/description
 *
 * lintcode
 * Medium (30.00%)
 * Total Accepted:    13976
 * Total Submissions: 46475
 * Testcase Example:  '[[1,5,7],[3,7,8],[4,8,9]]\n4\n'
 *
 * Find the *k*th smallest number in a row and column sorted matrix.
 * 
 * Each row and each column of the matrix is incremental.
 * 
 * Example 1:
 * Input:
 * [
 * [1 ,5 ,7],
 * [3 ,7 ,8],
 * [4 ,8 ,9],
 * ]
 * k = 4
 * Output: 5
 * 
 * Example 2:
 * Input:
 * [
 * [1, 2],
 * [3, 4]
 * ]
 * k = 3
 * Output: 3
 * 
 * Challenge
 * O*(klogn*) time, n is the maximum of the width and height of the matrix.
 * 
 * @Category 二分
 * @Identity
 */
class Solution {
public:
    /**
     * @param matrix: a matrix of integers
     * @param k: An integer
     * @return: the kth smallest number in the matrix
     */
    // S1: (精简代码)二分 + 从右上角开始
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back() + 1;      // [lo, hi) // 坑: +1
        while(left < right) {
            int mid = left + (right - left) / 2;
            int count = 0,  j = matrix[0].size() - 1;                   // 从右上角开始找mid是第几小
            for(int i = 0; i < matrix.size(); i++) {
                while(j >= 0 && matrix[i][j] > mid) j--;                // mid小了左移
                count += (j + 1);                                       // mid大/等于了上移
            }
            if(count < k) { left = mid + 1; }                           // 几<K,去右区找更大mid来增加'几'
            else { right = mid; }                                       // 几>=K,去左区找更小/相等mid来减少/保持'几'
        }
        return left;                                                    // 找最小/左的满足条件(第K小)的数
    }

    // S2:???? 二分 + 左下角开始  T=O((m+n)lgn) S=O(1)
    int kthSmallest1(vector<vector<int>> &matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back();
        while (left < right) {                          // T=O(max(m,n)log(max-min)))=O(klogn)
            int mid = left + (right - left) / 2;
            int cnt = search_less_equal(matrix, mid);   // 看矩阵中有几个<=mid
            if (cnt < k) { left = mid + 1; }            // 若几<K,则需更大的mid来使几变大,去右找
            else right = mid;                           // 若几>=K,则需更小的mid来使几变小,去左找,
                                                        // 当几=K时mid是候选答案,须保留,但需要找满足条件的最小mid,故rignt=mid
        }
        return left;                                    // 找最小/左的满足条件(第K小)的数
    }
    int search_less_equal(vector<vector<int>>& matrix, int target) {    // 找<=target的数的总个数
        int n = matrix.size(), i = n - 1, j = 0, res = 0;               // 从左下角开始找
        while (i >= 0 && j < n) {                                       // i=m-1~0, j=0~n-1, O(m+n)=O(max(m,n))
            if (matrix[i][j] <= target) {
                res += i + 1;                                           // 右移一位,相当于大过i+1个数
                ++j;                                                    // 小了往右变更大
            }
            else { --i; }                                               // 打了往上变更小
        }
        return res;                                                     // 找最小/左的满足条件(第K小)的数
    }

};
