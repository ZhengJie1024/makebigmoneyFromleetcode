#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isDigit(char t) {
      return 0 <= t - '0' && t - '0' < 10;
    }
    bool isSmallDigit(char t) {
      return 0 <= t - 'a' && t - 'a' < 26;
    }


    string getString(string s) {
      if (s.empty() || s.size() <= 1) {
        return s;
      }

      int digit = 0;
      string pre_s = "";
      int pos_begin = -1; // 第一个 [ 的位子
      // 处理 前缀
      for (int i = 0; i < s.size(); i++) {

        if (s[i] == '[') {
          pos_begin = i;
          break;
        }
        if (isSmallDigit(s[i])) {
          pre_s+=s[i];
        }
        if (isDigit(s[i])) {
          digit = digit * 10 + (s[i] - '0');
        }
      }

      if (pos_begin == -1) {
        return pre_s;
      }

      // 找到对应的 ‘]’
      int stack_cnt = 1;
      int pos_end = -1; // 第一个 ] 的位子
      for (int i = pos_begin + 1; i < s.size(); i++) {
        if (s[i] == '[') {stack_cnt++;}
        if (s[i] == ']') {stack_cnt--;}
        if (stack_cnt == 0) {
          pos_end = i;
          break;
        }
      }

      string pos = getString(s.substr(pos_begin + 1, pos_end - pos_begin - 1));
      string res = "";
      for (int i = 0 ; i < digit ; i++) {
        res += pos;
      }

      res = pre_s + res;
      if (pos_end != s.size() - 1 ) {
        res += getString(s.substr(pos_end + 1, s.size() - (pos_end + 1)));
      }
      return res;
    }

    string decodeString(string s) {
      return getString(s);
    }
};