#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

// 完全背包问题，重复采样，不考虑顺序
class Solution {
public:
    int change(int amount, vector<int>& coins) {
      vector<int> dp(amount + 1, 0);

      dp[0] = 1;
      // 1,2,5
      for (auto coin : coins) {
        for (int i = 1; i <= amount; i++) {
          if (i - coin < 0 ) { continue;}
          dp[i] = dp[i] + dp[i - coin];
        }
      }
      return dp[amount];
    }

};