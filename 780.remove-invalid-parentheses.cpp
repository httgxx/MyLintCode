/*
 * @lc app=lintcode id=780 lang=cpp
 *
 * [780] Remove Invalid Parentheses
 *
 * https://www.lintcode.com/problem/remove-invalid-parentheses/description
 *
 * lintcode
 * Hard (37.00%)
 * Total Accepted:    2599
 * Total Submissions: 6871
 * Testcase Example:  '"()())()"'
 *
 * Remove the minimum number of invalid parentheses in order to make the input
 * string valid. Return all possible results.
 * 
 * Example:
 * Input: "(a)())()"
 * Output: ["(a)()()", "(a())()"]
 * 
 * S1: DFS 栈
 * 
 * 
 * S2: BFS 队列
 * q{{s}}, visited{{s}}, found=false
 * while(!q.empty())
 *     t=q头
 *     if(t合法) { t入res, found=true}
 *     if(found) continue
 *     for t每个字符
 *         if是(或): 去掉括号后成t',若没查过t'则t'入q和visited
 * 返回 res
 * 辅助 isValid(t): 左扫到右,逢(加逢)减,中途若cnt<0则)多非法,最后若还剩(则非法
 * 大坑:不能if(isValid(t)内部直接continue,否则会返回不是最少步骤的解法
 *      必须if(isValid(t)后found=true才continue来保证一旦合法就不再继续删()检验合法性
 */
class Solution {
public:
    /**
     * @param s: The input string
     * @return: Return all possible results
     */
    vector<string> removeInvalidParentheses(string &s) {
        vector<string> res;
        unordered_set<string> visited{{s}};
        queue<string> q{{s}};  // 初始化s入列
        bool found = false;
        while (!q.empty()) {
            string t = q.front(); q.pop();
            if (isValid(t)) {
                res.push_back(t);
                found = true;
            }
            if (found) continue;  // 坑: 不能if(isValid(t)是直接continue,否则会返回不是最少步骤的解法
            for (int i = 0; i < t.size(); ++i) {
                if (t[i] != '(' && t[i] != ')') continue;  // 坑: 跳过非()
                string str = t.substr(0, i) + t.substr(i + 1);  // 去除多余()
                if (!visited.count(str)) {  // 坑: 避免cycle
                    q.push(str);
                    visited.insert(str);
                }
            }
        }
        return res;
    }
    bool isValid(string t) {
        int cnt = 0;
        for (int i = 0; i < t.size(); ++i) {
            if (t[i] == '(') ++cnt;  // 逢(加
            else if (t[i] == ')' && --cnt < 0) return false;  // 逢)减 // 坑: 若)多了则非法
        }
        return cnt == 0;  // 坑: 最后检查有无多余(
    }
};
