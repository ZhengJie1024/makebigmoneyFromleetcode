//进阶:
//
//如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
//如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？

#include <queue>

// 本质上是需要维护一个能够一直插入并且保持顺序的结构 -> 平衡二叉
// 这里是求中位数，所有可以利用优先队列，其他的分位点也可以，基于 qmax qmin来求

// 踩坑 : priotity_queue 里面的 less 后， top是最大的，也就是 最大堆

class MedianFinder {
public:
    // less<int> 是最大
    priority_queue<int, vector<int>, less<int>> qmin;
    priority_queue<int, vector<int>, greater<int>> qmax;

    MedianFinder() {
    }

    void addNum(int num) {
      // qmin qmax
      if (qmin.empty() && qmax.empty()) {
        qmin.push(num);
        return;
      }
      if (num > qmin.top()) {
        qmax.push(num);
        if (qmin.size() < qmax.size()) {
          qmin.push(qmax.top());
          qmax.pop();
        }
      } else {
        qmin.push(num);
        if (qmin.size() > qmax.size() + 1) {
          qmax.push(qmin.top());
          qmin.pop();
        }
      }
    }

    double findMedian() {
      if ((qmin.size() + qmax.size()) % 2 == 0) {
        return (qmin.top() + qmax.top()) / 2.0;
      } else {
        return qmin.top();
      }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */