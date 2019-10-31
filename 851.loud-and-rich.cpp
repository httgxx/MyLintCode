/*
 * @lc app=leetcode id=851 lang=cpp
 *
 * [851] Loud and Rich
 *
 * https://leetcode.com/problems/loud-and-rich/description/
 *
 * algorithms
 * Medium (49.10%)
 * Total Accepted:    9.7K
 * Total Submissions: 19.7K
 * Testcase Example:  '[[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]]\n[3,2,5,4,6,1,7,0]'
 *
 * In a group of N people (labelled 0, 1, 2, ..., N-1), each person has 
 * different amounts of money, and different levels of quietness.
 * For convenience, we'll call the person with label x, simply "person x".
 * We'll say that richer[i] = [x, y] if person x definitely has more money than
 * person y.  Note that richer may only be a subset of valid observations.
 * Also, we'll say quiet[x] = q if person x has quietness q.
 * 
 * Now, return answer, where answer[x] = y if y is the least quiet person (that
 * is, the person y with the smallest value of quiet[y]), among all people who
 * definitely have equal to or more money than person x.
 * 
 * Example 1:
 * Input: richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet=[3,2,5,4,6,1,7,0]
 * Output: [5,5,2,5,4,5,6,7]
 * Explanation: 
 * answer[0] = 5. Person 5 has more money than 3, which has more money than 1, which has more
 * money than 0. The only person who is quieter (has lower quiet[x]) is person 7, but
 * it isn't clear if they have more money than person 0.
 * answer[7] = 7. Among all people that definitely have equal to or more money than person 7
 * (which could be persons 3, 4, 5, 6, or 7), the person who is the quietest(has lower quiet[x])
 * is person 7.
 * The other answers can be filled out with similar reasoning.
 * Note:
 * 1 <= quiet.length = N <= 500
 * 0 <= quiet[i] < N, all quiet[i] are different.
 * 0 <= richer.length <= N * (N-1) / 2
 * 0 <= richer[i][j] < N
 * richer[i][0] != richer[i][1]
 * richer[i]'s are all different.
 * The observations in richer are all logically consistent.
 * 
 * @Category 递归 建立连接表?排序?
 * @Idea 对每个人返回最安静且不比其穷的人(可以是自己)的index //题目注明没有相同富的人
 * 若没人比人[i]富裕,为其返回i
 * 若没人比人[i]安静,为其返回i
 * 否则在不比其穷的人中找最安静的返回index
 * 
 */
class Solution {
public:
    // 建立连接表,排序,递归
    // T=O() S=O()
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        vector<int> res(quiet.size(), -1);                                  // 初始结果集:都是-1表明都没找到res
        unordered_map<int, vector<int>> richers;                            // 建立连接表:{idx=>[所有比其富的人的idx集合]}
        for (auto a : richer) { richers[a[1]].push_back(a[0]); }
        for (int i = 0; i < quiet.size(); ++i) {                            // 访问对每个人i
            helper(richers, quiet, i, res);                                 //   递归找从i开始不比i穷的最安静的人res
        }
        return res;
    }
    int helper(unordered_map<int, vector<int>>& richers,                    // 递归找从i开始不比i穷的最安静的人res
               vector<int>& quiet, int i, vector<int>& res) {
        if (res[i] > 0) { return res[i]; }                                  // 人i以前处理过,直接返回答案
        res[i] = i;                                                         // 人i以前没处理过,初始化为自身i
        for (int j : richers[i]) {
            if (quiet[res[i]] > quiet[helper(richers, quiet, j, res)]) {    // 对每个比i富的人j,找不比j穷的最安静的人x(递归)
                res[i] = res[j];                                            // 若x比i的当前res更安静,则将i的res设为x
            }
        }
        return res[i];                                                      // 返回最安静的res[i]
    }
};
