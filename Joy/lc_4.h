#include <iostream>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <string>
#include <cfloat>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
      std::vector<int>* snums = nullptr;
      std::vector<int>* lnums = nullptr;
      if (nums1.size() > nums2.size()) {
        snums = &nums2;
        lnums = &nums1;
      } else {
        snums = &nums1;
        lnums = &nums2;
      }

      int n = nums1.size() + nums2.size();
      int seg_sise = (n + 1) / 2;

      int left_seg = 0;
      int right_seg = snums->size();
      int medium_seg = 0;
      int long_seg = 0;
      double res = DBL_MIN;
      int left_max = INT_MIN;
      int right_min = INT_MAX;
      while (left_seg <= right_seg) {
        medium_seg =left_seg + (right_seg - left_seg ) / 2;// 便向左边
        std::cout << "\n" << "left_seg = " << left_seg << " medium_seg = " << medium_seg << " right_seg = " << right_seg;
        // judgemet
        long_seg = seg_sise - medium_seg;
        // 是否
        int short_index = medium_seg - 1;
        int long_index = long_seg - 1;
        // short_index 大于 long_index + 1, right = medium
        // long_index 大于 short_index + 1， left = medium + 1
        std::cout << " short_index = " << short_index << " long_index = " << long_index ;
        if (long_index + 1 < lnums->size() && short_index >= 0 &&  snums->at(short_index) > lnums->at(long_index + 1)) {
          right_seg = medium_seg;
          continue;
        }
        if (short_index + 1 < snums->size() && long_index >= 0 &&  lnums->at(long_index) > snums->at(short_index + 1)) {
          left_seg = medium_seg + 1;
          continue;
        }
        std::cout << "\n" << "ans ";

        if (short_index >= 0 && short_index < snums->size()) {
          left_max =  snums->at(short_index);
        }
        if (long_index >= 0 && long_index < lnums->size()) {
          left_max =  std::max(lnums->at(long_index), left_max);
        }
        if (long_index + 1 < lnums->size()) {
          right_min = lnums->at(long_index + 1);
        }
        if (short_index + 1 < snums->size()) {
          right_min = std::min(snums->at(short_index + 1), right_min);
        }

        if (n % 2 == 0 ) {
          res = (right_min + left_max) / 2.0 ;
        } else {
          res = left_max;
        }
        return res;
      }
      return res;
    }
};