#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

class Solution {
public:
// 折半 搜索
// 搜索n长度，选中i个里面和的顺序， 2^n + n*m*logm
// 搜索剩余的n长度，在节点最后 查询，找到 (n - i） 组里面 最大 且不超过 nums.size() / 2的, 2^n
// 搜索最后的，
// diff = pos - (sum - pos)
//   pos > sum / 2
    int minimumDifference(vector<int>& nums) {
      int n = nums.size() / 2;
      vector<vector<int>> cnt_sort(n + 1);

      // 2^n种 可能性
      for (int i = 0; i < 1 << n; i++) {
        int sum = 0;
        int cnt = 0;
        for (int j = 0; j < n ; j++) {
          if (i >> j & 1) {
            cnt += 1;
            sum += nums[j];
          } else {
            sum += -nums[j];
          }
        }
        cnt_sort[cnt].push_back(sum);
      }

      for (int i = 1; i <= n; i++ ) {
        sort(cnt_sort[i].begin(), cnt_sort[i].end());
      }

      // 2^n种 可能性
      int res = INT_MAX;
      for (int i = 0; i < 1 << n; i++) {
        int sum = 0;
        int cnt = 0;
        for (int j = 0; j < n ; j++) {
          if (i >> j & 1) {
            cnt += 1;
            sum += nums[j + n];
          } else {
            sum += -nums[j + n];
          }
        }

        // 二分 找最小， z= min(abs(a + b))
        auto& sort_nums =  cnt_sort[n - cnt];
        auto it=lower_bound(sort_nums.begin(),sort_nums.end(),-sum);
        if(it!=sort_nums.end()) {
          res=min(res, sum + *it);
        }
      }
      return res;
    }
};