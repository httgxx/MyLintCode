/*
 * @lc app=lintcode id=1230 lang=cpp
 *
 * [1230] Assign Cookies
 *
 * https://www.lintcode.com/problem/assign-cookies/description
 *
 * lintcode
 * Easy (44.00%)
 * Total Accepted:    429
 * Total Submissions: 955
 * Testcase Example:  '[1,2,3]\n[1,1]'
 *
 * Assume you are an awesome parent and want to give your children some
 * cookies. But, you should give each child at most one cookie. Each child $i$
 * has a greed factor $g_{i}$, which is the minimum size of a cookie that the
 * child will be content with; and each cookie $j$ has a size $s_{j}$. If
 * $s_{j} \geq g_{i}$, we can assign the cookie $j$ to the child $i$, and the
 * child $i$ will be content. Your goal is to maximize the number of your
 * content children and output the maximum number.
 * 
 * Note:
 * 1.You may assume the greed factor is always positive.
 * 2.You cannot assign more than one cookie to one child.
 * 
 * Example 1:
 * Input: [1,2,3], [1,1]
 * Output: 1
 * Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
 * And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
 * You need to output 1.
 * 
 * Example 2:
 * Input: [1,2], [1,2,3]
 * Output: 2
 * Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
 * You have 3 cookies and their sizes are big enough to gratify all of the children, 
 * You need to output 2.
 * 
 * @Category Greedy 
 * @Idea 贪婪法
 * S1: 都从小到大排列
 * 从饼干角度出发:小饼干不满足胃口小的小朋友,更不可能满足胃口大的小朋友,所以能1次判断某个饼干是否能用
 * 饼干小到大排,小朋友胃口小到大排,先拿小饼干喂胃口小的小朋友,能喂饱则饱孩子数+1且继续下个小朋友,能不能喂饱都继续下个饼干
 * 
 * 坑: 满足的小朋友个数!=已访问的孩子数,故不用额外变量记录
 * 坑: 循环条件不要少了&&j<=g.size()因为小朋友可能在饼干用完前就都被喂完
 * 
 * S2: 都从大到小排列
 * 从小朋友角度出发:大饼干不满足胃口大的小朋友,小饼干更不可能,所以能1次判断是否能喂饱某个小朋友
 * 小朋友胃口大到小排,饼干大到小排,先拿大饼干喂胃口大的小朋友,能喂饱则饱孩子数+1且继续下个饼干,能不能喂饱都继续下个小朋友
 * 
 * 坑: 满足的小朋友个数!=已访问的孩子数,得用额外变量记录计,因为会跳过喂不饱的孩子
 * 坑: 循环条件不要少了&&i<=s.size()因为饼干可能在小朋友喂完前就被用完
 */
class Solution {
public:
    /**
     * @param g: children's greed factor
     * @param s: cookie's size
     * @return: the maximum number
     */
    // Greedy 贪婪法
    // S1 从饼干角度出发:小饼干不满足胃口小的小朋友,更不可能满足胃口大的小朋友,所以能1次判断某个饼干是否能用
    // 饼干小到大排,小朋友胃口小到大排,先拿小饼干喂胃口小的小朋友,能喂饱则饱孩子数+1且继续下个小朋友,能不能喂饱都继续下个饼干
    // T=O(max(mlogm,nlogn)) S=O(1)
    int findContentChildren1(vector<int> &g, vector<int> &s) {
        sort(g.begin(), g.end());                           // 小朋友按胃口从小到大排序 O(nlogn)
        sort(s.begin(), s.end());                           // 饼干按从小到大排序 O(mlogm)
        int j = 0;                                          // 满足的小朋友个数
        for (int i = 0; i < s.size() && j < g.size(); ++i) {// 贪婪法:先用小饼干喂胃口小的小朋友 O(max(m,n)) // 坑:别忘j<g.size()!!!
            if (s[i] >= g[j]) { ++j; }                      // 若当前小朋友已饱,则用下个饼干喂下个小朋友(++j)
                                                            // 若当前小朋友不饱,则用下个饼干喂当前小朋友(j不变)
                                                            // 饱或不饱,当前饼干都不再用(++i),小饼干喂不饱就换大饼干喂
        }
        return j;                                           // 满足的小朋友个数=已访问的孩子数
    }
    // S2: 从小朋友角度出发:大饼干不满足胃口大的小朋友,小饼干更不可能,所以能1次判断是否能喂饱某个小朋友
    // 小朋友胃口大到小排,饼干大到小排,先拿大饼干喂胃口大的小朋友,能喂饱则饱孩子数+1且继续下个饼干,能不能喂饱都继续下个小朋友
    // T=O(max(mlogm,nlogn)) S=O(1)
    int findContentChildren(vector<int> &g, vector<int> &s) {
        sort(g.begin(), g.end(), greater<int>());           // 小朋友按胃口从大到小倒序排 O(nlogn)
        sort(s.begin(), s.end(), greater<int>());           // 饼干按从大到小倒序排 O(mlogm)
        int res = 0;                                        // 满足的小朋友个数
        for (int i = 0, j = 0; j < g.size() && i < s.size(); ++j) {// 贪婪法:先用大饼干喂胃口大的小朋友 O(max(m,n)) // 坑:别忘i<s.size()!!!
            if (s[i] >= g[j]) { ++i; ++res; }               // 若当前小朋友已饱,则用下个饼干(++i)喂下个小朋友，饱孩子数+1
                                                            // 若当前小朋友不饱,则用当前饼干(i不变)喂下个小朋友
                                                            // 饱或不饱,当前小朋友都不再喂(++j),大饼干喂不饱小饼干更加喂不饱
        }
        return res;                                         // 坑: 满足的小朋友个数!=已访问的孩子数,得另外统计,因为会跳过喂不饱的孩子
    }
};
