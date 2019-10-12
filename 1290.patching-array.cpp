/*
 * @lc app=lintcode id=1290 lang=cpp
 *
 * [1290] Patching Array
 *
 * https://www.lintcode.com/problem/patching-array/description
 *
 * lintcode
 * Hard (42.00%)
 * Total Accepted:    232
 * Total Submissions: 546
 * Testcase Example:  '[1,3]\n6'
 *
 * Given a sorted positive integer array nums and an integer n, add/patch
 * elements to the array such that any number in range `[1, n]` inclusive can
 * be formed by the sum of some elements in the array. Return the minimum
 * number of patches required.
 * 
 * Example 1:
 * nums = [1, 3], n = 6
 * Return 1.
 * Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
 * Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
 * Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
 * So we only need 1 patch.
 * 
 * Example 2:
 * nums = [1, 5, 10], n = 20
 * Return 2.
 * The two patches can be [2, 4].
 * 
 * Example 3:
 * nums = [1, 2, 2], n = 5
 * Return 0.
 * 
 * @Category
 * @Idea 
 * 每次找最小不能表示的数,看加入此数后能表示的数的范围增到多大,不够大则继续找和加,直到最大数在能表示的访问之内.
 * 注: 元素不能重复使用，否则的话只有要有1，就能组成所有的数字了
 * 
 */
class Solution {
public:
    /**
     * @param nums: an array
     * @param n: an integer
     * @return: the minimum number of patches required
     */
    // S1: 找/更新最小不能由当前访问过的数字所表示的数字miss
    // T=O(n) S=O(1)
    int minPatches(vector<int> &nums, int n) {
        long miss = 1, res = 0, i = 0;                  // 最小不能表示数miss初始为1
        while (miss <= n) {                             // 只要最大数字还没法被表示,就继续补充数
                                                        // 加入[i]后,可表示值范围=[1,miss)+[[i], miss+[i]) //=[1,miss)+[i]+[1+[i],miss+[i])
            if (i < nums.size() && nums[i] <= miss) {   // 若[i]<=miss,右边界..miss)和左边界[[i]..合并,可表示值范围变为[1, miss+[i])
                miss += nums[i++];                      //   新miss=旧miss+[i],且不需额外添数字
            } 
            else {                                      // 若[i]>miss,中间部分[miss,[i])还不能被表示
                miss += miss;                           //   加入miss,可表示值范围变为[1, miss]+[1+miss,miss+miss)=[1, miss+miss)
                ++res;                                  //   新miss=旧miss+旧miss,且额外添数字数+=1
            }
        }
        return res;
    }
};
