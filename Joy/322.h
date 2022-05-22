
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
// target = amount, 需要的最小的硬币数量
// 可以重复增加
    int coinChange(vector<int>& coins, int amount) {
      vector<int> dp(amount + 1, INT_MAX);
      // 凑足 i钱需要的最少硬币数量
      dp[0] = 0;

      for (int i = 0; i < coins.size(); i++) {
        int sigle_amount = coins[i];
        for (int j = 1; j <= amount; j++) {
          if (j - sigle_amount >= 0 && dp[j - sigle_amount] != INT_MAX ) {
              dp[j] = min(dp[j - sigle_amount] + 1, dp[j]);
          }
        }
      }

      if (dp[amount] == INT_MAX) {
        return -1;
      } else {
        return dp[amount];
      }
    }
};