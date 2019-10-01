/*
 * @lc app=lintcode id=617 lang=cpp
 *
 * [617] Maximum Average Subarray II
 *
 * https://www.lintcode.com/problem/maximum-average-subarray-ii/description
 *
 * lintcode
 * Medium (24.00%)
 * Total Accepted:    8226
 * Total Submissions: 34176
 * Testcase Example:  '[1,12,-5,-6,50,3]\n3\n'
 *
 * Given an array with positive and negative numbers, find the `maximum average
 * subarray` which length should be greater or equal to given length `k`.
 * 
 * Example 1:
 * Input:[1,12,-5,-6,50,3] 3
 * Output: 15.667
 * Explanation: (-6 + 50 + 3) / 3 = 15.667
 * 
 * Example 2:
 * Input:[5] 1
 * Output:5.000
 * 
 * @Category 二分法
 * @Idea
 * T=O(nlog(max + min))，n=nums的长度，max/min是nums中最大/小值
 * 所求的最大平均值一定介于原数组的最大值和最小值之间，所以目标是用二分法来快速在最大最小值间定位最大平均值
 * 初始化left=数组最小值,right=数组最大值,mid=left和right的中间值,难点就在于如何得到mid和要求的最大平均值之间的大小关系,从而判断二分的方向
 * 若已算出最大平均值maxAvg则对于任意一个长度>=k的数组，如果每个数都减去maxAvg则得到的累加差值一定<=0
 * 所以通过left和right值算出来的mid,可看作是maxAvg的一个candidate.
 * 所以让数组中的每一个数字都减去mid,然后算差值的累加和,一旦发现累加和>0则说明mid比maxAvg小,去右区继续找更大的mid
 * 具体步骤：
 * 1.每次进入循环时(循环条件是(right-left>1e-6误差),建立前缀和数组prefixSums,然后求出原数组中最小值赋给left,最大值赋给right
 * 2.算出mid,prefixSumMin初始为0,maxSum初始为INT_MIN.
 *   然后遍历数组,先更新prefixSums=各项-mid的差值累加
 *   目标是找长度>=k的子数组的平均值>mid,由于每个数-mid,则转换为找长度>=k的子数组的差累积值>0,转变成"最大>k的sumrange要<0"
 *   如果确实小于0，则end = mid，否则start = mid。
 * 
 */
class Solution {
public:
    /**
     * @param nums: an array with positive and negative numbers
     * @param k: an integer
     * @return: the maximum average
     */
    // 二分法 T=O(nlog(max + min)) S=O(n)
    double maxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double left = INT_MAX, right = INT_MIN;
        for (int i = 0; i < n; i++) {
            left = min(left, (double)nums[i]);
            right = max(right, (double)nums[i]);
        }
        vector<double> sumNums(n + 1);
        sumNums[0] = 0;
        while (right - left > 1e-6) {
            double mid = (left + right) / 2;
            for (int i = 0; i < n; i++) {
                sumNums[i + 1] = sumNums[i] + nums[i] - mid;
            }
            double preMin = 0;
            double sumMax = INT_MIN;
            for (int i = k; i <= n; i++) {
                sumMax = max(sumMax, sumNums[i] - preMin);
                preMin = min(preMin, sumNums[i - k + 1]);
            }
            if (sumMax >= 0) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
        return left;
    }
};
