/*
 * @lc app=lintcode id=399 lang=cpp
 *
 * [399] Nuts & Bolts Problem
 *
 * https://www.lintcode.com/problem/nuts-bolts-problem/description
 *
 * lintcode
 * Medium (22.00%)
 * Total Accepted:    7393
 * Total Submissions: 32468
 * Testcase Example:  '["ab","bc","dd","gg"]\n["AB","GG","DD","BC"]\n'
 *
 * Given a set of *n* nuts of different sizes and *n* bolts of different sizes.
 * There is a one-one mapping between nuts and bolts. 
 * 
 * Comparison of a nut to another nut or a bolt to another bolt is **not
 * allowed**. It means nut can only be compared with bolt and bolt can only be
 * compared with nut to see which one is bigger/smaller.  We will give you a
 * compare function to compare nut with bolt.
 * 
 * Using the function we give you, you are supposed to sort nuts or bolts, so
 * that they can map in order.
 * Example
 * Given nuts = ['ab','bc','dd','gg'], bolts = ['AB','GG', 'DD', 'BC'].
 * Your code should find the matching of bolts and nuts.
 * According to the function, one of the possible return:
 *   nuts = ['ab','bc','dd','gg'], bolts = ['AB','BC','DD','GG'].
 * If we give you another compare function, the possible return is the following:
 *   nuts = ['ab','bc','dd','gg'], bolts = ['BC','AA','DD','GG'].
 * So you must use the compare function that we give to do the sorting.
 * The order of the nuts or bolts does not matter. You just need to find the matching bolt for each nut.
 * 
 * @Category quickSort 2arrays
 * @Idea quickSort 2arrays
 * 要求:只能比较bolt和nut,不能bolts之间比或nuts之间比,如何分别排序bolts和nuts
 * 思路:因bolt和nut一一配对,先随机选bolt作pivot来快排nuts,再选已在正确位置的nut作pivot来快排bolts,
 *      然后递归nuts左右半段重复上述步骤
 * e.g. dd bb cc aa 和 BB DD AA CC
 * =>先选BB作pivot来partition "dd bb cc aa"=>bb aa dd cc //"bb aa"顺序不确定,"dd cc"顺序不确定
 * =>再选bb作pivot来partition "BB DD AA CC"=>BB AA DD CC //"BB AA"顺序不确定,"DD CC"顺序不确定
 * =>再递归到左右半段quick sort
 * 
 * T=O(nlogn) S=O(n)
*/
/**
 * class Comparator {
 *     public:
 *      int cmp(string a, string b);
 * };
 * You can use compare.cmp(a, b) to compare nuts "a" and bolts "b",
 * if "a" is bigger than "b", it will return 1, 
 * else if they are equal, it will return 0, 
 * else if "a" is smaller than "b", it will return -1.
 * When "a" is not a nut or "b" is not a bolt, it will return 2, which is not valid.
 **/ 
class Solution {
public:
    /**
     * @param nuts: a vector of integers
     * @param bolts: a vector of integers
     * @param compare: a instance of Comparator
     * @return: nothing
     */
    // bolts和nuts都各自排序但只能比较bolt和nut
    // 因bolt和nut一一配对,先随机选bolt作pivot来快排nuts,再选已在正确位置的nut作pivot来快排bolts,
    // 然后递归nuts左右半段重复上述步骤
    // T=O(nlogn) S=O(n)
    void sortNutsAndBolts(vector<string> &nuts, vector<string> &bolts, Comparator compare) {
        if (nuts.empty() || bolts.empty() || nuts.size() != bolts.size()) { return; }   // 处理特例
        quickSort(nuts, bolts, compare, 0, nuts.size() - 1);
    }

    void quickSort(vector<string> &nuts, vector<string> &bolts, Comparator compare, int l, int r) {
        if (l >= r) { return; }                                     // 递归结束
        int pivotIdx = partition(nuts, bolts[l], compare, l, r);    // 快排nuts:将bolts[l]作pivot来分区nuts,找对应nuts pivot正确位置
        partition(bolts, nuts[pivotIdx], compare, l, r);            // 快排bolts:将nuts中刚定位的值作pivot来分区bolts,找对应pivot位置
        quickSort(nuts, bolts, compare, l, pivotIdx - 1);           // 递归快排nuts左半段
        quickSort(nuts, bolts, compare, pivotIdx + 1, r);           // 递归快排nuts右半段
    }

    int partition(vector<string> &strs, string pivot, Comparator compare, int l, int r) {
        int smallEnd = l;                                           // smallEnd从l开始
        for (int i = l + 1; i <= r; ++i) {                          // 从[l+1]开始
            if (compare.cmp(strs[i], pivot) == -1 ||                //   若[i]<pivot
                compare.cmp(pivot, strs[i]) == 1) {                 //   坑:cmp(nut,bolt)而strs[i]可nut可bolt,故2种比较结果union
                ++smallEnd;                                         //     smallEnd后移1 //此时仍有smallEnd<=l
                swap(strs[i], strs[smallEnd]);                      //     交换[i]和[smallEnd]以确保smallEnd指向比pivot小的最后一个 
            }
            else if (compare.cmp(strs[i], pivot) == 0 ||            //   若[i]==pivot
                compare.cmp(pivot, strs[i]) == 0) {                 //   坑:cmp(nut,bolt)而strs[i]可nut可bolt,故2种比较结果union
                swap(strs[i], strs[l]);                             //     交换[i]和[l]以确保pivot在最开头,换过来的原开头会继续和pivot比
                --i;                                                //     for(...;++i)会后移i,但交换[i]和[l]后还应用[i]新值比较,故先--i
            }
        }
        swap(strs[smallEnd], strs[l]);                              // 最后将pivot放到正确位置且返回该位置index
        return smallEnd;
    }
};
