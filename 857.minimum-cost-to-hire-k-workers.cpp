/*
 * @lc app=leetcode id=857 lang=cpp
 *
 * [857] Minimum Cost to Hire K Workers
 *
 * https://leetcode.com/problems/minimum-cost-to-hire-k-workers/description/
 *
 * algorithms
 * Hard (48.70%)
 * Total Accepted:    22.6K
 * Total Submissions: 46.5K
 * Testcase Example:  '[10,20,5]\n[70,50,30]\n2'
 *
 * There are N workers.  The i-th worker has a quality[i] and a minimum wage
 * expectation wage[i].
 * 
 * Now we want to hire exactly K workers to form a paid group.  When hiring a
 * group of K workers, we must pay them according to the following rules:
 * 
 * Every worker in the paid group should be paid in the ratio of their quality
 * compared to other workers in the paid group.
 * Every worker in the paid group must be paid at least their minimum wage
 * expectation.
 * 
 * Return the least amount of money needed to form a paid group satisfying the
 * above conditions.
 *  
 * Example 1:
 * Input: quality = [10,20,5], wage = [70,50,30], K = 2
 * Output: 105.00000
 * Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
 *
 * Example 2: 
 * Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
 * Output: 30.66667
 * Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers
 * seperately. 
 * 
 * Note:
 * 1 <= K <= N <= 10000, where N = quality.length = wage.length
 * 1 <= quality[i] <= 10000
 * 1 <= wage[i] <= 10000
 * Answers within 10^-5 of the correct answer will be considered correct.
 * 
 */
class Solution {
public:
    // 贪心 T=O(nlogn) S=O(n)
    // 1. 工资越低技能越高的工人越省成本,所以要找工资/技能比值小的工人
    //    工资/技能比值相同时,技能越低工资越低,所以要找技能小的工人
    //    故先按工资/技能从小到大排,再按技能从小到大排
    // 2. 用最大堆求当前技能最小的K个工人
    //    每次堆内>k个人, 去掉技能最大的(最贵的)工人
    //    每次堆内有k个人,计算总花费=技能总和*工资/技能,更新最小花费值
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        double res = DBL_MAX, qsum = 0, n = quality.size();                 // 坑: double, DBL_MAX
        vector<pair<double, int>> workers;                                  // workers<pair<工资/技能,技能>>
        priority_queue<int> pq;                                             // 用最大堆求技能最小的K个工人
        for (int i = 0; i < n; ++i) {                                       // T=O(n) S=O(n)
            workers.push_back({ double(wage[i]) / quality[i], quality[i] });// 先按工资/技能从小到大排,再按技能从小到大排
        }
        sort(workers.begin(), workers.end());                               // T=O(nlogn)
        for (auto worker : workers) {                                       // T=O(nlogk) S=O(k)
            qsum += worker.second;                                          // 累计堆内技能总和
            pq.push(worker.second);                                         // 当前技能入堆
            if (pq.size() > K) {                                            // 若堆内>k个工人
                qsum -= pq.top(); pq.pop();                                 //   丢技能最大的(最贵的),并更新堆内技能总和
            }
            if (pq.size() == K) {                                           // 若堆内正好k个工人
                res = min(res, qsum * worker.first);                        //   计算花费=技能总和*工资/技能,更新最小花费
            }
        }
        return res;
    }
};
