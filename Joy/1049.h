#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

class Solution {
public:
// 背包问题 转化成 diff = sum(k[i] * stones[i]), k属于 1 ｜ -1， 最终 diff 最小(令 diff > 0)
//  diff = pos - (sum - pos) = 2 * pos - sum > 0 , pos > sum / 2
// 也就是说 pos 大于 sum/2, 同时尽可能小
//         neg 小于 sum/ 2, 同时尽可能大。
    int lastStoneWeightII(vector<int>& stones) {
      int stone_sum = 0;
      for (auto stone: stones) {
        stone_sum += stone;
      }

      int dp_size = stone_sum / 2 + 1;
      vector<vector<bool>> dp(2, vector<bool> (dp_size, false));
      dp[0][0] = true;
      dp[1][0] = true;

      for (int i = 0; i < stones.size(); i++) {
        int pre = i % 2;
        int post = (i + 1) % 2;

        for (int j = 1; j < dp_size; j++) {
          // 不加入这块石头
          dp[post][j] = dp[pre][j];
          // 加入 这块石头 到 负集合
          if (0 <= j - stones[i])  {
            dp[post][j] = dp[post][j] | dp[pre][j - stones[i]];
          }
        }
      }
      int final = stones.size() % 2;
      for (int j = dp_size - 1; j >= 0; j--) {
        if (dp[final][j]) {
          return stone_sum - 2 * j;
        }
      }
      return -1;
    }
};