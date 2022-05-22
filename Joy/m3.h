
// 2(2(b)2(c))2(2(a))2(2(c))
// bbccbbccaaaa
// tree 后序遍历
// for in [2(2(b)2(c)), 2(2(a))]
//   stack, split
//   s = 2 * f(input = 2(b)2(c)) +  2 * f(input = 2(a)) + 2 * f(input = 2(c))
// o(m), n 叶子节点, m全部节点，n = 3， 多叉数

// 1(2(2(b)2(c))2(2(a))2(2(c)))

#include <string>
#include <vector>
class m3 {
public:
  bool s(std::string& res, std::string& input ) {
    res_ = &res;
    dfs(res, 0, input.size());
  }

private:
  bool dfs(std::string& input, int begin, int end) {
    // split 节点
    std::vector<int > splits;
    int left_count = 0;
    for (int i = begin; i <= end - 1; i++) {
      if (input[i] == '(') {
        left_count++;
      } else if (input[i] == ')') {
        left_count--;
      } else {
        continue;
      }
      if (left_count == 0) {
        // 把 '）' push 进入 split 节点中， 用于后续划分
        splits.push_back(i);
      }
    }
    // 如果只有一个，说明可以是叶子节点

    // 多个继续迭代


  }

  std::string* res_;

};
