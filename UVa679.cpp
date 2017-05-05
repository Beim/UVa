/*
 * UVa679.cpp
 */
#include <iostream>
// #include <vector>
// #include <cstdio>
// #include <algorithm>
// #include <queue>
// #include <map>
// #include <stack>
// #include <utility>
#include <cstring>

// #include "./util.hpp"

using namespace std;

const int maxd = 20;
int tree[1<<maxd];

int get_id (int depth, int num) {
  int max_num = 1 << depth;
  // vector<int> tree(max_num);
  memset(tree, 0, max_num * sizeof(int));
  int pos;
  while (num--) {
    pos = 1;
    while (2 * pos < max_num) {
      if (tree[pos] == 1) { // go right
        tree[pos] = 0;
        pos = 2 * pos + 1;
      }
      else { // go left
        tree[pos] = 1;
        pos = 2 * pos;
      }
    } 
  }
  return pos;
}

int get_id_1 (int depth, int num) {
  int k = 1;
  for (int i = 0; i < depth - 1; i++) {
    if (num % 2) {
      k = k * 2;
      num = (num + 1) / 2;
    }
    else {
      k = k * 2 + 1;
      num = num / 2;
    }
  }
  return k;
}


int main () {
  int cases;
  cin >> cases;
  while (1) {
    int D, I;
    cin >> D;
    if (D == -1) break;
    cin >> I;
    cout << get_id_1(D, I) << endl;
  }
  return 0;
}
