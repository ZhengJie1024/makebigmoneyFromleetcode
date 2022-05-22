//给你一个由若干括号和字母组成的字符串 s ，删除最小数量的无效括号，使得输入的字符串有效。
//
//返回所有可能的结果。答案可以按 任意顺序 返回。
//
// 提示：
//1 <= s.length <= 25
//s 由小写英文字母以及括号 '(' 和 ')' 组成
//s 中至多含 20 个括号

// 输入：s = "()())()"
//输出：["(())()","()()()"]

// 输入：s = "(a)())()"
//输出：["(a())()","(a)()()"]
// 输入：s = ")("
//输出：[""]


#include <string>
#include <set>
using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
      // 第一次 遍历
      res.clear();
      int cnt = 0;
      int left_cnt = 0;
      int right_cnt = 0;
      for (int i = 0; i < s.length(); i++) {
        if (s.at(i) != '(' && s.at(i) != ')') {
          continue;
        }
        cnt += 1;
        if (s.at(i) == '(') {
          left_cnt++;
        } else {
          if (left_cnt > 0 ) {
            left_cnt--;
          } else {
            right_cnt++;
          }
        }
      }

      if (left_cnt + right_cnt == 0) {
        return vector<string>{s};
      }

      string tmp_s;

      dfs(s, tmp_s,0, 0, left_cnt, right_cnt);

      vector<string> res_tmp;
      for (auto i = res.begin(); i != res.end(); i++) {
        res_tmp.push_back((*i));
      }
      return res_tmp;
    }

    void dfs(const string& s, string& tmp_s, int tmp_left, int cur_index, int left_cnt, int right_cnt) {
      if (tmp_left < 0) {
        return;
      }
      if (cur_index == s.length()) {
        if (tmp_left == 0 && left_cnt == 0 && right_cnt == 0) {
          res.insert(tmp_s);
        }
        return;
      }
      if (s[cur_index] == '(') {
        if (left_cnt > 0 ) {
          // 删除
          dfs(s, tmp_s, tmp_left, cur_index + 1, left_cnt - 1, right_cnt);
        }
        // 保留 左节点
        tmp_s += s[cur_index];
        dfs(s, tmp_s, tmp_left + 1, cur_index + 1 , left_cnt,  right_cnt);
        tmp_s.erase(tmp_s.end() - 1);

      } else if (s[cur_index] == ')') {
        if (right_cnt > 0) {
          // 删除 有节点
          dfs(s, tmp_s, tmp_left, cur_index + 1, left_cnt , right_cnt - 1 );
        }
        // 保留  节点
        tmp_s += s[cur_index];
        dfs(s, tmp_s, tmp_left - 1 , cur_index + 1 , left_cnt , right_cnt );
        tmp_s.erase(tmp_s.end() - 1 );
      } else {
        tmp_s += s[cur_index];
        dfs(s, tmp_s, tmp_left, cur_index + 1, left_cnt, right_cnt);
        tmp_s.erase(tmp_s.end() - 1 );
      }
    }

private:

    set<string> res;
};