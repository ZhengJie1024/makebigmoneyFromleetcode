#include <unordered_map>
#include <stack>
#include <stdlib.h>

using namespace std;

class FreqStack {
public:

    FreqStack() {
      freq2s_.clear();
      val2freq_.clear();
    }

    ~FreqStack() {
      val2freq_.clear();
      for (auto v2f : freq2s_) {
        delete v2f.second;
      }
      freq2s_.clear();
    }

    // 将一个整数 val 压入栈顶
    void push(int val) {
      if (val2freq_.count(val) > 0) {
        val2freq_[val] += 1;
      } else {
        val2freq_[val] = 1;
      }

      if (val2freq_[val] > max_freq_) {
        max_freq_ = val2freq_[val];
      }

      if (freq2s_.count(val2freq_[val]) > 0) {
        freq2s_[val2freq_[val]]->push(val);
      } else {
        freq2s_[val2freq_[val]] = new stack<int>();
        freq2s_[val2freq_[val]]->push(val);
      }
    }

    int pop() {
      if (max_freq_ <= 0) {
        return -1;
      }

      int res_val = freq2s_[max_freq_]->top();
      val2freq_[res_val]--;
      freq2s_[max_freq_]->pop();
      if (freq2s_[max_freq_]->empty()) {
        delete freq2s_[max_freq_];
        freq2s_.erase(max_freq_);
        max_freq_--;
      }
      return res_val;
    }

private:
    unordered_map<int, stack<int>*> freq2s_;
    unordered_map<int, int> val2freq_;
    int max_freq_ = 0;
};
