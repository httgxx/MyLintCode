/*
 * @lc app=lintcode id=541 lang=cpp
 *
 * [541] Zigzag Iterator II
 *
 * https://www.lintcode.com/problem/zigzag-iterator-ii/description
 *
 * lintcode
 * Medium (44.00%)
 * Total Accepted:    3288
 * Total Submissions: 7362
 * Testcase Example:  '[[1,2,3],[4,5,6,7],[8,9]]\n'
 *
 * Follow up [Zigzag Iterator](http://www.lintcode.com/en/problem/zigzag-iterator/ "Zigzag Iterator"):
 * What if you are given `k` 1d vectors? How well can your code be extended to such cases? 
 * The "Zigzag" order is not clearly defined and is ambiguous for `k > 2` cases. 
 *  If "Zigzag" does not look right to you, replace l"Zigzag" with "Cyclic".
 * 
 * Example1
 * Input: k = 3
 * vecs = [
 *  [1,2,3],
 *  [4,5,6,7],
 *  [8,9],
 * ]
 * Output: [1,4,8,2,5,9,3,6,7]
 * 
 * Example2
 * Input: k = 3
 * vecs = [
 *  [1,1,1]
 *  [2,2,2]
 *  [3,3,3]
 * ]
 * Output: [1,2,3,1,2,3,1,2,3]
 * 
 */
class ZigzagIterator2 {
public:
    /*
    * @param vecs: a list of 1d vectors
    */
    ZigzagIterator2(vector<vector<int>>& vecs) {
        for (auto & vec : vecs) {
            if (!vec.empty()) { q.push(make_pair(vec.begin(), vec.end())); }
        }
    }

    /*
     * @return: An integer
     */
    int next() {
        auto it = q.front().first, end = q.front().second;
        q.pop();
        if (it + 1 != end) { q.push(make_pair(it + 1, end)); }
        return *it;
    }

    /*
     * @return: True if has next
     */
    bool hasNext() {
        return !q.empty();
    }
private:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> q;
};

/**
 * Your ZigzagIterator2 object will be instantiated and called as such:
 * ZigzagIterator2 solution(vecs);
 * while (solution.hasNext()) result.push_back(solution.next());
 * Ouptut result
 */
