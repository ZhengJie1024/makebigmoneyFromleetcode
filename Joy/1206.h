#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class Skiplist {
public:
    struct Node {
        int val;
        vector<Node*> next;

        explicit Node (int val, int level): val(val) {
          next.resize(level, nullptr);
        }
    };

    Skiplist() {
      // head_的所有 level不能为空指针
      level_size_ = 32;
      head_ = new Node(INT_MIN, level_size_);

      srand (time(NULL));
    }

    ~Skiplist() {
      delete head_;
      for (int i = 0; i < recycle_.size(); i++) {
        delete recycle_[i];
      }
      recycle_.clear();
    }

    bool search(int target) {
      Node* cur = head_;
      for (int i = max_level_ - 1; i >= 0; i--) {
        while (cur->next[i] != nullptr) {
          if (cur->val <= target && target < cur->next[i]->val ) {
            break;
          }
          cur = cur->next[i];
        }
        if (cur->val == target) {
          return true;
        }
      }
      return false;
    }

    void add(int num) {
      // level 高的少一点，
      int current_level_size = randomlevel() + 1;
      Node* new_node = new Node(num, current_level_size);

      if (size_ == 0) {

        for (int i = current_level_size - 1; i >= 0; i--) {
          head_->next[i] = new_node;
        }
      } else {
        Node* cur = head_;
        for (int i = max_level_ - 1; i >= 0; i--) {
          while (cur->next[i] != nullptr) {
            if (cur->val <= num && num < cur->next[i]->val ) {
              break;
            }
            cur = cur->next[i];
          }
          if (i < current_level_size) {
//             交换
             Node* tmp = cur->next[i];
             cur->next[i] = new_node;
             new_node->next[i] = tmp;
          }
        }
      }
      if (current_level_size > max_level_) {
        for (int i = max_level_; i < current_level_size; i++) {
          head_->next[i] = new_node;
        }
        max_level_ = current_level_size;
      }
      size_++;
    }

    bool erase(int num) {
      Node* cur = head_;
      bool flag = false;
      Node* target = nullptr;
      for (int i = max_level_ - 1; i >= 0; i--) {
        while (cur->next[i] != nullptr) {
          if (cur->val < num && num <= cur->next[i]->val ) {
            break;
          }
          cur = cur->next[i];
        }
        if (cur->next[i] != nullptr && cur->next[i]->val == num) {
          target = cur->next[i];
          flag = true;
        }
        if (flag && cur->next[i] == target) {
          cur->next[i] = target->next[i];
        }
      }
      if (flag) {
        delete target;
        recycle_.push_back(target);
        size_--;
      }

      return flag;
    }

private:
    int randomlevel() {
      int level = 0;
      for (int i = 0; i < level_size_; i++) {
        level = i;
        if ((rand() % 100) / 100.0 >= p_) {
          break;
        }
      }
      return level;
    }

   Node* head_;
   int level_size_ = -1;
   int size_ = 0;
   float p_ = 0.25;
   int max_level_ = 0;
   vector<Node*> recycle_;
};