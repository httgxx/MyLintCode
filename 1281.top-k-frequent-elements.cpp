/*
 * @lc app=lintcode id=1281 lang=cpp
 *
 * [1281] Top K Frequent Elements
 *
 * https://www.lintcode.com/problem/top-k-frequent-elements/description
 *
 * lintcode
 * Medium (73.00%)
 * Total Accepted:    310
 * Total Submissions: 420
 * Testcase Example:  '[1,1,1,2,2,3]\n2'
 *
 * Given a non-empty array of integers, return the **k** most frequent elements.
 * Assume k is always valid
 * 
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 * 
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 * 
 * Require T=O(nlogn)
 * S1: map[val]=freq => add each <freq,val> to maxHeap => pop k times into res
 * 坑: 加入maxHeap时要将map的键和值(freq)反过来才能按freq进行堆排序
 *     maxHeap.push({mapItor.second, mapItor.first})  //.而不是->
 * 坑: 出maxHeap时要将原值加入结果集 pq.top().second 而不是.first(freq)
 * S2: 
 * 
 */
class Solution {
public:
    /**
     * @param nums: the given array
     * @param k: the given k
     * @return: the k most frequent elements
     */
    // S1: map + maxheap T=O(nlogn)
    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> m;
        priority_queue<pair<int, int>> pq;  //maxHeap
        vector<int> res;
        
        for (auto num : nums) { ++m[num]; }  // O(n) count frequency
        for (auto it : m) { pq.push({ it.second, it.first }); }  // O(nlogn) 坑:先存it.second频率!
        for (int i = 0; i < k; ++i) {
            res.push_back(pq.top().second);  // O(k) output top k values
            pq.pop();
        }
        return res;
    }
};
