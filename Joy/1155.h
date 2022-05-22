#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;
// 这里有 n 个一样的骰子，每个骰子上都有 k 个面，分别标号为 1 到 k 。
//
// 给定三个整数 n ,  k 和 target ，返回可能的方式(从总共 kn 种方式中)滚动骰子的数量，使正面朝上的数字之和等于 target 。
//
// 答案可能很大，你需要对 109 + 7 取模
//

// 1-k 背包问题
class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
      vector<int> dp(target + 1, 0);
      dp[0] = 1;
      for (int i = 1; i <= n ; i++ ) {
        // todo  这里 必须 j >= 0， i=2时候会把dp[0] = 0, 题目比较特殊
        for (int j = min(target, i * k); j >= 0; j--) {
          dp[j] = 0;
          for (int z = 1; z <= k; z++) {
            if (j - z < 0) {
              continue;
            }
            dp[j] = (dp[j - z] + dp[j]) % t;
          }
        }
      }
      return dp[target] ;
    }

private:
    int t = 1e9+7;
};