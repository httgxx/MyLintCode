/*
 * @lc app=lintcode id=978 lang=cpp
 *
 * [978] Basic Calculator
 *
 * https://www.lintcode.com/problem/basic-calculator/description
 *
 * lintcode
 * Medium (45.00%)
 * Total Accepted:    1314
 * Total Submissions: 2902
 * Testcase Example:  '"1 + 1"'
 *
 * Implement a basic calculator to evaluate a simple expression string.
 * 
 * The expression string may contain open `'('` and closing parentheses `')'`,
 * the plus `'+'` or minus sign `'-'`, **non-negative** integers and empty
 * spaces `' '`.
 * 
 * You may assume that the given expression is always valid.
 * Example 1
 * Input："1 + 1"
 * Output：2
 * 
 * Example 2
 * Input："(1+(4+5+2)-3)+(6+8)" 
 * Output：23
 * 
 * @Category 表达式 stack
 * @Idea 表达式 stack
 * 
 */
class Solution {
public:
    /**
     * @param s: the given expression
     * @return: the result of expression
     */
    // stack T=O(n) S=O(1)
    int calculate(string s) {
        int n = s.size(), res = 0, sign = 1;
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c >= '0') {                         // 若遇数字
                int num = 0;                        //   则连读数字并算值
                while (i < n && s[i] >= '0') {      
                    num = 10 * num + (s[i++] - '0');
                }
                res += sign * num;
                --i;                                // 坑:回退多走的最后1步
            } else if (c == '+') {                  // 若遇+
                sign = 1;                           //   则取正值
            } else if (c == '-') {                  // 若遇-
                sign = -1;                          //   则取负值
            } else if (c == '(') {                  // 若遇(
                st.push(res);                       //   则先进栈数值,后进栈+/-
                st.push(sign);
                res = 0;                            // 坑:重置数值
                sign = 1;                           // 坑:重置值的符合为正
            } else if (c == ')') {                  // 若遇)
                res *= st.top(); st.pop();          //   则先算+/-,再加数值
                res += st.top(); st.pop();
            }
        }
        return res;
    }
};
