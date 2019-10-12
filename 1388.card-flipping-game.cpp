/*
 * @lc app=lintcode id=1388 lang=cpp
 *
 * [1388] Card Flipping Game
 *
 * https://www.lintcode.com/problem/card-flipping-game/description
 *
 * lintcode
 * Medium (68.00%)
 * Total Accepted:    149
 * Total Submissions: 223
 * Testcase Example:  '[1,2,4,4,7]\n[1,3,4,1,3]'
 *
 * On a table are N cards, with a positive integer printed on the front and
 * back of each card (possibly different).
 * 
 * We flip any number of cards, and after we choose one card. 
 * 
 * If the number X on the back of the chosen card is not on the front of any
 * card, then this number X is good.
 * 
 * What is the smallest number that is good?  If no number is good, output 0.
 * 
 * Here, fronts[i] and backs[i] represent the number on the front and back of
 * card i. 
 * 
 * A flip swaps the front and back numbers, so the value on the front is now on
 * the back and vice versa.
 * 
 * Example:
 * Input: fronts = [1,2,4,4,7], backs = [1,3,4,1,3]
 * Output: 2
 * Explanation: If we flip the second card, the fronts are [1,3,4,4,7] and the backs are [1,2,4,1,3].
 * We choose the second card, which has number 2 on the back, and it isn't on the front of any card, so 2 is good.
 * Note:
 * 1 <= fronts.length == backs.length <= 1000.
 * 1 <= fronts[i] <= 2000.
 * 1 <= backs[i] <= 2000.
 * 
 * @Category 逻辑
 * @Idea 逻辑
 * 正反都有值的牌,先可以任意翻,到达一定状态后,再指一张牌使其反面的值不在任何当前正面值中.
 * 反面值不在当前任何正面值中=>反面值也不等于同一张牌的正面值=>一定是一张正反值不同的牌.
 * 所有这种牌的正反值中求最小值即可.只需在指牌之前将所有等于这个最小值的牌面全翻到反面去.
 */
class Solution {
public:
    /**
     * @param fronts: 
     * @param backs: 
     * @return: nothing
     */
    // 找所有正反不同的牌,再找这些牌的正反值中的最小值
    // T=O(n) S=O(1)
    int flipgame(vector<int> &fronts, vector<int> &backs) {
        int res = INT_MAX, n = fronts.size();
        unordered_set<int> same;
        for (int i = 0; i < n; ++i) {                               // 找到所有正反同值的牌
            if (fronts[i] == backs[i]) { same.insert(fronts[i]); }
        }
        for (int front : fronts) {                                  // 找正反不同值的牌的正面值中最小值
            if (!same.count(front)) { res = min(res, front); }
        }
        for (int back : backs) {                                    // 找正反不同值的牌的反面值中最小值
            if (!same.count(back)) res = min(res, back);
        }
        return (res == INT_MAX) ? 0 : res;                          // 坑: 有可能都是正反同值得牌,故INT_MAX时返回0 
    }
};
