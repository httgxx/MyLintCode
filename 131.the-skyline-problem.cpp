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
 * 
 * @Category skyline
 * @Idea 扫描线  T=O(nlogn) S=O(n)
 * 先把每个[start,end,height]打散成[start,-h],[end,h],按x轴从小到大排,则同h的start在end前
 * 从左扫到右,若start(-h<0)则h入堆,若end(h>0)则h出堆,退出后将余下高度最大值入结果集
 * 需将拐点转换成三元组加入结果集
 */
class Solution {
public:
    /**
     * @param buildings: A list of lists of integers
     * @return: Find the outline of those buildings
     */
    // 先把每个[start,end,height]打散成[start,-h],[end,h],按x轴从小到大排,则同h的start在end前
    // 从左扫到右,若start(-h<0)则h入堆,若end(h>0)则h出堆,退出后将余下高度最大值入结果集
    // 需将拐点转换成三元组加入结果集
    // T=O(nlogn) S=O(n)
    vector<vector<int>> buildingOutline(vector<vector<int>>& buildings) {
        if(buildings.empty()) { return {}; }    // 特例:空串
        vector<vector<int>> res, xh;
        for (auto &b : buildings) {             // 每个[start,end,h]打散成[start,-h],[end,h]
            xh.push_back({b[0], -b[2]});
            xh.push_back({b[1], b[2]});
        }
        sort(xh.begin(), xh.end());             // 按x坐标从小到大排序,同高start在end前(-h<h)
        
        multiset<int> m;                        // multiset(按堆排好序,插入删除后仍有序)代替最大堆存h
        m.insert(0);                            // 巧: 加0以便将没和其他楼重叠的end也加入结果集合
        int pre = 0, cur = 0;                   // 上一高度,当前高度,都初始为0
        vector<int> pre_pt = {0, 0};            // 上一拐点[x,h]
        for (auto &a : xh) {
            if (a[1] < 0) { m.insert(-a[1]); }  // 若start,进入楼,则h入堆m
            else { m.erase(m.find(a[1])); }     // 若end,退出楼,则h出堆m
            cur = *m.rbegin();                  // 当前高度=m中最大h(尾元素)
            if (cur != pre) {                   // 若计算的当前高度!=上一高度
                if (pre_pt[1] != 0) {           // [x,当前高度]入结果集
                    res.push_back({pre_pt[0], a[0], pre_pt[1]});
                }
                pre_pt[0] = a[0];
                pre_pt[1] = cur;
                pre = cur;                      //   当前高成为新的上一高度    
            }
        }
        return res;
    }
};
