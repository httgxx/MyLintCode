/*
 * @lc app=lintcode id=7 lang=cpp
 *
 * [7] Serialize and Deserialize Binary Tree
 *
 * https://www.lintcode.com/problem/serialize-and-deserialize-binary-tree/description
 *
 * lintcode
 * Medium (29.00%)
 * Total Accepted:    35246
 * Total Submissions: 118105
 * Testcase Example:  '{3,9,20,#,#,15,7}'
 *
 * Design an algorithm and write code to serialize and deserialize a binary
 * tree. Writing the tree to a file is called 'serialization' and reading back
 * from the file to reconstruct the exact same binary tree is 'deserialization'.
 */
/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 * 
 * @Category ostringstream + istringstream + recursion
 * @Idea 字符串输入输出流+递归
 * 坑: 用ostringstream out和istringstream in(string data), out << s, in >> s
 * 坑: 必须用' '分隔结点,用'#'标记空来建满二叉树,这样才能保证先根访问二叉树能被唯一还原
 * 坑: 结点值是int型 必须由istringstream>>s后通过stoi(s)转换成int val
 * serialize(TreeNode* root): 定义ostringstream out; serialize(root,out); return out.str();
 *   serialize(root, out): if(root){ out<<root->val<<' '; serialize(root->left,out); serialize(root->right,out);}
 *                         else{ out<<'#'; }
 * TreeNode* deserialize(string& data): 定义istringstream in(data); return deserialize(in);
 *   TreeNode* deserialize(data): string val; in >> val; if(val=='#')return nullptr; 
 */


class Solution {
public:
    /**
     * This method will be invoked first, you should design your own algorithm 
     * to serialize a binary tree which denote by a root node to a string which
     * can be easily deserialized by your own "deserialize" method later.
     */
    string serialize(TreeNode * root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    /**
     * This method will be invoked second, the argument data is what exactly
     * you serialized at method "serialize", that means the data is not given by
     * system, it's given by your own serialize method. So the format of data is
     * designed by yourself, and deserialize it here as you serialize it in 
     * "serialize" method.
     */
    TreeNode * deserialize(string &data) {
        istringstream in(data);
        return deserialize(in);
    }
private:
    void serialize(TreeNode *root, ostringstream &out) {
        if (root) {
            out << root->val << ' ';                // 用' '分隔结点
            serialize(root->left, out);             // 递归
            serialize(root->right, out);            // 递归
        }
        else {
            out << "# ";                            // 用'#'标记空
        }
    }
    TreeNode* deserialize(istringstream &in) {
        string val;
        in >> val;                                  // 用' '分隔结点
        if (val == "#") return nullptr;             // 用'#'标记空
        TreeNode *root = new TreeNode(stoi(val));   // 坑:必须由string转换成int型结点值
        root->left = deserialize(in);               // 递归
        root->right = deserialize(in);              // 递归
        return root;
    }
};
