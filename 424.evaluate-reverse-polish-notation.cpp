/*
 * @lc app=lintcode id=424 lang=cpp
 *
 * [424] Evaluate Reverse Polish Notation
 *
 * https://www.lintcode.com/problem/evaluate-reverse-polish-notation/description
 *
 * lintcode
 * Medium (29.00%)
 * Total Accepted:    6941
 * Total Submissions: 23213
 * Testcase Example:  '["2", "1", "+", "3", "*"]'
 *
 * Evaluate the value of an arithmetic expression in [Reverse Polish
 * Notation](http://en.wikipedia.org/wiki/Reverse_Polish_notation).
 * 
 * Valid operators are `+`, `-`, `*`, `/`. Each operand may be an **integer**
 * or another expression.
 * 
 * Example 1:
 * Input: ["2", "1", "+", "3", "*"] 
 * Output: 9
 * Explanation: ["2", "1", "+", "3", "*"] -> (2 + 1) * 3 -> 9
 * 
 * Example 2:
 * Input: ["4", "13", "5", "/", "+"]
 * Output: 6
 * Explanation: ["4", "13", "5", "/", "+"] -> 4 + 13 / 5 -> 6
 * 
 * @Category Polish Notation
 * @Idea stack
 */
class Solution {
public:
    /**
     * @param tokens: The Reverse Polish Notation
     * @return: the value
     */
    // Stack
    // T=O(n) S=O(n)
    int evalRPN(vector<string> &tokens) {
        stack<int> s;
        for (auto a : tokens) {
            if (a == "+" || a == "-" || a == "*" || a == "/") {
                if (s.size() < 2) { break; }
                int t = s.top(); s.pop();       // 操作数已经入栈,出栈
                int k = s.top(); s.pop();
                if (a == "+") { k += t; }       // 操作符计算后结果入栈
                else if (a == "-") { k -= t; }
                else if (a == "*") { k *= t; }
                else if (a == "/") { k /= t; }
                s.push(k);
            }
            else { s.push(stoi(a)); }           // 操作数直接入栈
        }
        return s.top();
    }
};
