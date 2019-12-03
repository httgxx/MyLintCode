/*
 * @lc app=lintcode id=817 lang=cpp
 *
 * [817] Range Sum Query 2D - Mutable
 *
 * https://www.lintcode.com/problem/range-sum-query-2d-mutable/description
 *
 * lintcode
 * Medium (45.00%)
 * Total Accepted:    2089
 * Total Submissions: 4599
 * Testcase Example:  'NumMatrix([[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]])\nsumRegion(2, 1, 4, 3)\nupdate(3, 2, 2)\nsumRegion(2, 1, 4, 3)'
 *
 * Given a 2D matrix, find the sum of the elements inside the rectangle defined
 * by its upper left corner (row1, col1) and lower right corner (row2, col2).
 * And the elements of the matrix could be changed.
 * 
 * You have to implement three functions:
 * - `NumMatrix(matrix)` The constructor.
 * - `sumRegion(row1, col1, row2, col2)` Return the sum of the elements inside
the rectangle defined by its upper left corner (row1, col1) and lower right
 * corner (row2, col2). 
 * - `update(row, col, val)` Update the element at (row, col) to `val`.
 * 
 * Note:
 * - The matrix is only modifiable by update.
 * - You may assume the number of calls to update and sumRegion function is distributed evenly.
 * - You may assume that row1 ≤ row2 and col1 ≤ col2.
 * 
 * Example 1:
 * Input:
 * NumMatrix(
 *  [[3,0,1,4,2],
 *   [5,6,3,2,1],
 *   [1,2,0,1,5],
 *   [4,1,0,1,7],
 *   [1,0,3,0,5]]
 * )
 * sumRegion(2,1,4,3)
 * update(3,2,2)
 * sumRegion(2,1,4,3)
 * Output:
 *   8
 *   10
 * 
 * Example 2:
 * Input:
 * NumMatrix([[1]])
 * sumRegion(0, 0, 0, 0)
 * update(0, 0, -1)
 * sumRegion(0, 0, 0, 0)
 * Output:
 *   1
 *   -1
 * 
 * @Category Binary Index Tree/Fenwick Tree
 * @Idea 树状数组 //查询和修改的复杂度均为O(logn)
 * 所有奇数位置的数字和原数组对应位置的相同,偶数位置是原数组若干位置之和
 * 如原数组A(a1, a2, a3, a4 ...)和其树状数组C(c1, c2, c3, c4 ...)有如下关系
 * C1 = A1
 * C2 = A1 + A2
 * C3 = A3
 * C4 = A1 + A2 + A3 + A4
 * C5 = A5
 * C6 = A5 + A6
 * C7 = A7
 * C8 = A1 + A2 + A3 + A4 + A5 + A6 + A7 + A8
 * ...
 * 某个位置到底有几个数组成是根据该位置坐标的最低位Low Bit(二进制数的最右边的1)开始加上后面的0(若有的话)组成的数字
 * 如1到8的最低位如下面所示：
 * 坐标          二进制       最低位
 * 1               0001          1
 * 2               0010          2
 * 3               0011          1
 * 4               0100          4
 * 5               0101          1
 * 6               0110          2
 * 7               0111          1
 * 8               1000          8
 * 9               1001          1
 * 10              1010          2
 * 11              1011          1
 * 12              1100          4
 * 13              1101          1
 * ...
 * 最低位的计算方法有两种一种是x&(x^(x–1)),另一种是利用补码特性x&-x
 * nums = { 1, 3, 5, 9, 11, 13, 15, 17}
 * bits ={0 1  4  5 18  11  24  15  74}
 * - 现在要update(2,2),先求diff=[3]-2=5-2=-3,然后根据最低位的值来更新后面含有这位数字的所以位置,一般只需更新部分偶数位置的值即可
 *   下一位需要更新的位置为j+=(j&-j)=3+1=4故更新[4]-3=15, 下一位需要更新的位置为j+=(j&-j)=4+4=8故更新[8]-3=71
 * - 现在要求区域和sum(i,j),从i开始每次sum+=[j],然后更新j-=(j&-j),扫完一遍可快速得前i个数和
 * 
 * 树状数组讲解:
 * https://blog.csdn.net/Yaokai_AssultMaster/article/details/79492190
 */
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        if (matrix.empty() || matrix[0].empty()) { return; }
        mat.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
        bit.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                update(i, j, matrix[i][j]);
            }
        }
    }
    void update(int row, int col, int val) {                // 将val加到[row,col]位置的数字上
        int diff = val - mat[row + 1][col + 1];
        for (int i = row + 1; i < mat.size(); i += i&-i) {
            for (int j = col + 1; j < mat[i].size(); j += j&-j) {
                bit[i][j] += diff;
            }
        }
        mat[row + 1][col + 1] = val;
    }
    int sumRegion(int row1, int col1, int row2, int col2) { // 求从左上[row1,col1]到右下[row2,col2]位置的所有数字的和
        return getSum(row2 + 1, col2 + 1) + getSum(row1, col1) -
               getSum(row1, col2 + 1) - getSum(row2 + 1, col1) ;
    }
    int getSum(int row, int col) {
        int res = 0;
        for (int i = row; i > 0; i -= i&-i) {
            for (int j = col; j > 0; j -= j&-j) {
                res += bit[i][j];
            }
        }
        return res;
    } 
private:
    vector<vector<int>> mat;
    vector<vector<int>> bit;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */
