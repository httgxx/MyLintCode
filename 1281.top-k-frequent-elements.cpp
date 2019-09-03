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
 * 
 * S1: map + 最大堆 // T=O(nlogn)
 * 思路: 用map统计每个val的freq,所有<freq,val>入最大堆,最后输出堆顶k次 
 * 实现:
 * 统计频率 unordered_map[val]=freq
 * 建立大堆 priority_queue<pair<int, int>> pq; 
 * 加入大堆 q.push({freq,val}); // not {val,freq}!!
 * 出大堆顶 res.push_back(pq.pop().second)  // not pop().first!!
 * 
 * 坑: 入大堆时要将map的键和值(freq)反过来存入才能按freq排序
 * 坑: 出大堆时要将pq的第二项(value)加入结果集(第一项是freq)
 * 
 * S2: map + 最小堆 // T=O(nlogK) //logK而非logN
 * 思路:
 * 1.用map统计每个val的freq
 * 2.建立维护大小为K的最小堆来保存当前的topK:
 *   2.1 if 堆没满//size<k: 直接入堆{freq,val} 
 *   2.2 else//堆满size==k:
 *       2.2.1 if 新freq<=堆顶: 跳过 //过滤掉所有<=当前第K大的
 *       2.2.2 else//freq>堆顶: 出堆再入堆 //用新的topK之一替换掉旧的第K大 //先出后入=>保持堆大小<=K
 * 3.输出堆栈中的所有数据并反向加入结果集(结果是大到小排序)
 * 实现:
 * 统计频率 unordered_map[val]=freq 
 * 创建小堆 priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>>()> pq;
 *  若最小堆已满
 *   1) 若不比堆顶大,跳过新值不入堆  if (freq <= pq.top());
 *   2) 若比堆顶大,堆顶出后新值入堆  else pq.pop(); pq.push({freq,val}) // not {val,freq}!!, must pop()
 *  若最小堆未满
 *   直接入堆: if (pq.size() != k) pq.push(({freq,val});
 * 最后反向输出小堆所有 res.push_front(pq.pop().second) // not pop().first!!, push_front!!
 * 
 * 坑: 入大堆时要将map的键和值(freq)反过来存入才能按freq排序
 * 坑: 出大堆时要将pq的第二项(value)加入结果集(第一项是freq)
 */
class Solution {
public:
    /**
     * @param nums: the given array
     * @param k: the given k
     * @return: the k most frequent elements
     */
    // S1: map + minheap 按频率堆排序,大小为K的最小堆保存topK // T=O(nlogK)
    vector<int> topKFrequent(vector<int> nums, int k) {
        unordered_map<int, int> m;
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>> pq;  //minHeap
        vector<int> res;
        for (auto num : nums) { ++m[num]; }  // 统计频率
        for (auto it : m) {
            int val = it.first, freq = it.second;
            if (pq.size() < k) { pq.push({freq, val}); }  // 堆未满,直接入堆
            else if (freq > pq.top().first) {  // 堆已满,只入堆比堆顶大的值(跳过<=的),勿忘.first!!
                pq.pop();  // 先出再入,保证堆大小<=k
                pq.push({freq, val});
            }
        }
        while (!pq.empty()) {
            res.push_back(pq.top().second);  //勿忘.second!!
            pq.pop();
        }
        return res;
    }

    // S2: map + minheap 按频率堆排序,全部入最大堆,取top // T=O(nlogK)
    vector<int> topKFrequent2(vector<int> &nums, int k) {
        unordered_map<int, int> m;
        priority_queue<pair<int, int>> pq;  //maxHeap
        vector<int> res;
        for (auto num : nums) { ++m[num]; }  // O(n) 算频率
        for (auto it : m) { pq.push({ it.second, it.first }); }  // O(nlogn) 堆排序 坑:先存it.second频率!
        for (int i = 0; i < k; ++i) {
            res.push_back(pq.top().second);  // O(k) 输出频率前k的值 坑:输出top.second值！
            pq.pop();
        }
        return res;
    }

};
