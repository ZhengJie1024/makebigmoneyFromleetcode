#include <vector>
#include <math.h>
#include <queue>

using namespace std;

//  力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 基于归并的非递归解决思路（非递归： 从底向上，逐层归并）
class Solution {
public:

    vector<int> countSmaller(vector<int>& nums) {
      // res init
      res_.resize(nums.size(), 0);

      // index init
      index_.resize(nums.size(), 0);
      for (int i = 0;i < nums.size(); i++) {
        index_[i] = i;
      }

      // NOTE(zhengjie) 智能指针指向局部变量，可能会导致函数结束提前释放。等到智能指针自己释放的时候会触发空指针异常
      nums_ = &nums;

      // tmp inedx init
      tmp_.resize(nums.size(), 0);

      int step = 0;
      int last_step = 0;
      int b = 0;
      int e = 0;
      int m = 0;

      for (int i = 0 ; i < log2((double) nums.size()) ; i++) {
        last_step = step;
        // NOTE 这部分出错了，二叉树递归每一层步长 不是 2的倍数
        step = pow(2, i+1);
        b = 0;
        while (b < nums.size()) {
          e = min(b + step,  (int) nums.size());
          if (i != 0) {
            m = min(b + last_step,  (int) nums.size());
          } else {
            m = b + (e - b ) / 2;
          }
          partition(b, e, m);
          b = b + step;
        }
      }

      nums_ = nullptr;
      return std::move(res_);
    }

    // [b, e)
    void partition(int b, int e, int m) {
      if (b + 1 ==  e) {
        // 只有一个情况返回
        return ;
      }

      // [0,4) m = 0+(4-0)/2 = 2
      // [0,2) m = 0 + (2 - 0) /2 = 1
//      int m = b + (e - b ) / 2;

      // merge;
      // 两个的情况
      // 如果是 归并，这部分 只需要排序 融合两个序列即刻
      // 这里需要考虑 对前序 的 res的num做改变，后序的 res 的num不需要变更

      for (int i = b ; i < m; i++) {
        // 比target 小的 第一个
        int count_num = BinarySearch(m, e, nums_->at(index_[i])) ;
        count_num = e - count_num ;
        res_[index_[i]] += count_num;
      }

      // ERROR 双指针 合并 两个序列, 合并到 index上 。这种思路有问题
      // NOTE(zhengjie) 双指针有逻辑问题
      int i = b;
      int j = m;
      int c = b;
      while (i < m && j < e) {
        if (nums_->at(index_[i]) < nums_->at(index_[j])) {
          tmp_[c] = index_[j];
          j++;
        } else {
          tmp_[c] = index_[i];
          i++;
        }
        c++;
      }
      while (i < m) {
        tmp_[c] = index_[i];
        i++;
        c++;
      }
      while (j < e) {
        tmp_[c] = index_[j];
        j++;
        c++;
      }
      for (int i = b;i < e;i++) {
        index_[i] = tmp_[i];
      }
    }

    int BinarySearch(int begin, int end, int target_num);

    vector<int>* nums_;
    vector<int> res_;
    vector<int> index_;
    vector<int> tmp_;

};

inline int Solution::BinarySearch(int begin, int end, int target_num) {
  // 二分查找 比target 小的 第一个

  if (begin + 1 >= end) {
    return nums_->at(index_[begin]) >= target_num ? end : begin;
  }

  int b = begin;
  int e = end;
  int m = b + (e - b )/2;;
  while (m < e) {
    if (nums_->at(index_[m]) >= target_num) {
      b = m + 1; // NOTE(zhengjie), 这里一般需要考虑，不然二分会死循环
    } else {
      // n[m] < target_num
      if (m == begin) {
        return m;
      } else if (nums_->at(index_[m-1]) >= target_num) {
        return m;
      } else {
        e = m;
      }
    }
    m = b + (e - b )/2;;
  }
  return end;
}