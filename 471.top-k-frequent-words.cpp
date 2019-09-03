/*
 * @lc app=lintcode id=471 lang=cpp
 *
 * [471] Top K Frequent Words
 *
 * https://www.lintcode.com/problem/top-k-frequent-words/description
 *
 * lintcode
 * Medium (26.00%)
 * Total Accepted:    8700
 * Total Submissions: 32934
 * Testcase Example:  '["yes","lint","code","yes","code","baby","you","baby","chrome","safari","lint","code","body","lint","code"]\n3\n'
 *
 * Given a list of words and an integer k, return the top k frequent words in
 * the list.
 * 
 * S1: map+minHeap // T=O(nlogk) S=O(n)
 * 用map统计频率
 * 加入minHeap(自定义比较器 freq降序 word升序)
 * 保持堆大小不超过k, 超过则pop堆顶
 * 最后输出堆内所有元素,因为用最小堆所以会从小到大输出,需要反序输出结果数组(从后往前写)
 * 坑: 在结果数组从后往前
 */
class Solution {
public:
    /**
     * @param words: an array of string
     * @param k: An integer
     * @return: an array of string
     */
    // S1: map + maxHeap // T=O(nlogk) S=O(n)
    vector<string> topKFrequentWords(vector<string> &words, int k) {
        vector<string> res(k);  // !!!先初始化大小之后才能反向写入
        unordered_map<string, int> freq;
        auto cmp = [](pair<string, int>& a, pair<string, int>& b) {  // 自定义比较器:freq降序,word升序
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        }; // 勿忘";"!!!
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp) > q(cmp);
        for (auto word : words) ++freq[word];  // 统计频率
        for (auto f : freq) {
            q.push(f);
            if (q.size() > k) q.pop(); // 保持大小为k的最小堆
        }
        for (int i = res.size() - 1; i >= 0; --i) {  // 用的是最小堆,所以是从小到达输出,需要从数组尾往前赋值
            res[i] = q.top().first; q.pop();
        }
        return res;
    }
};
