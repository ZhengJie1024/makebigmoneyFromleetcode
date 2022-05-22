#include <string>
#include <set>
#include <ostream>
#include <random>
using namespace std;

// 写一个在圆中产生均匀随机点的函数 randPoint 。
// 一个方法：
// 1. 转化成角函数形式，pro 0-360, r 0-R, 随机撒点转化成xy
      // Note : r 的 随机点 需要sqrt
// 2. 撒点正方形，判断是否超出去，拒绝采样 3 .14/ 4

// 变成均匀分布的通用思路：https://leetcode-cn.com/problems/generate-random-point-in-a-circle/solution/cong-01-jun-yun-fen-bu-wrapdao-ren-yi-fe-uk4t/
// 均匀分布的累计密度函数（cdf）: f(x) = x , x 属于 [0,1]
//   1. 拆分出独立的元素，例如这里的r, pro
//   2. 分别写出每个元素的累计分布， r cdf : g(x) = x^2,  如果是均匀，g(x) = f(y) = y, 能够看出 反函数关系，
//        所以 x = g(y)-1, x = y^0.5, y是随机采样出来的。


class Solution {
public:
    Solution(double radius, double x_center, double y_center) :radius_(radius), x_center_(x_center), y_center_(y_center) {};

    vector<double> randPoint() {
      std::vector<double> res;
      res.resize(2, 0.0);

      double r = sqrt(uni(rng)) * radius_;
      double pro = uni(rng) * 2 * M_PI;

      res[0] = x_center_ + r * cos(pro) ;
      res[1] = y_center_ + r * sin(pro) ;
      return std::move(res);
    }

private:
    double radius_ ;
    double x_center_;
    double y_center_;
    mt19937 rng{random_device{}()};
    uniform_real_distribution<double> uni{0, 1};
};