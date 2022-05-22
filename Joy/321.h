//给定长度分别为 m 和 n 的两个数组，其元素由 0-9 构成，表示两个自然数各位上的数字。
// 现在从这两个数组中选出 k (k <= m + n) 个数字拼接成一个新的数，要求从同一个数组中取出的数字保持其在原数组中的相对顺序。
//
//求满足该条件的最大数。结果返回一个表示该最大数的长度为 k 的数组。
//
//说明: 请尽可能地优化你算法的时间和空间复杂度。
//
//示例 1:
//
//输入:
//nums1 = [3, 4, 6, 5]
//nums2 = [9, 1, 2, 5, 8, 3]
//k = 5
//输出:
//[9, 8, 6, 5, 3]
//示例 2:
//
//输入:
//nums1 = [6, 7]
//nums2 = [6, 0, 4]
//k = 5
//输出:
//[6, 7, 6, 0, 4]
//示例 3:
//
//输入:
//nums1 = [3, 9]
//nums2 = [8, 9]
//k = 3
//输出:
//[9, 8, 9]
//
// 解法：
//  由于是选k个，所以可以转化成 从 m中抽取 x, 从 n中抽取 y, 然后xy merge, 这种方式有k中可能序列，再去取其中最大
//  k (m + n + k)
// 如何从 m个里面选出 x个数，能够最大， 6, 7, 6, 8, 6, 8, 4, 3 ->


#include <string>
#include <set>
#include <ostream>
using namespace std;


class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
      int m = nums1.size(), n = nums2.size();
      vector<int> maxSubsequence(k, 0);
      int start = max(0, k - n), end = min(k, m);
      for (int i = start; i <= end; i++) {
        vector<int> subsequence1(MaxSubsequence(nums1, i));
        vector<int> subsequence2(MaxSubsequence(nums2, k - i));
        vector<int> curMaxSubsequence(merge(subsequence1, subsequence2));
        if (compare(curMaxSubsequence, 0, maxSubsequence, 0) > 0) {
          maxSubsequence.swap(curMaxSubsequence);
        }
      }
      return maxSubsequence;
    }

    vector<int> MaxSubsequence(vector<int>& nums, int k) {
      int length = nums.size();
      vector<int> stack(k, 0);
      int top = -1;
      int remain = length - k;
      for (int i = 0; i < length; i++) {
        int num = nums[i];
        while (top >= 0 && stack[top] < num && remain > 0) {
          top--;
          remain--;
        }
        if (top < k - 1) {
          stack[++top] = num;
        } else {
          remain--;
        }
      }
      return stack;
    }


    // todo
    // 对比 两个 vector diff， 可以是变长的vector
    int compare(vector<int>& subsequence1, int index1, vector<int>& subsequence2, int index2) {
      int x = subsequence1.size(), y = subsequence2.size();
      while (index1 < x && index2 < y) {
        int difference = subsequence1[index1] - subsequence2[index2];
        if (difference != 0) {
          return difference;
        }
        index1++;
        index2++;
      }
      return (x - index1) - (y - index2);
    }

    // todo 这里效率更低
    // 402那种 删除逻辑会更优， 添加的情况下得，保证在满足约束的情况下是最大的
    // 删除的时候，只需要最近的一个对比即可
    void MaxSubsequenceV2 (const vector<int>& nums, vector<int>& cur, int k){
      cur.clear();
      cur.reserve(k);


      for(int i = 0; i < nums.size(); i++) {
         int j = cur.size() - 1;
         // 2-0+0 >=2
         // 2 - 1 + 1 >=2
         // todo
         while (j  >= 0 && (nums.size() - i + cur.size() > k)) {
           if (cur[j] < nums[i]) {
             cur.pop_back();
           }
           j--;
         }
        if (cur.size() < k ) {
          cur.push_back(nums[i]);
          continue;
        }
      }
    }

    // todo
    // 这里 merge 需要考虑 两个相等的时候 改选哪一个：
      // 01 02 应该先消耗02的0
    vector<int> merge(vector<int>& subsequence1, vector<int>& subsequence2) {
      int x = subsequence1.size(), y = subsequence2.size();
      if (x == 0) {
        return subsequence2;
      }
      if (y == 0) {
        return subsequence1;
      }
      int mergeLength = x + y;
      vector<int> merged(mergeLength);
      int index1 = 0, index2 = 0;
      for (int i = 0; i < mergeLength; i++) {
        if (compare(subsequence1, index1, subsequence2, index2) > 0) {
          merged[i] = subsequence1[index1++];
        } else {
          merged[i] = subsequence2[index2++];
        }
      }
      return merged;
    }

};