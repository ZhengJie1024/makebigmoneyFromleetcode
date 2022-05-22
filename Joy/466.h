#include <vector>

class Solution {
public:
    int countDigitOne(int n) {
      // n =  123456709
      int ans = 0;
      long long mulk = 1;
      for (int k = 0;n > mulk;k++) {
        ans += (n/(mulk*10) * (mulk)) +  min(max(n % (mulk * 10) - mulk + 1, 0LL), mulk);
        mulk *= 10;
      }
      return ans;
    }
};
