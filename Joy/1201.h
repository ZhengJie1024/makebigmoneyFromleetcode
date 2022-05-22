#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

class Solution {
public:
// 找到第n个能被 a|b|c整除的数据
// 简单的方法： 每个数据除一下
// 找到 （a*b*c）中的最大公倍数的，for循环去判断，可以节省很多无效的判断
// 容斥定理：
//      a|b|c = a + b + c - a*b - a*c - b*c + a*b*c
//       给定一个值，算出 多少个 丑数
//        小于 i 的 有多少个丑数：
//                      i/a + i / b + i / c - i / lcm(a*b) -  i / lcm(a*b) -  i / lcm(a*b) + i / lcm(a*b*c)
    long lcm(int a, int b, int c) {
      long a_b_lcm = lcm(a, b);
      return lcm(a_b_lcm, c);
    }

    long lcm(int a, int b) {

      return ((long) a * b / gcb(a, b) );
    }

    int gcb(int a, int b) {
      if (a%b == 0) {
        return b;
      } else {
        return gcb(b ,a%b);
      }
    }


    int nthUglyNumber(int n, int a, int b, int c) {

      int i = -1;
      const vector<long> array({a, b, c , lcm(a, b), lcm(c, b),lcm(a, c), lcm(a, b, c)});
      auto CountFunction = [&] (int m) {
          return m/array[0] + m / array[1] + m / array[2]
          - m / array[3] -  m / array[4] -  m / array[5]
          + m / array[6];
      };
      // ab = 435967306 ac = 673832934 bc = 73442282232513951 abc = 146884564465027902
      std::cout << " ab = " << lcm(a, b) << " ac = " << lcm(a, c) << " bc = " << lcm(c, b) << " abc = " << lcm(a, b, c);
      int right = INT_MAX;
      int left = 1;
      while (left + 1 != right) {
        i = left + (right - left ) / 2;
        int count = CountFunction(i);
        if (count < n) {
          left = i;
        } else {
          right = i;
        }
      }

      return i;
    }
};

//class Solution {
//public:
//    typedef long long ll;
//    // greatest common divisor 最大公约数
//    ll gcd(ll a, ll b) {
//      return b == 0 ? a : gcd(b, a % b);
//    }
//    // least common multiple 最小公倍数
//    ll lcm(ll a, ll b) {
//      return a * b / gcd(a, b);
//    }
//
//    int nthUglyNumber(int n, int a, int b, int c) {
//      ll ab = lcm(a, b), ac = lcm(a, c), bc = lcm(b, c);
//      ll abc = lcm(ab, c);
//      function<ll(ll)> uglyNumbersCount = [&](ll m) {
//          return m / a + m / b + m / c - m / ab - m / ac - m / bc + m / abc;
//      };
//
//      // ab = 435967306 ac = 673832934 bc = 73442282232513951 abc = 146884564465027902
//      std::cout << " ab = " << ab << " ac = " << ac << " bc = " << bc << " abc = " << abc;
//      ll countPerCycle = uglyNumbersCount(abc); // 一个最小公倍数周期内丑数个数
//      int cycles = n/countPerCycle; // n 包含多少个最小公倍数周期
//      // 搜索区间周期优化为 [abc*cycles, abc*(cycles+1)) 周期区间左闭右开
//      ll l = abc*cycles-1, r = abc*(cycles+1);
//      while (l+1 != r) {
//        ll mid = (l+r)>>1;
//        // 容斥原理：计算 cnt 为[1,mid]中的丑数个数
//        ll cnt = uglyNumbersCount(mid);
//        if (cnt < n) {
//          l = mid;
//        } else {
//          r = mid;
//        }
//      }
//      return (int)r;
//    }
//};