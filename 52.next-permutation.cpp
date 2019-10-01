/*
 * @lc app=lintcode id=52 lang=cpp
 *
 * [52] Next Permutation
 *
 * https://www.lintcode.com/problem/next-permutation/description
 *
 * lintcode
 * Medium (28.00%)
 * Total Accepted:    11928
 * Total Submissions: 41956
 * Testcase Example:  '[1]\n\n'
 *
 * Given a list of integers, which denote a permutation.
 * 
 * Find the next permutation in ascending order.
 * 
 * Examples:
 * [1] => [1]
 * [1,3,2,3] => [1,3,3,2]
 * [4,3,2,1] => [1,2,3,4]
 * 
 * @Category Array, Permutation
 * @Idea
 * S: T=O(n) S=O(1)
 * 下一个全排列是什么意思? 所有全排列按照从小到大排列,当前全排列的下一个全排列.若已经是最大全排列,则返回最小的全排列.
 * [1,2,3,4]=>[1,2,4,3]=>[1,3,2,4]=>[1,3,4,2]=>[1,4,2,3]=>[1,4,3,2]=>[2,1,3,4]=>...=>[4,3,2,1]=>[1,2,3,4]
 * 例如[1,4,3,2]=>[2,1,3,4]时,[1,4,3,2]中'4,3,2'是以末尾结尾的最长降序子串(无法再变大的末尾子串部分),要整个串变大
 * 且要以最小程度的变大,只能增加这个子串的前一位'1',且只能将'1'变大成后面子串中的最小数字'2',之后还需将交换后的子串
 * '4,3,1'重新按从小到大排列得到将'1'变大以后的最小排列[2,1,3,4].
 * 所以算法为:
 * 1.从右向左扫整个串,直到前一元素[i]<后一元素[i+1],即找到以末尾结尾的最长降序子串的前驱位置i //[1,4,3,2]的'1'
 * 2.从右向左扫那个最长降序子串,直到找到比字符[i]大的最小/最右边元素[j],将[i]与[j]交换 //[2,4,3,1]
 * 3.将交换后不再降序的那个子串反序使得从大到小变成从小到大,以保证得到位置i上变成[j]后的最小排列  //[2,1,3,4]
 * 
 * 考虑有重复元素的情况 [3,4,4,2,2]=>[4,2,2,3,4]
 * 首先找到需要增大的数字,即从右往左的第1个变小的数字3(须跳过与第2个4相等的第1个4继续向左找)
 * 然后找到可以替换3的数字,即从右往左的最小的比3大的数字(第2个4) 3,4,4,2,2 => 4,4,3,2,2
 * 最后反转原最长降序子串4,3,2,2 => 2,2,3,4以得到增大后的最小排列[4,2,2,3,4]
 * 
 * corner: size<2 return a
 * i=n-2; while(i>=0 && a[i]>=a[i+1])--i
 * if(i>=0)
 *     j=n-1; while(j>=0 && a[j]<=a[i])--j
 *     swap(a[i],a[j])
 * reverse(a.begin()+i+1, a.end())
 * return a
 * 
 * 坑 找最长降序子串的前驱时
 *    >=而不是>因为要跳过=
 *    一定要每次循环都检查i>=0,否则如果已经最大全排列则i=-1会[-1]导致index溢出
 * 坑 一定要i>=0 时才去替换那个前驱, 否则如果已经最大全排列则i=-1会[-1]导致index溢出
 * 坑 找替换前驱的元素时
 *    <=而不是<因为要跳过=
 *    一定要每次循环都检查j>=0,否则如果已经最大全排列则i=-1会[-1]导致index溢出
 * 坑 最后别忘记reverse替换后的最长降序子串变为升序
 */
class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers
     */
    // T=O(n) S=O(1)
    vector<int> nextPermutation(vector<int> &nums) {
        int n = nums.size();
        if (n < 2) { return nums; }  // []=>[], [x]=>[x]

        int i = n - 2;  // n>=2
        while (i >= 0 && nums[i] >= nums[i + 1]) { --i; }  // 找到最长降序子串的前驱
                                                           // 坑: >=而不是>因为要跳过=
                                                           // 坑: i>=0否则index溢出
        if (i >= 0) {  // 坑: i<0时(已是最大全排列i=-1)不能再替换[i]因为[-1]会溢出!!!
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) { --j; }  // 找到比那个前驱大的最小元素
                                                           // 坑: <=而不是<因为要跳过=
                                                           // 坑: j>=0否则index溢出
            swap(nums[i], nums[j]);
        }
        
        reverse(nums.begin() + i + 1, nums.end());  // 坑: 别忘+1因为是前驱之后的子串重排!!
        return nums;
    }
};
