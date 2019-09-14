/*
 * @lc app=leetcode id=854 lang=cpp
 *
 * [854] K-Similar Strings
 *
 * https://leetcode.com/problems/k-similar-strings/description/
 *
 * algorithms
 * Hard (33.27%)
 * Total Accepted:    9.4K
 * Total Submissions: 26.7K
 * Testcase Example:  '"ab"\n"ba"'
 *
 * Strings A and B are K-similar (for some non-negative integer K) if we can
 * swap the positions of two letters in A exactly K times so that the resulting
 * string equals B.
 * 
 * Given two anagrams A and B, return the smallest K for which A and B are
 * K-similar.
 * 
 * Example 1:
 * Input: A = "ab", B = "ba"
 * Output: 1
 * 
 * Example 2:
 * Input: A = "abc", B = "bca"
 * Output: 2
 * 
 * Example 3:
 * Input: A = "abac", B = "baca"
 * Output: 2
 * 
 * Example 4:
 * Input: A = "aabc", B = "abca"
 * Output: 2
 * 
 * Note:
 * 1 <= A.length == B.length <= 20
 * A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd',
 * 'e', 'f'}
 * 
 * 
 */
class Solution {
public:
    // BFS + 回溯 T=O(n) S=O(n)
    int kSimilarity(string A, string B) {
        int res = 0, n = A.size();
        queue<string> q{{A}};
        unordered_set<string> visited{{A}};
        while (!q.empty()) {
            for (int k = q.size(); k > 0; --k) {
                string cur = q.front(); q.pop();
                if (cur == B) return res;                           // 匹配完全则返回
                int i = 0;
                while (i < n && cur[i] == B[i]) ++i;                // 找第1个Ai!=Bi
                for (int j = i + 1; j < n; ++j) {                   // 从i+1开始找j使Aj=Bi且Ai=Bj
                    if (cur[j] != B[i] || cur[j] == B[j]) continue; // 跳过Aj!=Bi,跳过Aj==Bj(Bj!=Bi故也有Aj!=Bi) 
                    //等同 if(cur[j] == B[i] && cur[j] != B[j]){...}
                    swap(cur[i], cur[j]);                           // 交换
                    if (!visited.count(cur)) {                      // 记录以防止重复访问
                        visited.insert(cur);
                        q.push(cur);                                // 入队到下一层继续匹配交换
                    }
                    swap(cur[i], cur[j]);                           // 回溯
                }
            }
            ++res;
        }
        return -1; 
    }
};
