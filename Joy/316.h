// 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。
// 需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。

// 示例 1：
//
//输入：s = "bcabc"
//输出："abc"
//示例 2：
//
//输入：s = "cbacdcbc"
//输出："acdb"
// 

//提示：
//
//1 <= s.length <= 104
//s 由小写英文字母组成
// https://leetcode-cn.com/problems/remove-duplicate-letters/
#include <string>
#include <set>
#include <ostream>
#include <stack>
using namespace std;
// 不断删除关键字符 即下降趋势字符
// 需要一个单调栈实现，这里用了 一个 string  代替, 所以会更快一点
// 对于序列来说，要么上升要么下降，上升的直接append, 下降的趋势需要一个个循环弹出不符合的字符。
// 其中注意的规则有：
//  如果是后续唯一的，则必须进，终止弹出，
//  如果是已经有的，则直接跳过
//    例如 abc-c的情况，可以直接跳出的
//    例如 abdbcbd例子中 abd-b的情况，
//        这里的一个优化，这种情况，b直接跳过，如果弹也可以，但是没有必要，无效操作，细节地方
class Solution {
public:
    string removeDuplicateLetters(string s) {
      std::vector<int> char_sets;
      char_sets.resize(26, 0);
      std::vector<bool> char_contrained_sets;
      char_contrained_sets.resize(26,0);
      int dup_cnt = 0;
      for (int i = 0; i < s.length(); i++) {
        char_sets[s[i] - 'a']++;
      }

      string res;
      for (int i = 0; i < 26; i++) {
        if (char_sets[i] > 0) {
          res.push_back(char_sets[i]);
        }
      }

      int ptr = -1;

      bool replace;

      // bcabc
      // b
      // bc
      // b
      // a
      for (int i = 0; i < s.length(); i++) {
        char_sets[s[i] - 'a']--;
        if (ptr == -1) {
          // 暂时空状 直接加进去
          res[++ptr] = s[i];
          char_contrained_sets[res[ptr] - 'a'] = true;
        } else if (char_contrained_sets[s[i] - 'a']) {
           // 之前的stack 已经 录入
        } else if ( res[ptr] > s[i] ) {
          // 有更小的，需要加入
          // 05432, 1
          while (ptr > -1 && res[ptr] > s[i]) {
            if (char_sets[res[ptr] - 'a'] == 0) {
              // 不能被替换
              break;
            }
            // 能被替换
            char_contrained_sets[res[ptr] - 'a'] = false;
            ptr--;
          }
          res[++ptr] = s[i];
          char_contrained_sets[res[ptr] - 'a'] = true;
        } else if (res[ptr] < s[i]) {
          res[++ptr] = s[i];
          char_contrained_sets[res[ptr] - 'a'] = true;
        }
      }
      return res;
    }
};