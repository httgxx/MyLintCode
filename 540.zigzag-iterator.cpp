/*
 * @lc app=lintcode id=540 lang=cpp
 *
 * [540] Zigzag Iterator
 *
 * https://www.lintcode.com/problem/zigzag-iterator/description
 *
 * lintcode
 * Medium (56.00%)
 * Total Accepted:    3915
 * Total Submissions: 6938
 * Testcase Example:  '[1,2]\n[3,4,5,6]\n'
 *
 * Given two **1d** vectors, implement an iterator to return their elements alternately.
 * 
 * Example1
 * Input: v1 = [1, 2]
 *    and v2 = [3, 4, 5, 6]
 * Output: [1, 3, 2, 4, 5, 6]
 * Explanation: 
 * By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].
 * 
 * Example2
 * Input: v1 = [1, 1, 1, 1]
 *    and v2 = [3, 4, 5, 6]
 * Output: [1, 3, 1, 4, 1, 5, 1, 6]
 * 
 */
class ZigzagIterator {
public:
    /*
    * @param v1: A 1d vector
    * @param v2: A 1d vector
    */
    // S1: queue<cur_iter, end_iter>
    // T=O(n1+n2) S=O(1) // 耗空间
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (!v1.empty()) { q.push(make_pair(v1.begin(), v1.end())); }   // 初始放v1首
        if (!v2.empty()) { q.push(make_pair(v2.begin(), v2.end())); }   // 初始放v2首
    }
    int next() {
        auto it = q.front().first, end = q.front().second;              // 取队列首元素对应<cur_iter,end_iter>
        q.pop();                                                        // 退出队列首
        if (it + 1 != end) { q.push(make_pair(it + 1, end)); }          // 若cur_iter没到尾end_iter,push<cur_iter+1,end>
        return *it;                                                     // 返回当前队首
    }
    bool hasNext() {
        return !q.empty();
    }
private:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> q;

   /*
   // S2: 初始化时就创建好合并数组,之后顺序访问
   // T=O(n1+n2) S=O(n1+n2) // 耗空间
   ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        int n1 = v1.size(), n2 = v2.size(), n = max(n1, n2);
        for (int i = 0; i < n; ++i) {
            if (i < n1) v.push_back(v1[i]);
            if (i < n2) v.push_back(v2[i]);
        }
    }
    int next() {
        return v[i++];
    }
    bool hasNext() {
        return i < v.size();
    }
private:
    vector<int> v;
    int i = 0; */
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator solution(v1, v2);
 * while (solution.hasNext()) result.push_back(solution.next());
 * Ouptut result
 */
