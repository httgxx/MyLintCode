/*
 * @lc app=lintcode id=1070 lang=cpp
 *
 * [1070] Accounts Merge
 *
 * https://www.lintcode.com/problem/accounts-merge/description
 *
 * lintcode
 * Medium (53.00%)
 * Total Accepted:    3354
 * Total Submissions: 6224
 * Testcase Example:  '[["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]'
 *
 * Given a list accounts, each element accounts[i] is a list of strings, where
 * the first element accounts[i][0] is a name, and the rest of the elements are
 * emails representing emails of the account.
 * 
 * Now, we would like to merge these accounts. Two accounts definitely belong
 * to the same person if there is some email that is common to both accounts.
 * Note that even if two accounts have the same name, they may belong to
 * different people as people could have the same name. A person can have any
 * number of accounts initially, but all of their accounts definitely have the
 * same name.
 * 
 * After merging the accounts, return the accounts in the following format: the
 * first element of each account is the name, and the rest of the elements are
 * emails in **sorted order**. The accounts themselves can be returned in any
 * order.
 * 
 * Example 1
 * Input:
*	[
 *		["John", "johnsmith@mail.com", "john00@mail.com"],
 *		["John", "johnnybravo@mail.com"],
 *		["John", "johnsmith@mail.com", "john_newyork@mail.com"],
 *		["Mary", "mary@mail.com"]
 *	]
 *	Output: 
 *	[
 *		["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],
 *		["John", "johnnybravo@mail.com"],
 *		["Mary", "mary@mail.com"]
 *	]
 *	Explanation: 
 *	The first and third John's are the same person as they have the common email "johnsmith@mail.com".
 *	The second John and Mary are different people as none of their email addresses are used by other accounts.
 *	You could return these lists in any order, for example the answer
 *	[
 *		['Mary', 'mary@mail.com'],
 *		['John', 'johnnybravo@mail.com'],
 *		['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']
 *	]
 *	is also acceptable.
 *
 * @Category: Union Find
 * @Idea: 并查集
 * 合并含有相同email的user
 * 输入:[[user,email,email,...]] 输出:[[user,email,email,...]]
 * 1.建立root_map: 合并所有(users的)emails到connected_components,每个连通分量包含相同user的所有emails(选其中某个email为root_email为该连通分量的id)
 *   root[email]=root_email //connected_component_id
 *   root_map不再是int[]而是unordered_map<string,string>,因为string=>string而不是int=>int
 * 2.从root_map构建结果集
 *   每个连通分量对应一个unique的user,要知道是哪个user必须事先保存map[email]=user
 *   每个连通分量里的emails必须字母排序后加到对应user的结果集item
 * 
 */
class Solution {
public:
    /**
     * @param accounts: List[List[str]]
     * @return: return a List[List[str]]
     */
    // Union Find
    // 合并emails到connected_components后重新建结果集
    // T=O(mnlogn) S=O(mn)
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
        unordered_map<string, string> root;                                 // root[email]=rootEmail
        unordered_map<string, string> user;                                 // user[rootEmail]=userName
        for (auto account : accounts) {                                     // 1.初始化: 将输入的每个user当作1个component // T=O(mn) S=O(mn)
            for(int i = 1; i < account.size(); ++i) {                       //   对该user的每个email
                user[account[i]] = account[0];                              //     记录该email对应的user
                root[account[i]] = account[1];                              //     将第1个email设为component的root且设为该user所有emails的root(即加入该component)
            }                                                               // 注!!!:初始化结束后,同component中不同email可能会有不同root,因为如果同1个email在不同
        }                                                                   //       components出现过,则该email的root会被更新为它出现过的最后一个component的root
        for (auto account : accounts) {                                     // 2.合并component: 含有相同email的component合并成一个connected_component
            string newRoot = find(account[1], root);                        // T=O(mnlogn) S=O(mn)
            for(int i = 1; i < account.size(); ++i) {
                root[find(account[i], root)] = newRoot;       
            }                     
        }
        unordered_map<string, set<string>> mergedComponents;                // 3.合并email: 找出属于每个connected_component的所有emails
        for (auto account : accounts) {                                     // T=O(mnlogn) S=O(mn)
            for (int i = 1; i < account.size(); ++i) {
                mergedComponents[find(account[i], root)].insert(account[i]);
            }
        }
        vector<vector<string>> res;                                         // res[i]=[user,email,email,email] // T=O(mnlogn) S=O(mn)
        for (auto root2Emails : mergedComponents) {                         // 4.输出: 每个合并后的connected_component里的所有email排序后+user加入结果集
            vector<string> mergedAccount(root2Emails.second.begin(), root2Emails.second.end()); 
            mergedAccount.insert(mergedAccount.begin(), user[root2Emails.first]);
            res.push_back(mergedAccount);                                                     
        }

        return res;
    }
    string find(string s, unordered_map<string, string>& root) {            // 递归find&set root+压缩路径
        return root[s] == s ? s : root[s] = find(root[s], root);
    }
};
