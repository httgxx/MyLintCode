/*
 * @lc app=lintcode id=1219 lang=cpp
 *
 * [1219] Heaters
 *
 * https://www.lintcode.com/problem/heaters/description
 *
 * lintcode
 * Easy (38.00%)
 * Total Accepted:    1072
 * Total Submissions: 2751
 * Testcase Example:  '[1,2,3]\n[2]'
 *
 * Winter is coming! Your first job during the contest is to design a standard
 * heater with fixed warm radius to warm all the houses.
 * 
 * Now, you are given positions of houses and heaters on a horizontal line,
 * find out minimum radius of heaters so that all houses could be covered by
 * those heaters.
 * 
 * So, your input will be the positions of houses and heaters seperately, and
 * your expected output will be the minimum radius standard of heaters.
 * 
 * Example 1:
 * Input: [1,2,3],[2] Output: 1
 * Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, 
 * then all the houses can be warmed.
 * 
 * Example 2:
 * Input: [1,2,3,4],[1,4] Output: 1
 * Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard,
 * then all the houses can be warm
 * 
 * @Category BS 二分
 * @Idea 已知房子和heater位置,求heater所需的最小加热半径
 * 先按heater位置排序,再对每个房子二分找不小于该房子的首个heater位置,计算这个heater和前一个heater哪个离该房字近
 * 近的heater选来加热该房子,并用近的距离做新的加热半径更新最值
 * T=O(nlogn) S=O(1)
 * 
 */
class Solution {
public:
    /**
     * @param houses: positions of houses
     * @param heaters: positions of heaters
     * @return: the minimum radius standard of heaters
     */
    // 二分
    // 先按heater位置排序,再对每个房子二分找不小于该房子的首个heater位置,计算这个heater和前一个heater哪个离该房字近
    // 近的heater选来加热该房子,并用近的距离做新的加热半径更新最值
    // T=O(nlogn) S=O(1)
    int findRadius(vector<int> &houses, vector<int> &heaters) {
        int res = 0, n = heaters.size();
        sort(heaters.begin(), heaters.end());                               // 先按heater位置排序
        for (int house : houses) {                                          // 对每个房子
            int left = 0, right = n;
            while (left < right) {                                          // 二分查找不小于房子的首个heater的位置
                int mid = left + (right - left) / 2;
                if (heaters[mid] < house) { left = mid + 1; }
                else right = mid;
            }
            int dist1 = (right == n) ? INT_MAX : heaters[right] - house;    // 计算该heater到该房子的距离
            int dist2 = (right == 0) ? INT_MAX : house - heaters[right - 1];// 计算前一个heater到该房子的距离
            res = max(res, min(dist1, dist2));                              // 用距离近的heater且距离即为加热半径,更新最值
        }
        return res;
    }
};
