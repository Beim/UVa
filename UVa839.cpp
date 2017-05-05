/*
 * uva839 
 */
#include <iostream>
// #include <sstream>
#include <vector>
// #include <cstdio>
// #include <algorithm>
#include <queue>
// #include <map>
// #include <stack>
// #include <utility>
#include <cstring>

// #include "./util.hpp"

using namespace std;

bool solution (int &num);
bool solution1 (int &num);

int main () {
  int cases;
  cin >> cases;
  while (cases--) {
    int num;
    if (solution1(num))
      cout << "YES\n";
    else
      cout << "NO\n";
    if (cases) 
      cout << endl;
  }
  return 0;
}

bool solution1 (int &num) {
  int W1, D1, W2, D2;
  bool b1 = true, b2 = true;
  cin >> W1 >> D1 >> W2 >> D2;
  if (!W1) b1 = solution1(W1);
  if (!W2) b2 = solution1(W2);
  num = W1 + W2;
  return b1 && b2 && (W1 * D1 == W2 * D2);
}

bool solution (int &num) {
  int Wl, Dl, Wr, Dr;
  cin >> Wl >> Dl >> Wr >> Dr;
  if (Wl == 0 || Wr == 0) {
    int flag = 1;
    int num1, num2;
    if (!solution(num1)) flag = 0;
    if (!solution(num2)) flag = 0;
    if (flag == 0) return false;
    num = num1 + num2;
    return Dl * num1 == Dr * num2;
  }
  else {
    num = Wl + Wr;
    return Dl * Wl == Dr * Wr;
  }
}
