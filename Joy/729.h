#include <vector>
#include <stack>
#include <iostream>
using namespace std;
// [[], [10, 20], [15, 25], [20, 30]]

class SegNode {
  public:
    explicit SegNode(long l , long r) : l_(l), r_(r) {
      avaliable = true;
      left_ = nullptr;
      right_ = nullptr;
      need_up = false;
    }

    SegNode* left() {
      if (left_ == nullptr) {
        left_ = new SegNode(l_, mid());
      }
      return left_;
    }

    SegNode* right() {
      if (right_ == nullptr) {
        right_ = new SegNode(mid(), r_);
      }
      return right_;
    }

    // 10,20  15,25 true
    bool query(long start, long end) {
      lazy_create();
      if (start <= l_ && r_ <= end) {
        return avaliable;
      }

      bool res = true;
      if (start <  mid()) {
        res &= left()->query(start, end);
      }

      if (mid() < end) {
        res &= right()->query(start, end);
      }
      return res;
    }

    void lazy_create() {
      if (need_up) {
        left()->need_up = true;
        right()->need_up = true;
        avaliable = false;
        need_up = false;
      }
    }

    void update(long start, long end) {
      if (start <= l_ && r_ <= end) {
        avaliable = false;
        need_up = true;
        return ;
      }
      lazy_create();

      if (start < mid()) {
        left()->update(start, end);
      }

      if (mid() < end) {
        right()->update(start, end);
      }
      // push up
      avaliable = right()->avaliable && left()->avaliable;
    }

  private:
    int mid() {
      return l_ + (r_ - l_) / 2;
    }

    // 左闭右开
    long l_;
    long r_;
    SegNode* left_;
    SegNode* right_;
    bool avaliable;
    bool need_up;
};

class MyCalendar {
public:
    MyCalendar() {
      root_ = new SegNode(0, 10e9);
    }

    bool book(int start, int end) {
      if (root_->query(start, end)) {
        root_->update(start, end);
        return true;
      }
      return false;
    }

private:
    SegNode* root_;
};
