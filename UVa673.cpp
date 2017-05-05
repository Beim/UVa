/*
 * uva673
 */
#include <iostream>
// #include <sstream>
#include <vector>
// #include <cstdio>
#include <algorithm>
#include <queue>
// #include <map>
#include <stack>
// #include <utility>
#include <cstring>
// #include <cstdlib>

// #include "./util.hpp"

using namespace std;

int main (void) {
  int cases;
  scanf("%d", &cases);
  getchar();
  while (cases--) {
    stack<char> stk;
    char str[150];
    fgets(str, 150, stdin);
    for (auto it = begin(str); it != end(str); it++) {
      char c = *it;
      if (c == '\n') break;;
      if (c == '(' || c == '[') {
        stk.push(c);
      }
      else if (c == ')') {
        if (stk.empty() || stk.top() != '(') {
          stk.push('a');
          break;
        }
        else { // stk.top() == ')'
          stk.pop();
        }
      }
      else if (c == ']') {
        if (stk.empty() || stk.top() != '[') {
          stk.push('a');
          break;
        }
        else {
          stk.pop();
        }
      }
    }
    if (stk.empty()) {
      cout << "Yes\n";
    }
    else {
      cout << "No\n";
    }
  }
  return 0;
}
