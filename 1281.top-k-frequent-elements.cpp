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
 * S1: map + 最大堆 // T=O(nlogn)  //空间比bucket小 时间中等
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
 * S2: map + 最小堆 // T=O(nlogK) //logK而非logN //空间占最小 时间中等
 * 思路:
 * 1.用map统计每个val的freq
 * 2.建立维护大小为K的最小堆来保存当前的topK:
 *   2.1 if 堆没满//size<k: 直接入堆{freq,val} 
 *   2.2 else//堆满size==k:
 *       if 新freq>堆顶: 出堆再入堆 //用新的topK之一替换掉旧的第K大 //先出后入=>保持堆大小<=K
 *       // else//freq>堆顶: 跳过 //过滤掉所有<=当前第K大的
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
 * 
 * // S3: map + bucket list T=O(n) S=O(n)  //空间占最大 时间最快
 * 定义一组桶[nums.size+1][]=> 桶[i]=[所有频率为i的值]
 * 倒着访问这组桶,每次遇到非空桶则输出同中的值,如果输出了K个值则终止
 * 统计频率 unordered_map[val]=freq 
 * 建立桶   vector<vector<int>> bucket(nums.size() + 1);
 * 更新桶   bucket[freq].push_back(val);
 * 输出     for i=nums.size~0  //倒着访问桶 
 *             for j=0~bucket[i].size()-1 //正着访问桶中的值
 *                 res.push_back(bucket[i][j]); // 输出访问的值
 *                 if (res.size() == k) return res; //输出k个值则退出    
 */
class Solution {
public:
    /**
     * @param nums: the given array
     * @param k: the given k
     * @return: the k most frequent elements
     */
    // S1: map + Bucket list T=O(n) S=O(n) 
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m; 
        vector<vector<int>> bucket(nums.size() + 1);  //最后一个通bucket[size]则size+1个buckets
        vector<int> res;
        for (auto a : nums) ++m[a];  // 统计频率
        for (auto it : m) { bucket[it.second].push_back(it.first); }  // 入桶
        for (int i = nums.size(); i >= 0; --i) {  // 倒着访问桶
            for (int j = 0; j < bucket[i].size(); ++j) {  // 正着访问桶内值
                res.push_back(bucket[i][j]);  // 出桶
                if (res.size() == k) return res;
            }
        }
        return res;
    }

    // S2: map + minheap 按频率堆排序,大小为K的最小堆保存topK // T=O(nlogK)
    vector<int> topKFrequent2(vector<int> nums, int k) {
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

    // S3: map + minheap 按频率堆排序,全部入最大堆,取top // T=O(nlogK)
    vector<int> topKFrequent3(vector<int> &nums, int k) {
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
