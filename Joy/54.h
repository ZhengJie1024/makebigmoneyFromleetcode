#include <vector>
#include <iostream>
using namespace std;

// 错误写法，这是lc的第二种解法思路，但是存在一些问题，对特定case无法解决，原因是 directions的规则遍历会漏掉
/// //

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
      vector<int> res;
      int row = matrix.size();
      if (row == 0) {
        return res;
      }
      int colums = matrix[0].size();
      if (colums == 0) {
        return res;
      }
      int n = min(row,colums);
      int level = (n + 1) / 2;
      auto begin_idx = make_pair<int, int>(0,0);

      vector<pair<int , int>> directions({make_pair<int , int>(0,1), make_pair<int , int>(1, 0), make_pair<int , int>(0, -1), make_pair<int , int>(-1, 0)});
      vector<pair<int , int>> thresholds({make_pair<int , int>(0, colums - 1), make_pair<int , int>(row - 1, colums - 1), make_pair<int , int>(row - 1,0), make_pair<int , int>(0,0)});
      for (int i = 0; i < level; i++) {
        // 遍历 一边
        auto cur_idx = begin_idx;
        for (int j = 0; j < 4; j++) {
          auto direction = directions[j];
          auto threshold = thresholds[j];
          do {
            if (abs(threshold.first - cur_idx.first) == i && abs(threshold.second - cur_idx.second) == i ) {
              break;
            }
            std::cout << " idx : " << cur_idx.first << "," << cur_idx.second << "\n";
            // res.push_back(matrix[cur_idx.first][cur_idx.second]);
            cur_idx.first += direction.first;
            cur_idx.second += direction.second;
          } while (cur_idx.first != begin_idx.first || cur_idx.second != begin_idx.second);
        }

        begin_idx.first++;
        begin_idx.second++;
      }
      return res;
    }
};