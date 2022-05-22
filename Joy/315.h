#include <vector>

using namespace std;

// titile : 计算右侧小于当前元素的个数
// 给定一个整数数组 nums，按要求返回一个新数组 counts。数组 counts 有该性质： counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量。
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
// 输入：nums = [5,2,6,1]
    //输出：[2,1,1,0]
    //解释：
    //5 的右侧有 2 个更小的元素 (2 和 1)
    //2 的右侧仅有 1 个更小的元素 (1)
    //6 的右侧有 1 个更小的元素 (1)
    //1 的右侧有 0 个更小的元素
    //

    // [5,2,6,1]
    // [1,0,1,0]
    // [2,1,1,0]

// 基于归并的解决思路，耗时间 打败10%用户，800ms, 需要优化归并的算法
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

      partition(0, nums.size());
      return std::move(res_);
    }

    // [b, e)
    void partition(int b, int e) {
      if (b + 1 ==  e) {
        // 只有一个情况返回
        return ;
      }

      // [0,4) m = 0+(4-0)/2 = 2
      // [0,2) m = 0 + (2 - 0) /2 = 1
      int m = b + (e - b ) / 2;
      // [0,2)
      partition(b, m);
      // [2,4)
      partition(m, e);

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