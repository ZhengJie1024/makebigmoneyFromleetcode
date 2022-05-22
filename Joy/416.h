#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;
//给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
class Solution {
public:
// 01背包问题
// 转化 成 能否找到 sum(kx) = nums
    bool canPartition(vector<int>& nums) {
      int sum_nums = 0;
      for (int i : nums) {
        sum_nums += i;
      }
      if (sum_nums % 2 == 1) {return false;}
      int target = sum_nums / 2;
      vector<vector<bool>> dp(2, vector<bool>(target + 1, false));
      // 能否组成
      dp[0][0] = true;
      dp[1][0] = true;

      for (int i = 0; i < nums.size(); i++) {
        int pre = i % 2;
        int post = (i + 1) % 2;

        for (int j = 1; j <= target; j++) {
          dp[post][j] = dp[pre][j];
          if (j - nums[i] >= 0) {
            dp[post][j] = dp[post][j] | dp[pre][j - nums[i]];
          }
        }
      }
      int final = nums.size() % 2;
      return dp[final][target];
    }
};