#include <vector>
#include <stack>
#include <iostream>
using namespace std;

// 输入：
//["NumArray", "sumRange", "update", "sumRange"]
//[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
//输出：
//[null, 9, null, 8]

class NumArray {
public:
    NumArray(vector<int>& nums) {
      n = nums.size();
      initSegment(nums);
    }

    void update(int index, int val) {
      update(0, pow(2, level) - 1, 0, index , val);
    }

    int update(int left, int right, int node_idx, int index, int val) {
      if (left == right && index == left) {
        int tmp = segmentTree[node_idx];
        segmentTree[node_idx] = val;
        return val - tmp;
      }
      int mid = left + (right - left) / 2;
      int update_diff = 0;
      if (index <= mid ) {
        update_diff = update(left, mid, node_idx * 2 + 1, index, val);
        segmentTree[node_idx] += update_diff;
      } else if ( mid < index ) {
        update_diff = update(mid + 1, right, node_idx * 2 + 2, index, val);
        segmentTree[node_idx] += update_diff;
      }
      return update_diff;
    }

    int sumRange(int left, int right) {
      return sumRange(left, right, 0, pow(2, level) - 1, 0);
    }

    int sumRange(int left, int right, int node_l, int node_r, int node_idx) {
//      cout << " left = " << left << " right = " << right << " node_l = " << node_l << " node_r = " << node_r
//           << " node_idx = " << node_idx << "\n";
      if (left <= node_l && node_r <= right) {
        return segmentTree[node_idx];
      }
      if (right < node_l || node_r < left) {
        return 0;
      }
      // 1
      // 2
      int node_mid = node_l + (node_r - node_l) / 2;
      int res = 0;
      if (left <= node_mid) {
        // (0, 2, 0, 1, 1)
        // (0, 2, 2, 2, 5)
        res = sumRange(left, right, node_l, node_mid, node_idx * 2 + 1);

      }
      if (node_mid < right) {
        // (0, 2, 2, 3, 2)
        // (0, 2, 3, 3, 6)
        res += sumRange(left, right, node_mid + 1, node_r, node_idx * 2 + 2);
      }
      return res;
    }


    void print() {


       for (int i = 0; i < segmentTree.size() ; i++) {
         cout << " idx : " << i << " val = " <<  segmentTree[i];
       }
      cout << " level : " << level << " n = "<< n << " size = " << size << "\n";
    }

private:
    void initSegment(vector<int>& nums) {
      segmentTree.resize(4 * n, 0);
      // build segment true
      level = (int) log2(n) + 1;
      size = pow(2, level);
      for (int i = level; i >=0 ;i--) {
        int b = pow(2, i) - 1; // 3,  1
        int e = pow(2, i + 1) - 2; // 6,  2
        if (i == level) {
          for (int j = 0; j < n;j++) {
            segmentTree[j + b] = nums[j];
          }
        } else {
          //
          for (int j = b; j <= e;j++) {
            int tmp = 2*j;
            segmentTree[j] = segmentTree[tmp + 1] + segmentTree[tmp + 2];
          }
        }
      }
    }


    vector<int> segmentTree;
    int n;
    int size;
    int level;
};
