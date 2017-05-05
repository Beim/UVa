/*
 * uva514
 */
#include <iostream>
#include <vector>
// #include <cstdio>
// #include "./util.hpp"
// #include <algorithm>
#include <queue>
#include <map>
#include <stack>

using namespace std;

int judge (queue<int> &input, queue<int> &output) {
  stack<int> st;
  queue<int> possible;
  queue<int> reality(output);
  while (!input.empty()) {
    int x = input.front();
    input.pop();
    if (x == output.front()) {
      output.pop();
      possible.push(x);
    }
    else {
      st.push(x);
    }
  }
  while (!st.empty()) {
    possible.push(st.top());
    st.pop();
  }
  return possible == reality;
}

int main () {
  int iarr[]{1, 2, 3, 4, 5};
  int oarr[]{5, 4, 3, 2, 1};
  queue<int> input;
  queue<int> output;
  for (int i = 0; i < 5; i++) {
    input.push(iarr[i]);
    output.push(oarr[i]);
  }
  if (judge(input, output)) {
    cout << "ok\n";
  }
  else {
    cout << "no\n";
  }
  return 0;
}
