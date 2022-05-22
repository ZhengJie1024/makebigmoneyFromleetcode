#include <math.h>
#include <algorithm>
#include <iostream>
class Solution {
public:
    int getStep(long cur, long n) {
      long last = cur;
      int res = 0;
      while (cur <= n) {
        res += std::min(last, n) - cur + 1;
        cur *= 10;
        last = last * 10 + 9;
      }
      return res;
    }

    int findKthNumber(int n, int k) {
// 分桶 计算 1，2，3，4，5，6，7，8，9 开头的多少个
      long cur = 1;

      int res = cur;
      while (k != 0) {
        int step = getStep(cur, n);
        res = cur;
        if (step < k) {
          k = k - step;
          cur++;
        } else {
          // step > k, 在当前节点
          cur *= 10;
          k--;
        }
      }
      return res;
    }
};