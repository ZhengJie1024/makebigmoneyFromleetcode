//
// Created by zhengjie on 2022-05-09.
//

// a [2,3,5,7]
// b [2,3,2*2, 5, 2 * 3]
// n

#include <vector>

class m2 {
  int s(int n , std::vector<int> a) {
    std::vector<int> b;
    b.push_back(1);

    for (int i = 1 ; i <= n ;i++) {
      // a [2,3,5,7]
      // b [2,3,2*2], n=3
      // n = 4
      // a [2,3,5(i),7]
      // b [1(5) ,2-> (3),3 ->(2) ,2*2(j),5]
      // n = 5
      // a [2(i),3,5,7]
      // b [1(j7) ,2-> (3),3(j) ->(6) ,2*2->8,5, 6]
      // n * (bsize + a_size) ,j = m, i = asize

      int tmp_i = a.size() - 1;
      int res = INT_MAX;
      int init_j = 0;
      // find init_j

      // fill b vector
      for (int j = init_j;j < b.size() ;j++) {
           while (tmp_i >= 0) {
             int tmp_res = a[tmp_i] * b[j];
             if (tmp_res > b.back()) {
               res = std::min(res, tmp_res);
               tmp_i--;
             } else {
               // tmp_i <= b, 已经到边界，跳出 开始 j++
               break;
             }
           }
      }
      b.push_back(res);
    }

    return b[n];
  }
};

