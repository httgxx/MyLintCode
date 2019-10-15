/*
 * @lc app=lintcode id=980 lang=cpp
 *
 * [980] Basic Calculator II
 *
 * https://www.lintcode.com/problem/basic-calculator-ii/description
 *
 * lintcode
 * Medium (42.00%)
 * Total Accepted:    1236
 * Total Submissions: 2890
 * Testcase Example:  '"3+2*2"'
 *
 * Implement a basic calculator to evaluate a simple expression string.
 * 
 * The expression string contains only **non-negative** integers, `+`, `-`,
 * `*`, `/` operators and empty spaces ` `. The integer division should
 * truncate toward zero.
 * 
 * You may assume that the given expression is always valid.
 * 
 * Example 1:
 * Input: "3+2*2" Output: 7
 * 
 * Example 2:
 * Input: " 3/2 " Output: 1
 * 
 * @Category stack
 * @Idea stack
 * 
 * 
 */
class Solution {
public:
    /**
     * @param s: the given expression
     * @return: the result of expression
     */
    // stack
    int calculate(string s) {
        long res = 0, num = 0, n = s.size();
        char op = '+';
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + s[i] - '0';
            }
            if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' ||
                i == n - 1) {
                if (op == '+') { st.push(num); }    // 若+-则上一个操作数人栈
                if (op == '-') { st.push(-num); }   //   巧: 将-换成+统一操作
                if (op == '*' || op == '/') {       // 若*/则上一个操作数*/栈顶后用结果替换栈顶
                    int tmp = (op == '*') ? st.top() * num : st.top() / num;
                    st.pop();
                    st.push(tmp);
                }
                op = s[i];                          // 保存新操作符,下一轮使用
                num = 0;                            // 遇到操作符则上一个操作数已读完,须清零来读下一个操作数
            }
        }
        while (!st.empty()) {                       // 累加栈中所有数
            res += st.top();
            st.pop();
        }
        return res;
    }

    // S2: 先读操作数,再读操作符,每次遇到操作符则先用上次的操作符计算临时结果,
    //     再看如果这次操作符:只在+-时才将临时结果加入最终结果之后清零,否则临时结果继续
    // T=O(n) S=O(1)
    int calculate1(string &s) {
        long res = 0, curRes = 0, num = 0, n = s.size();
        char op = '+';
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c >= '0' && c <= '9') {                         // 先看是否数字
                num = num * 10 + c - '0';
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || // 再看是否操作符
                i == n - 1) {                                   // 或最后一个数字
                 switch (op) {                                  // 坑: switch(op)而不是switch(c)!
                    case '+': curRes += num; break;             //   即要用"上次"操作符计算临时结果
                    case '-': curRes -= num; break;
                    case '*': curRes *= num; break;
                    case '/': curRes /= num; break;
                }
                if (c == '+' || c == '-' || i == n - 1) {       // 若是+-或最后1个数字
                    res += curRes;                              // 最终结果+=加临时结果
                    curRes = 0;                                 // 清零临时结果
                }                                               // (若是*/则临时结果不清零也不加入最终结果,还继续计算)
                op = c;
                num = 0;                                        // 坑: 遇到操作符则操作数清零
            } 
        }
        return res;
    }
};
