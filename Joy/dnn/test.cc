#include <vector>
#include <libs/stdc++.h>

//class TestCode {
//public:
//    int HandleModel(const int k, const std::vector<int>& price) {
//      int rk = std::min(k, (int)price.size() / 2);
//      std::vector<std::vector<int>> buys(price.size(), std::vector<int>(rk + 1, 0));
//      std::vector<std::vector<int>> sells(price.size(), std::vector<int>(rk + 1, 0));
//
//      // buys[i][j] = max(buys[i - 1][j], sells[i - 1][j] - price[i])
//      // sells[i][j] = max(sells[i - 1][j], buys[i - 1][j - 1] + price[i])
//      // buys[i][0]
//      // sells[i][0] = 0
//
//      for (int i = 0; i < price.size();i++) {
//        buys[i][0] = INT_MIN;
//        sells[i][0] = INT_MIN;
//      }
//      sells[0][0] = 0;
//      buys[0][0] = -price[0];
//      for (int i = 1; i < price.size(); i++) {
//        for (int j = 1; j <= k; j++) {
//
//        }
//      }
//
//    }
//};

