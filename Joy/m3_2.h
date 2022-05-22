//
// Created by zhengjie on 2022-05-09.
//
// [ac, b, d, ee]
// acbe
// acbee
#include <string>
#include <unordered_set>
#include <vector>

// dp[i] = dp[j] && f(s[j+1:i]), o(n*n*1), word in dict
class m3_2 {
public:
    bool s(std::unordered_set<std::string>& dict, std::string& input ) {
      std::vector<bool> dp(input.size() + 1,false);
      dp[0] = true;
      for (int i = 1; i <= input.size() ; i++) {
        for (int j = 0; j <= i; j++) {
          std::string tmp(input.begin() + j + 1, input.begin() + i + 1);
          if (dp[j] && dict.count(tmp) > 0) {
            dp[j] = true;
            break;
          }
        }
      }
      return dp[input.size()];
    }
};
