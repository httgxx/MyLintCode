/*
 * @lc app=lintcode id=24 lang=cpp
 *
 * [24] LFU Cache
 *
 * https://www.lintcode.com/problem/lfu-cache/description
 *
 * lintcode
 * Hard (22.00%)
 * Total Accepted:    4854
 * Total Submissions: 21902
 * Testcase Example:  'LFUCache(3)\nset(2, 2)\nset(1, 1)\nget(2)\nget(1)\nget(2)\nset(3, 3)\nset(4, 4)\nget(3)\nget(2)\nget(1)\nget(4)\n'
 *
 * LFU (Least Frequently Used) is a famous cache eviction algorithm.
 * 
 * For a cache with capacity *k*, if the cache is full and need to evict a key
 * in it, the key with the lease frequently used will be kicked out.
 * 
 * Implement `set` and `get` method for LFU cache.
 */
#include <list>
class LFUCache {
public:
    /*
    * @param capacity: An integer
    */
    LFUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if (m.count(key) == 0) return -1;
        freq[m[key].second].erase(iter[key]);
        ++m[key].second;
        freq[m[key].second].push_back(key);
        iter[key] = --freq[m[key].second].end();
        if (freq[minFreq].size() == 0) ++minFreq;
        return m[key].first;
    }
    
    void set(int key, int value) {
        if (cap <= 0) return;
        if (get(key) != -1) {
            m[key].first = value;
            return;
        }
        if (m.size() >= cap) {
            m.erase(freq[minFreq].front());
            iter.erase(freq[minFreq].front());
            freq[minFreq].pop_front();
        }
        m[key] = {value, 1};
        freq[1].push_back(key);
        iter[key] = --freq[1].end();
        minFreq = 1;
    }

private:
    int cap, minFreq;
    unordered_map<int, pair<int, int>> m;
    unordered_map<int, list<int>> freq;
    unordered_map<int, list<int>::iterator> iter;
};
