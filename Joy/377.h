
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//  不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数
// nums = [1,2,3], target = 4

// 组合背包问题， 重复采样， 同时带顺序
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
      vector<int> dp(target + 1, 0);
      dp[0] = 1;
      sort(nums.begin(), nums.end());
      // 1,2,3 - 4
      for (int j = 1; j <= target; j++) {
        for (int i = 0; i < nums.size(); i++) {
          if (j - nums[i] < 0 || dp[j - nums[i]] > INT_MAX - dp[j]) {
            break;
          }
          dp[j] += dp[j - nums[i]];
        }

      }
      return dp[target];
    }
};