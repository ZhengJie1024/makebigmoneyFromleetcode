#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

// 整数数组 nums 和一个整数 target
// 数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
// 运算结果等于 target 的不同 表达式 的数目。

// k 找到 k个数 ， 和 为 target的组合数量
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
      int nums_sum = 0;
      for (auto num:nums) {
        nums_sum += num;
      }

      // target = pos + -(nums_sum - pos)
      // 2 pos   = ( target + nums_sum ) / 2
      // target =  -(nums_sum - neg) + neg = 2 * neg - nums_sum
      int new_target = abs(target + nums_sum);
      if (new_target % 2 == 1) {return 0;}
      new_target /= 2;

      // 找到能够加出 new_target 的组合数量

      vector<int> dp(new_target + 1, 0);
      dp[0] = 1;

      for (int i = 0; i < nums.size(); i++) {
        for (int j = new_target ; j >= 0; j--) {
          if (j - nums[i] >= 0) {
            dp[j] =  dp[j] + dp[j - nums[i]] ;
          }
        }

      }

      return dp[new_target];
    }
};