/*
 * @lc app=lintcode id=1727 lang=cpp
 *
 * [1727] Partition Array into Disjoint Intervals
 *
 * https://www.lintcode.com/problem/partition-array-into-disjoint-intervals/description
 *
 * lintcode
 * Medium (43.00%)
 * Total Accepted:    16
 * Total Submissions: 35
 * Testcase Example:  '[5,0,3,8,6]'
 *
 * Given an array A, partition it into two (contiguous) subarrays left and right so that:
 * Every element in left is less than or equal to every element in right.
 * left and right are non-empty.
 * left has the smallest possible size.
 * Return the length of left after such a partitioning.  It is guaranteed that
 * such a partitioning exists.
 * 
 * Example 1:
 * Input: [5,0,3,8,6] Output: 3
 * Explanation: left = [5,0,3], right = [8,6]
 * 
 * Example 2:
 * Input: [1,1,1,0,6,12] Output: 4
 * Explanation: left = [1,1,1,0], right = [6,12]
 * 
 * @Category interval partition
 * @Idea 分成左右两段,左段最大<=右段最小 求左段最后一个元素
 * 
 * 
 */
class Solution {
public:
    /**
     * @param A: 
     * @return: return an integer
     */
    // 分成左右两段,左段最大<=右段最小
    // T=O(n) S=O(1)
    int partitionDisjoint(vector<int> &A) {
        int leftLast = 0, leftMax = A[0], curMax = leftMax;
        for (int i = 1; i < A.size(); ++i) {
            if (A[i] < leftMax) {           // 若发现当前比左段最大值要小,则一定得将当前包含进左段,否则违法右段<=左段
                leftLast = i;               //   扩展左段直到包含当前数字
                leftMax = curMax;           //   扩展时可能会包含进比左段最大值大的数,所以须更新左段最大=当前最大
                cout<<leftMax<<","<<i<<endl;
            }
            else {
                curMax = max(curMax, A[i]); // 若当前数字>=当前左段最大,则不用扩展左段,当前数字属于右段，但要更新当前最大
            }                            
        }
        return leftLast + 1;                // 坑:返回左段长度=左段最后数字index+1
    }
};
