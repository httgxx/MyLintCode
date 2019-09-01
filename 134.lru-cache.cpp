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
 * 1. get() put() O(1)
 * 2. capacity limit
 *    set()
 *      if need to add && size == capacity:
 *          remove LRU b4 add
 *    get()/set()
 *      set target data to be most recently used
 * =>
 * 1. track visiting order of each data  => double linked list
 *    most recently used data // changed by get/set => move/add to front
 *    least recently used data// removed when full  => remove from back
 * 2. search O(1) => hashtable
 *    get(key) => move node for the key to front
 * 
 * hashtable: key, list_node_pointer
 * list: key, value
 * 
 * get(key)
 *    seach(key)
 *    if not found: return -1
 *    else:
 *        find node_pointer by key  
 *        move node to front
 *        return value
 * set(key, value)
 *    search(key)
 *    if found:
 *       find node_pointer by key
 *       update value
 *       move node to front
 *       return
 *    else not found
 *       if full:
 *          find tail
 *          find key for the tail
 *          remove tail's entry from hashtable
 *          remove tail from back
 *       //else:
 *       add to front
 *       add to hashtable
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
        auto mapItor = cache.find(key);
        if (mapItor == cache.end()) { return -1; }   // not find return -1
        auto listItor = mapItor->second;
        recent.splice(recent.begin(), recent, listItor);  // found: move to front and return
        return listItor->second;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        // write your code here
        auto mapItor = cache.find(key);
        if (mapItor != cache.end()) {  // if found:  update and move to front
            auto listItor = mapItor->second;
            listItor->second = value;   // update
            recent.splice(recent.begin(), recent, listItor);  // found: move to front and return    
            return;
        }
        
        if (cache.size() == cap) {  // if full: remove from back and from hashmap
           cache.erase(recent.rbegin()->first);  // remove from hashmap
           recent.pop_back();  // remove from back
        }

        recent.emplace_front(key, value);  // add to front
        cache[key] = recent.begin();  // add to hashmap
    }
private:
    int cap;
    list<pair<int, int>> recent;
    unordered_map<int, list<pair<int, int>>::iterator> cache;
};
