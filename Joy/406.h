#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class Solution {
public:
// 从低往高
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
      sort(people.begin(), people.end(), [] (const vector<int>& u, const vector<int>& v) {
          return (u[0] < v[0]) || (u[0] == v[0] && u[1] >= v[1]);
      });

      vector<vector<int>> res(people.size(), vector<int>(2, -1));

      for (auto& p : people) {
        int idx = p[1];
        for (int i = 0; i < res.size(); i++) {
          if (res[i][0] != -1 ) {
            continue;
          }
          if (idx == 0) {
            res[i][0] = p[0];
            res[i][1] = p[1];
          }
          idx--;
        }
      }
      return res;
    }

    // vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    //     sort(people.begin(), people.end(), [] (const vector<int>& u, const vector<int>& v) {
    //         return (u[0] > v[0]) || (u[0] == v[0] && u[1] <= v[1]);
    //     });

    //     vector<vector<int>> res;

    //     for (auto& p : people) {
    //         int idx = p[1];
    //         res.insert(res.begin() + idx, p);

    //     }
    //     return res;
    // }
};