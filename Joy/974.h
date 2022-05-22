#include <vector>
using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
      int res = 0;
      vector<vector<int>> dp;
      dp.resize(2, vector<int>());
      dp[0].resize(2 * k - 1, 0);
      dp[1].resize(2 * k - 1, 0);

      for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < 2 * k - 1; j++) {
          int t = j + (- (k - 1));
          dp[i % 2][((t+nums[i]) % k) - (- (k - 1))] = dp[(i + 1) % 2 ][j];
        }
        res += dp[i % 2 ][ k - 1];
      }
      return res;
    }
};