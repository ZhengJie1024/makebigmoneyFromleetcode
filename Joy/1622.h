#include <vector>
#include <stack>
#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;
typedef unsigned long long uint64;

class NodeSegTree {
public:
    struct Node {
        // 左闭右闭
        int l_;
        int r_;
        uint64 treesum_;
        uint64 mul_;
        uint64 bias_;

        Node(int l, int r) : l_(l), r_(r) {
          mul_ = 1;
          treesum_ = 0;
          bias_ = 0;
          left_ = nullptr;
          right_ = nullptr;
        }

        Node* left() {
          if (left_ == nullptr) {
            left_ = new Node(l_, mid());
          }
          return left_;
        }

        Node* right() {
          if (right_ == nullptr) {
            right_ = new Node(mid() + 1, r_);
          }
          return right_;
        }

        int mid() {
          return l_ + (r_ - l_) / 2;
        }

      private:
        Node* left_;
        Node* right_;


    };

    NodeSegTree (int l, int r) {
      root_ = new Node(l, r);
    }

    void add_update(Node* node, int lr, int rr, int val, bool is_mul = false) {
      if (lr <= node->l_ && node->r_ <= rr) {
        // 当前线段 处于覆盖区间
        if (lr == rr) {
          node->treesum_ = val;
        } else {
          if (is_mul) {
            node->mul_ *= val;
            node->bias_ *= val;
            node->treesum_ *= val;

            node->mul_ = node->mul_ % MOD;
          } else {
            node->bias_ +=  val;
            node->treesum_ += (node->r_ - node->l_ + 1) * val;
          }

          node->bias_ = node->bias_ % MOD;
          node->treesum_ = node->treesum_ % MOD;
        }
        return ;
      }

      lazy_update(node);

      if (lr <= node->mid()) {
        add_update(node->left(), lr, rr, val, is_mul);
      }
      if (node->mid() + 1 <= rr) {
        add_update(node->right(), lr, rr, val, is_mul);
      }

      node->treesum_ = node->left()->treesum_ + node->right()->treesum_;
      node->treesum_ =  node->treesum_ % MOD;
    }

    void lazy_update (Node* node) {
      if (node->bias_ != 0 || node->mul_ != 1) {
        node->left()->bias_ = node->left()->bias_ * node->mul_ + node->bias_;
        node->left()->mul_ *= node->mul_;
        node->left()->treesum_ = node->left()->treesum_ * node->mul_ + node->bias_;

        node->right()->bias_ = node->right()->bias_ * node->mul_ + node->bias_;
        node->right()->mul_ *= node->mul_;
        node->right()->treesum_ = node->right()->treesum_ * node->mul_ + node->bias_;

        node->left()->bias_ = node->left()->bias_ % MOD;
        node->left()->mul_ = node->left()->mul_ % MOD;
        node->left()->treesum_ = node->left()->treesum_ % MOD;

        node->right()->mul_ = node->right()->mul_ % MOD;
        node->right()->bias_ = node->right()->bias_ % MOD;
        node->right()->treesum_ = node->right()->treesum_ % MOD;

        node->bias_ = 0;
        node->mul_ = 1;
      }
    }

    int query(Node* node, int lr, int rr) {
      if (node->r_ < lr || rr < node->l_) {
        return 0;
      }
      if (node->r_ <= rr && node->l_ >= lr ) {
        return node->treesum_;
      }
      lazy_update(node);
      int res = query(node->left(), lr, rr) + query(node->right(), lr, rr);
      return res;
    }

  Node* root_;
};

class Fancy
{
public:
    NodeSegTree * ST;
    int n;          //实指

    Fancy()
    {
      this->ST = new NodeSegTree(0, 100000);
      this->n = -1;
    }

    void append(int val)
    {
      n ++;
      ST->add_update(ST->root_, n, n, val);
    }

    void addAll(int inc)
    {
      if (n >= 0)
        ST->add_update(ST->root_, 0, n, inc);
    }

    void multAll(int m)
    {
      if (n >= 0)
        ST->add_update(ST->root_, 0, n, m, true);
    }

    int getIndex(int idx)
    {
      if (n < idx)
        return -1;
      return ST->query(ST->root_, idx, idx);
    }
};