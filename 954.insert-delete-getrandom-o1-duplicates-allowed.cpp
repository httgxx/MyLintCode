/*
 * @lc app=lintcode id=954 lang=cpp
 *
 * [954] Insert Delete GetRandom O(1) - Duplicates allowed
 *
 * https://www.lintcode.com/problem/insert-delete-getrandom-o1-duplicates-allowed/description
 *
 * lintcode
 * Hard (43.00%)
 * Total Accepted:    1000
 * Total Submissions: 2257
 * Testcase Example:  'insert(1)\ninsert(1)\ninsert(2)\ngetRandom()\nremove(1)\ngetRandom()'
 *
 * Design a data structure that supports all following operations in average **O(1)** time.
 * Note: Duplicate elements are allowed.
 * insert(val): Inserts an item val to the collection.
 * remove(val): Removes an item val from the collection if present.
 * getRandom: Returns a random element from current collection of elements. The probability of
 * each element being returned is linearly related to the number of same value the collection contains.
 * 
 * Example 1:
 * Input:
 * insert(1)
 * insert(1)
 * insert(2)
 * getRandom()
 * remove(1)
 * 
 * // Init an empty collection.
 * RandomizedCollection collection = new RandomizedCollection();
 * // Inserts 1 to the collection. Returns true as the collection did not contain 1.
 * collection.insert(1);
 * // Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
 * collection.insert(1);
 * // Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
 * collection.insert(2);
 * // getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
 * collection.getRandom();
 * // Removes 1 from the collection, returns true. Collection now contains [1,2]
 * collection.remove(1);
 * // getRandom should return 1 and 2 both equally likely.
 * collection.getRandom();
 *
 * Example 2:
 * Input:
 * insert(1)
 * insert(1)
 * getRandom()
 * remove(1)
 * 
 * @Category DataStructure Design (Hashtable<int,set> + array)
 * 允许重复数字,则hashtable存数字在数组中的位置时,一个数字可能对应多个位置,用set存
 * 加入时加到数组尾,删除时换到数组尾删掉
 * 
 * // 坑: 只有是新加入时才会只有一个对应位置
 */
class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {}
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        nums.push_back(val);                    // 加到数组尾
        m[val].insert(nums.size() - 1);         // 将数组位置加入该数对应的位置集合/set中
        return m[val].size() == 1;              // 坑: 只有是新加入时才会只有一个对应位置
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (m[val].empty()) { return false; }   // 不存在,无法删除
        int idx = *m[val].begin();              // 找到数字在数字中的第一个位置
        m[val].erase(idx);                      // 将该位置从位置映射表中删除
        if (nums.size() - 1 != idx) {           // 若该位置不在数组尾,则需将数组尾的数字拷贝到该位置
            int t = nums.back();
            nums[idx] = t;                      // 将数组尾拷贝到该位置
            m[t].erase(nums.size() - 1);        // 删除待删元素在位置映射中的值
            m[t].insert(idx);                   // 更新数组尾元素在位置映射中的值
        } 
        nums.pop_back();                        // 删除数组尾元素
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return nums[rand() % nums.size()];      // 不受是否有重复数字的影响
    }
private:
    vector<int> nums;
    unordered_map<int, unordered_set<int>> m;   // set用来存重复值对应的数组中的不同位置, 用set是为了O(1)操作
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
