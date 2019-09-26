/*
 * @lc app=lintcode id=657 lang=cpp
 *
 * [657] Insert Delete GetRandom O(1)
 *
 * https://www.lintcode.com/problem/insert-delete-getrandom-o1/description
 *
 * lintcode
 * Medium (48.00%)
 * Total Accepted:    6976
 * Total Submissions: 14437
 * Testcase Example:  'insert(1)\nremove(2)\ninsert(2)\ngetRandom()\nremove(1)\ninsert(2)\ngetRandom()\n'
 *
 * Design a data structure that supports all following operations in average
 * `O(1)` time.
 * 
 * - `insert(val)`: Inserts an item val to the set if not already present.
 * - `remove(val)`: Removes an item val from the set if present.
 * - `getRandom`: Returns a random element from current set of elements. Each
 * element must have the same probability of being returned.
 * 
 * Example
 * // Init an empty set.
 * RandomizedSet randomSet = new RandomizedSet();
 * // Inserts 1 to the set. Returns true as 1 was inserted successfully.
 * randomSet.insert(1);
 * // Returns false as 2 does not exist in the set.
 * randomSet.remove(2);
 * // Inserts 2 to the set, returns true. Set now contains [1,2].
 * randomSet.insert(2);
 * // getRandom should return either 1 or 2 randomly.
 * randomSet.getRandom();
 * // Removes 1 from the set, returns true. Set now contains [2].
 * randomSet.remove(1);
 * // 2 was already in the set, so return false.
 * randomSet.insert(2);
 * // Since 2 is the only number in the set, getRandom always return 2.
 * randomSet.getRandom();
 * 
 * @Category DataStructure Design (Hashtable<int,int> + array/vector)
 * @Idea:数字插到数组尾,或交换到尾后删除尾,Hashtable存数字在数组中的映射
 */
class RandomizedSet {
public:
    RandomizedSet() {}

    /*
     * @param val: a value to the set
     * @return: true if the set did not already contain the specified element or false
     */
    bool insert(int val) {
        if (m.count(val)) { return false; } // 已存在,无法再加
        nums.push_back(val);                // 先把数字插到数组尾部
        m[val] = nums.size() - 1;           // 再建立数字到在数组中位置的映射
        return true;
    }

    /*
     * @param val: a value from the set
     * @return: true if the set contained the specified element or false
     */
    bool remove(int val) {
        if (!m.count(val)) { return false; }// 不存在,无法删除
        int last = nums.back();             // 找到数组尾部数字
        m[last] = m[val];                   // 先将数组尾部数字的数组位置改成待删数字的数组位置
        nums[m[val]] = last;                // 再将数组尾部数字拷贝到数组中待删数字的位置
        nums.pop_back();                    // 删除数组尾部数字(已经写入另一位置)
        m.erase(val);                       // 删除待删数字的位置映射
        return true;
    }

    /*
     * @return: Get a random element from the set
     */
    int getRandom() {
        return nums[rand() % nums.size()];  // 生成随机数后对数组大小取模
    }
private:
    vector<int> nums;
    unordered_map<int, int> m;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param = obj.insert(val);
 * bool param = obj.remove(val);
 * int param = obj.getRandom();
 */
