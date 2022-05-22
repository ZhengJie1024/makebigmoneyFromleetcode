//进阶:
//
//如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
//如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？

#include <set>

// 本质上是需要维护一个能够一直插入并且保持顺序的结构 -> 平衡二叉
// 维护一个 multiset 元素 利用双指针记录
// multiset支持重复，而set会去重
// insert 是 稳定加到后面， 默认是 less, 所以 插入时候放右边； 如果是greater
class MedianFinder {
    std::multiset<int> nums;
    std::multiset<int>::iterator left, right;

public:
    MedianFinder() : left(nums.end()), right(nums.end()) {}


    // 变成 奇数， 只走一个指针，向节点走，
    //    大等于right, right 不动， left往右走
    //    小于left, right 往左走
    // left <= num < right , 中间走

    // 变成 偶数， 只走一个指针，向节点走
    //    大等于right, right 往右走， left 不动
    //    小于left, right 不动, left, 往左走

    void addNum(int num) {
      const size_t n = nums.size();

      nums.insert(num);
      if (!n) {
        left = right = nums.begin();
      } else if (n & 1) {
        // 之前是奇数，变成 偶数
        if (num < *left) {
          left--;
        } else {
          right++;
        }
      } else {
        // 之前是偶数，变成 奇数
        if (num > *left && num < *right) {
          left++;
          right--;
        } else if (num >= *right) {
          left++;
        } else {
          right--;
          left = right;
        }
      }
    }

    double findMedian() {
      return (*left + *right) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */