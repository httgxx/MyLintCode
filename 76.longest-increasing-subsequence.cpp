/*
 * @lc app=lintcode id=76 lang=cpp
 *
 * [76] Longest Increasing Subsequence
 *
 * https://www.lintcode.com/problem/longest-increasing-subsequence/description
 *
 * lintcode
 * Medium (33.00%)
 * Total Accepted:    25572
 * Total Submissions: 77383
 * Testcase Example:  '[]'
 *
 * Given a sequence of integers, find the longest increasing subsequence (LIS).
 * You code should return the length of the LIS.
 * 
 * @Category DP(按情况叠加比较型)
 * @Ideas
 * S1: // T=O(nlogn) S=O(n) 
 * 最长上升子序列LIS
 * 相同长度的LIS末尾越小越有可能append新的更大数形成更长LIS
 * 记录每种长度的LIS的最小末尾值: ends[i]=所有长度为i的IncresingSequence的末尾值中最小的 
 * 每次访问到新数,用它去替换ends中第1个>=新数的LIS末尾 
 * 注: 若LIS不允许重复数,则ends不允许有重复数;如果LIS允许重复数,则ends允许有重复数
 *     两种情况下都是用a[i]去替换第一个>=a[j]的ends[k]
 * 
 * S2: // T=O(n^2) S=O(n)
 * dp[i]表示以a[i]结尾的LIS长度
 * =以a[i]前面的某个<a[i]的a[k]为结尾的LIS中最长的长度+1
 * =max{dp[k]|k<i且a[k]<a[i]} + 1
 * 初始 dp[0]=1
 * 顺序 i=0~n-1, k=i~i-1
 * 返回 max(dp[i])
 * 注: 若LIS不允许重复数,则ends不允许有重复数,要找a[k]<a[i]
 *     若LIS允许重复数,则ends允许有重复数,要找a[k]<=a[i]
 * 坑: dp[]初始化为1而不是0
 * 坑: 返回max(dp[i])而不是dp[n-1] 因为最长LIS可能是以任1个[i]结尾
 */
class Solution {
public:
    /**
     * @param nums: An integer array
     * @return: The length of LIS (longest increasing subsequence)
     */
    int longestIncreasingSubsequence(const vector<int> &nums) {
        vector<int> ends;
        for (int i = 0; i < nums.size(); ++i) {
            int left = 0, right = ends.size();  // ends可能已增长故每次重算right
            if (right == 0 || nums[i] > ends.back()) {
               // case1:[i]>当前LIS最小末尾,即加在最小末尾后形成更长LIS
               ends.push_back(nums[i]);  // 更新ends
            } else {  // ends中至少还有1个数所以肯定有left<=right
              // case2:[i]<当前LIS最小末尾,即不能直接形成更长LIS
              // 即二分找到ends中第一个>=[i]的值来替换成[i]
              while (left < right) {  // 至少还剩2个数
                int mid = left + (right - left) / 2;
                if (ends[mid] < nums[i]) {
                    left = mid + 1;  // [mid]太小,去右边找更大
                } else {  // ends[mid] >= nums[i]
                    right = mid;  // [mid]符合条件,去左边(包含mid)找更小
                }
              }
              ends[right] = nums[i];  // 肯定有1个>[i]所以只可能是这个
            }
        }
        return ends.size();
    }

    int longestIncreasingSubsequence1(const vector<int> &nums) {
        int n = nums.size();
        if (n < 2) { return n; }
        int res = 0;
        vector<int> dp(n, 1);  // 坑:初始值为1而不是0!
        for (int i = 1; i < n; ++i) {  // 以[i]结尾
            for (int k = 0; k < i; ++k) {  // 找[i]前面[k]<[i]
                if (nums[k] < nums[i]) {
                    dp[i] = max(dp[i], dp[k] + 1);
                }
            }
            res = max(res, dp[i]);  // 坑:最后不是返回dp[n-1]而是max(dp[i])
        }
        return res;
    }

    int longestIncreasingSubsequence1Path(const vector<int> &nums) {
        int n = nums.size();
        if (n < 2) { return n; }
        int res = 0;
        vector<int> dp(n, 1);  // 坑:初始值为1而不是0!
        vector<int> parent(n);  // 坑:必须指定大小,打印路径多开空间不要紧
        int node = 0;
        for (int i = 1; i < n; ++i) {  // 以[i]结尾
            for (int k = 0; k < i; ++k) {  // 找[i]前面[k]<[i]
                if (nums[k] < nums[i]) {
                    dp[i] = max(dp[i], dp[k] + 1);
                    if (dp[i] == dp[k] + 1) {
                        parent[i] = k;  // 更新当前节点的前驱结点
                    }
                }
            }
            res = max(res, dp[i]);  // 坑:最后不是返回dp[n-1]而是max(dp[i])
            if (res == dp[i]) { node = i; }  // 更新终点
        }
        vector<int> path(res);
        for (int i = res - 1; i >= 0; --i) {  // 倒着打印路径
            path[i] = node;
            node = parent[node];
        }
        for (int i = 0; i < res; ++i) {
            cout << path[i];
        }
        return res;
    }
};
