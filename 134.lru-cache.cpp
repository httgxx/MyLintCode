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
 * Capacity limit:
 * if add && size==cap: remove least recently used b4 add
 * => track visiting order of each data: newest=front, oldest=back
 * get: search data O(1) => hashtable
 *      move data to front O(1) => double linked list 
 * set: search data O(1) => hashtable
 *      if not found
 *         if full
 *            remove from back => list + tail
 *         else
 *            add to front => list
 * 
 * Data structure: hashtable + double linked list      
 * hashtable: <key, node_pointer>
 * list: <key, value>  
 * C++ STL: unorderd_map, list,
 * move data to front: list::splice(to_pos, list, from_pos)
 * add new to front: list::emplace_front(args)
 * move from back: list::pop_back()
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
        if (mapItor == cache.end()) { return -1; }
        auto listItor = mapItor->second;
        recent.splice(recent.begin(), recent, listItor);
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
        if (mapItor != cache.end()) {  // if exist, update and move to front
            auto listItor = mapItor->second;
            listItor->second = value;  // update
            recent.splice(recent.begin(), recent, listItor);  // move to front
            return;
        }

        if (cache.size() == cap) {  // if full, remove from map, remove from back
           cache.erase(recent.rbegin()->first);  // remove from map
           recent.pop_back();  // remove from back
        }

        recent.emplace_front(key, value); // not full, add to front, add to map
        cache[key] = recent.begin();
    }
private:
    int cap;
    list<pair<int, int>> recent;
    unordered_map<int, list<pair<int, int>>::iterator> cache;
};
