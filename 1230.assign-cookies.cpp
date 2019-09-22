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
 * 大饼干可满足胃口小的和胃口大的小朋友,所以更有用,在物尽其用小饼干后再用大饼干
 * 饼干小到大排,小朋友胃口小到大排,先拿小饼干喂胃口小的小朋友,不够了再拿大的喂
 * 
 * 坑: 满足一个小朋友才++index,故不用额外变量来记录满足的小朋友个数,最后访问的小朋友index+1就是
 * 坑: 循环条件不要少了&&j<=g.size()因为小朋友可能在饼干用完前就都被喂完
 */
class Solution {
public:
    /**
     * @param g: children's greed factor
     * @param s: cookie's size
     * @return: the maximum number
     */
    // Greedy 贪婪法
    // 先拿小饼干喂胃口小的小朋友,不够了再拿大的喂
    // T=O(max(mlogm,nlogn)) S=O(1)
    int findContentChildren(vector<int> &g, vector<int> &s) {
        sort(g.begin(), g.end());                           // 小朋友按胃口从小到大排序 O(nlogn)
        sort(s.begin(), s.end());                           // 饼干按从小到大排序 O(mlogm)
        int j = 0;                                          // 满足的小朋友个数
        for (int i = 0; i < s.size() && j < g.size(); ++i) {// 贪婪法:先用小饼干喂胃口小的小朋友 O(max(m,n)) // 坑:别忘j<g.size()!!!
            if (s[i] >= g[j]) { ++j; }                      // 满足一个小朋友,开始喂下个小朋友++j
                                                            // 满不满足小朋友,这个饼干都不再用++i
        }
        return j;                                           // 满足的小朋友个数
    }
};
