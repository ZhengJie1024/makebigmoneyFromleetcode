#include <vector>

using namespace std;

// 基于二叉搜索树的解决思路
// 遇到极端case 例如 [1,2,3,4,5,6] 完全升序的序列，二叉搜索树的查找退化成o(n),这种时候需要变成平衡二叉搜索树（l.1382），大致的思路应该是旋转

class Solution {
public:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        int left_num = 0;
        int right_num = 0;
        int index = 0;
    };

    vector<int> countSmaller(vector<int>& nums) {

      // res init
      res_.resize(nums.size(), 0);
      nums_ = &nums;
      if (nums.size() > 1) {
        Node *root = nullptr;
        Node *cur = nullptr;
        for (int i = nums.size() - 1 ; i >= 0 ; i--) {
          cur = new Node();
          cur->index = i;

          if (root == nullptr) {
            root = cur;
          } else {
            // 插入 节点
            res_[i] = insert(cur, root);
          }
        }
      }

      return std::move(res_);
    }

private:
    int insert(Node* cur, Node* root) {
      int res = 0;
      while (root != nullptr) {

        if (nums_->at(cur->index) < nums_->at(root->index)) {
          root->left_num++;
          if (root->left == nullptr) {
            root->left = cur;
            break;
          }
          root = root->left;

        } else if (nums_->at(cur->index) > nums_->at(root->index)) {
          // <=
          res += root->left_num + 1;

          root->right_num++;

          if (root->right == nullptr) {
            root->right = cur;
            break;
          }
          root = root->right;
        } else {
          // 直接命中 ，在 右节点插入 node
          Node* tmp = root->right;
          root->right = cur;
          cur->right = tmp;

          cur->right_num = root->right_num;
          root->right_num++;
          res += root->left_num;
          return res;
        }
      }
      return res;
    }

    vector<int>* nums_;
    vector<int> res_;

};
