#include <string>
#include <set>
#include <ostream>
#include <random>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 对于每个 Node:
// score = max(left_score  +  cur_score, right_score + cur_score, cur_score )
// max_num = max(max_num, max(max(left_score, 0) + max(right_score, 0 ) + cur_score))
// 左右 中， 后序遍历，保存 max_num
class Solution {
public:
    int maxPathSum(TreeNode* root, int &val)
    {
      if (root == nullptr) return 0;
      int left = maxPathSum(root->left, val);
      int right = maxPathSum(root->right, val);
      int lmr = root->val + max(0, left) + max(0, right);
      int ret = root->val + max(0, max(left, right));
      val = max(val, lmr);
      return ret;
    }

    int maxPathSum(TreeNode* root)
    {
      int val = INT_MIN;
      maxPathSum(root, val);
      return val;
    }
}