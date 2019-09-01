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
 * @Category DataStructure Design
 * @Idea
 * 要求:
 * 1. 读写都是O(1)
 * 2. 每次读/写都要设值为最近被访问的
 * 3. capacity => 满了再写需要删掉最久没有被访问的值
 * => HashTable + Double-Linked-List(按访问时间长久排序)
 * get(key) O(1)
 *     1.有
 *     2.没有
 * put(key, value) O(1)
 *     1.有
 *     2.没有
 *       2.1 满
 *       2.2 没满
 */
#include <list>  
class LRUCache {
public:
    /*
    * @param capacity: An integer
    */
    LRUCache(int capacity) {
        cap = capacity;
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        auto mapItor = cache.find(key);
        if (mapItor == cache.end()) { return -1; }  // 没找到返回-1
        auto listItor = mapItor->second;
        recent.splice(recent.begin(), recent, listItor);  // 找到则移到表头后返回value
        return listItor->second;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        auto mapItor = cache.find(key);
        if (mapItor != cache.end()) {  // 若已存在
            auto listItor = mapItor->second;
            // 方法一: 更新值后前移到表头, 并立即返回
            listItor->second = value;
            recent.splice(recent.begin(), recent, listItor);  // 移到表头
            return;  // 勿忘!!!

            // 方法二: 删除后继续(之后要当作新值加到表头)
            //recent.erase(listItor);  // will update map later when adding new node
        }
        
        if (cache.size() == cap) {  // 若满容则需删去最旧/表尾
            cache.erase(recent.rbegin()->first);  // 先删map中表尾对应的entry
            recent.pop_back();                    // 再删表尾(先删引用再删实体)
        }

        recent.emplace_front(key, value);  // 优于recent.push_back(make_pair(key, value))
        cache[key] = recent.begin();       // 先加表头再加入map(先加实体再加引用)
    }
private:
    int cap;  // capacity
    list<pair<int, int>> recent;  // key, value
    unordered_map<int, list<pair<int, int>>::iterator> cache;  // key, node_pointer
};
