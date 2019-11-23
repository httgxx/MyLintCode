/*
 * @lc app=lintcode id=131 lang=cpp
 *
 * [131] The Skyline Problem
 *
 * https://www.lintcode.com/problem/the-skyline-problem/description
 *
 * lintcode
 * Super (17.00%)
 * Total Accepted:    7505
 * Total Submissions: 43891
 * Testcase Example:  '[[1,3,3],[2,4,4],[5,6,1]]\n'
 *
 * Given *N* buildings in a x-axis，each building is a rectangle and can be
 * represented by a triple (start, end, height)，where start is the start
 * position on x-axis, end is the end position on x-axis and height is the
 * height of the building. Buildings may overlap if you see them from far
 * away，find the outline of them。
 * 
 * An outline can be represented by a triple, (start, end, height), where start
 * is the start position on x-axis of the outline, end is the end position on
 * x-axis and height is the height of the outline.
 * 
 * Example1:
 * Input:
 * [
 *  [1, 3, 3],
 *  [2, 4, 4],
 *  [5, 6, 1]
 * ]
 * Output:
 * [
 *  [1, 2, 3],
 *  [2, 4, 4],
 *  [5, 6, 1]
 * ]
 * Explanation:
 * The buildings are look like this in the picture. The yellow part is buildings.
 * 
 * Example2:
 * Input:
 * [
 *  [1, 4, 3],
 *  [6, 9, 5]
 * ]
 * Output:
 * [
 *  [1, 4, 3],
 *  [6, 9, 5]
 * ]
 * Explanation:
 * The buildings are look like this in the picture. The yellow part is buildings.
 */
class Solution {
public:
    /**
     * @param buildings: A list of lists of integers
     * @return: Find the outline of those buildings
     */
    vector<vector<int>> buildingOutline(vector<vector<int>> &buildings) {
        // write your code here
        vector<vector<int>> ret;
        vector<pair<int, int>> nodes;
        for (auto &building: buildings) {
            nodes.emplace_back(building[0], -building[2]); // 加入先放大的高度
            nodes.emplace_back(building[1], building[2]); // 退出先放小的高度 
        }
        
        sort(nodes.begin(), nodes.end());
        
        multiset<int> m;
        m.insert(0);
        int cur_h = 0, prev_h = 0;
        pair<int, int> prev_pt = {0, 0};
        
        for (auto &node: nodes) {
            if (node.second < 0) {
                m.insert(-node.second);                
            } else {
                m.erase(m.find(node.second));
            }
            cur_h = *m.rbegin();
            if (cur_h != prev_h) {
                if (prev_pt.second != 0) {
                    ret.push_back({prev_pt.first, node.first, prev_pt.second});
                }
                prev_pt = {node.first, cur_h};
                prev_h = cur_h;
            }
        }
        return ret;
    }
};
