#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <cfloat>

using namespace std;


class Solution {
public:
// 多次二分，遍历每个primes中数据，找到第一个大于 当前数 / primes[i]的历史数据， log(m) * n * m
    int nthSuperUglyNumber(int n, vector<int>& primes) {
      vector<int> res({1});
      vector<int> ptr(primes.size(), 0); // 初始化指向 0 位
      n--;
      while (n != 0) {
        //
        double min_value = DBL_MAX;
        for (int i = 0 ; i < primes.size() ; i++) {
          if (res[ptr[i]] < min_value / primes[i]) {
            min_value = res[ptr[i]] * primes[i];
          }
        }
        res.push_back(min_value);

        for (int i = 0 ; i < primes.size() ; i++) {
          while (res[ptr[i]] <= min_value / primes[i]) {
            ptr[i]++;
          }
        }

        n--;
      }
      for (int i = 0 ; i < res.size() ; i++) {
        std::cout << " idx = " << i + 1 << " value = " << res[i]  << "\n"  ;
      }
      return res[res.size() - 1];
    }
};