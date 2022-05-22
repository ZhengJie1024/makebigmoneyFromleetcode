#include <vector>
using namespace std;
class Solution {
public:
    int search(vector<int>& nums, int target) {
      int res = -1;
      int l = 0;
      int r = nums.size();
      int m = 0;
      bool is_left = false;
      while (l < r) {
        m = l + (r - l ) / 2; // (0, 1) , 0 + 0 = 0
        if (target == nums[m]) {return m;}
        // 判断 m 处于 那边
        is_left = nums[m] > nums[nums.size() - 1];
        if (is_left) {
          if (target > nums[m]) {
            l = m + 1;
          } else if (nums[0] <= target) {
            r = m;
          } else {
            l = m + 1;
          }
        } else {
          if (target < nums[m]) {
            r = m;
          } else if (nums[nums.size() - 1 ] < target) {
            r = m;
          } else {
            l = m + 1;
          }
        }
      }
      return -1;
    }
};