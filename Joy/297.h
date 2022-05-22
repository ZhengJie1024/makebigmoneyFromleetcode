#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;
// 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
//
//完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

// 完全背包问题 可以重复采样
// 或者当成
class Solution {
public:
    int numSquares(int n) {
      int sqrt_n = sqrt(n);
      if (sqrt_n == n) {return 1;}

      vector<int > dp(n + 1, INT_MAX);
      dp[0] = 0;
      // 1, 2, 3
      // dp[n] = min(dp[n - i^2]) + 1;

      for (int i = 1; i <= sqrt_n; i++) {
        int pow_i = i * i;
        for (int j = 1; j <= n ; j++) {
          if (j - pow_i >=0 && dp[j - pow_i] != INT_MAX) {
            dp[j] = min(dp[j], dp[j - pow_i] + 1);
          }
        }
      }
      return dp[n];
    }
};