#include "1206.h"
#include <math.h>
#include <iostream>
#include <vector>

// nn train
int main() {
  // ["Skiplist","add","add","add","search","add","search","erase","erase","search"]
  //              [[],[1],[2],[3],[0],[4],[1],[0],[1],[1]]
  Skiplist s;
  s.add(1);
  s.add(2);
  s.add(3);

  s.search(0);
//
  s.add(40);
  s.search(1);
//  s.erase(40);
  s.erase(1);
  s.search(1);

  s.add(1);
  s.add(2);
  s.add(3);

  std::cout << " res = done " << s.search(40);;
  return 0;
}

