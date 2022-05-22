//
// 几乎每一个人都用 乘法表。但是你能在乘法表中快速找到第k小的数字吗？
//
//  给定高度m 、宽度n 的一张 m * n的乘法表，以及正整数k，你需要返回表中第k 小的数字。
// m∗log(mn)
// 对于每个点 可以计算他是第几大的
class Solution {
public:
    // 表里面 的 range [1, m * n], 但是可能会存在 1 <= i <= m*n, 但是不在表里，同时候又是第k小的数
    int findKthNumber(int m, int n, int k) {
      int l = 1;
      int r = m * n;
      int mid = -1;
      if (m > n) {
        // 交换
        m = m + n;
        n = m - n;
        m = m - n;
      };
      while (l < r) {
        mid = l + (r - l ) / 2;
        if (!enough(mid, m , n, k)) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }

      return l;
    }

    bool enough(int mid, int m, int n, int k) {
      int count = 0;
      for (int i = 1; i <= m; i++) {
        count += std::min(mid / i , n);
      }
      return count >= k;
    }
};