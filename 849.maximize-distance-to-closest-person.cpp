/*
 * @lc app=leetcode id=849 lang=cpp
 *
 * [849] Maximize Distance to Closest Person
 *
 * https://leetcode.com/problems/maximize-distance-to-closest-person/description/
 *
 * algorithms
 * Easy (41.75%)
 * Total Accepted:    44.8K
 * Total Submissions: 107.4K
 * Testcase Example:  '[1,0,0,0,1,0,1]'
 *
 * In a row of seats, 1 represents a person sitting in that seat, and 0
 * represents that the seat is empty. 
 * 
 * There is at least one empty seat, and at least one person sitting.
 * 
 * Alex wants to sit in the seat such that the distance between him and the
 * closest person to him is maximized. 
 * 
 * Return that maximum distance to closest person.
 * 
 * Example 1:
 * Input: [1,0,0,0,1,0,1]
 * Output: 2
 * Explanation: 
 * If Alex sits in the second open seat (seats[2]), then the closest person has
 * distance 2.
 * If Alex sits in any other open seat, the closest person has distance 1.
 * Thus, the maximum distance to the closest person is 2.
 * 
 * Example 2:
 * Input: [1,0,0,0]
 * Output: 3
 * Explanation: 
 * If Alex sits in the last seat, the closest person is 3 seats away.
 * This is the maximum distance possible, so the answer is 3.
 * 
 * Note:
 * 1 <= seats.length <= 20000
 * seats contains only 0s or 1s, at least one 0, and at least one 1.
 * 
 * @Category 2ptrs
 * @Idea 双指针 
 * T=O(n) S=O(n)
 * start=连续0的起点,初始化为0(左墙),i为当前扫到的座位位置
 * 遍历seats跳过空位,当遇到被占的座位i
 *   若start=0(连续空位靠左墙),选左墙空位,距离=i-start(0)=i
 *   否则是两头有人,选中间空位,距离=(i-start+1)/2
 *   更新start=当前被占座位的下一个位置(i+1)
 * 最后检查是否选最右边靠墙位置更远
 */
class Solution {
public:
    // 双指针 T=O(n) S=O(n)
    // start=连续0的起点,初始化为0(左墙),i为当前扫到的座位位置
    // 遍历seats跳过空位,当遇到被占的座位i
    //   若start=0(连续空位靠左墙),选左墙空位,距离=i-start(0)=i
    //   否则是两头有人,选中间空位,距离=(i-start+1)/2
    //   更新start=当前被占座位的下一个位置(i+1)
    // 最后检查是否选最右边靠墙位置更远
    int maxDistToClosest(vector<int>& seats) {
        int n = seats.size(), start = 0, res = 0;
        for (int i = 0; i < n; ++i) {
            if (seats[i] != 1) { continue; }            // 跳过空位
            if (start == 0) { res = max(res, i); }      // 若空位连着左墙,选靠墙位置,和当前人的最远距离=当前人位置-左墙(0)
            else { res = max(res, (i - start + 1) / 2);}// 若空位不连左墙(连着上一个人),选当前人和上一个人的中间位置
            start = i + 1;                              // 更新起始位置为当前所选位置的下一个
        }
        res = max(res, n - start);                      // 最后检查一下是否选最右靠墙位置最远
        return res;
    }
};
