/*
 * @lc app=lintcode id=134 lang=cpp
 *
 * [134] LRU Cache
 *
 * https://www.lintcode.com/problem/lru-cache/description
 *
 * lintcode
 * Hard (27.00%)
 * Total Accepted:    23371
 * Total Submissions: 84962
 * Testcase Example:  'LRUCache(2)\nset(2, 1)\nset(1, 1)\nget(2)\nset(4, 1)\nget(1)\nget(2)\n'
 *
 * Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: `get` and `set`.
 * 
 * - `get(key)` Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1.
 * - `set(key, value)` Set or insert the value if the key is not already
 * present. When the cache reached its capacity, it should invalidate the least
 * recently used item before inserting a new item.
 * ⁠
 * Finally, you need to return the data from each get.
 * 
 * Example
 * Example1
 * Input:
 * LRUCache(2)
 * set(2, 1)
 * set(1, 1)
 * get(2)
 * set(4, 1)
 * get(1)
 * get(2)
 * Output: [1,-1,1]
 * Explanation：
 * cache cap is 2，set(2,1)，set(1, 1)，get(2) and return 1，set(4,1) and delete (1,1)，
 * because （1,1）is the least use，get(1) and return -1，get(2) and return 1.
 * 
 * Example 2:
 * Input：
 * LRUCache(1)
 * set(2, 1)
 * get(2)
 * set(3, 2)
 * get(2)
 * get(3)
 * Output：[1,-1,2]
 * Explanation：
 * cache cap is 1，set(2,1)，get(2) and return 1，set(3,2) and delete (2,1)，get(2) and return -1，
 * get(3) and return 2.
 * 
 * LRUCache 
 * 1. O(1) get(key) set(key, value)
 * 2. Capacity limit
 *    if need to add && size == cap_limit:
 *       remove LRU/oldest data b4 add 
 * whenever get()/set(): set target data to be most recently used/newest
 * => track visiting order of each data: time order
 * - remove LRU: remove from end
 * - set newest: add/move to front
 * => double linked list
 * 
 * search O(1) => hashtable
 * 
 * hashtable: key, list_node_pointer
 * double linked list: key, value
 * 
 * get()
 *    hashtable search(key) => node_pointer
 *    if !found: return -1
 *    list move_to_front(node_pointer)
 *    return node_pointer->value
 * set()
 *    hashtable search(key) => node_pointer
 *    if found:
 *       node_pointer->value = value
 *       list move_to_front(node_pointer) 
 *       return
 *    if full:
 *       list find tail
 *       hashtable remove by tail.key
 *       list remove tail
 *    
 *    list add to front(new node(key, value))
 *    hashtable add(key, new_node_pointer)
 */
#include <list>
class LRUCache {
public:
    /*
    * @param capacity: An integer
    */
    LRUCache(int capacity) {
        // do intialization if necessary
        cap = capacity;
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        // write your code here
        auto cacheItor = cache.find(key);
        if (cacheItor == cache.end()) { return -1; }
        auto recentItor = cacheItor->second;
        recent.splice(recent.begin(), recent, recentItor);
        return recentItor->second;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        // write your code here
        auto cacheItor = cache.find(key);
        if (cacheItor != cache.end()) {
            auto recentItor = cacheItor->second;
            recentItor->second = value;
            recent.splice(recent.begin(), recent, recentItor);
            return;
        }
        
        if (cache.size() == cap) {
            cache.erase(recent.rbegin()->first);
            recent.pop_back();
        }

        recent.emplace_front(key, value);
        cache[key] = recent.begin();
    }
private:
    int cap;
    list<pair<int, int>> recent;
    unordered_map<int, list<pair<int, int>>::iterator> cache;
};

