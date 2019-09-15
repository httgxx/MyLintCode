/*
 * @lc app=lintcode id=56 lang=cpp
 *
 * [56] Two Sum
 *
 * https://www.lintcode.com/problem/two-sum/description
 *
 * lintcode
 * Easy (34.00%)
 * Total Accepted:    48034
 * Total Submissions: 138699
 * Testcase Example:  '[2,7,11,15]\n9\n\n'
 *
 * Given an array of integers, find two numbers such that they add up to a
 * specific target number.
 * 
 * The function `twoSum` should return *indices* of the two numbers such that
 * they add up to the target, where index1 must be less than index2. Please
 * note that your returned answers (both index1 and index2) are zero-based.
 * 
 * Example1:
 * numbers=[2, 7, 11, 15], target=9
 * return [0, 1]
 * 
 * Example2:
 * numbers=[15, 2, 7, 11], target=9
 * return [1, 2]
 * 
 * Challenge
 * Either of the following solutions are acceptable:
 * O(n) Space, O(nlogn) Time
 * O(n) Space, O(n) Time
 * 
 * @Category 2Sum
 * @Idea T=O(n) S=O(n)
 * for i=0~n-1
 *     if(map has target-nums[i]) return {m[target-nums[i]],i} //坑 若要index升序必须把i放后面
 *     else m[nums[i]]=i
 * return {}
 */
class Solution {
public:
    /**
     * @param numbers: An array of Integer
     * @param target: target = numbers[index1] + numbers[index2]
     * @return: [index1, index2] (index1 < index2)
     */
    // T=O(n) S=O(n)
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> m;              // m[数]=位置
        for (int i = 0; i < nums.size(); ++i) {
            if (m.count(target - nums[i])) {    // 存过差值,返回差值位置
                return {m[target - nums[i]], i};// 坑:做需要index升序,i要放后面!!!
            }
            m[nums[i]] = i;                     // 没存过差值,存自己位置
        }
        return {};                              // 没找到这样的对子
    }
};
