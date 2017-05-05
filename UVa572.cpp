/*
 * uva572
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

const int maxn = 100 + 5;

char pic[maxn][maxn];
int idx[maxn][maxn];
int m, n;

void dfs (int row, int col) {
  if (row < 0 || col < 0 || row >= m || col >= n) return;
  if (idx[row][col] == 1 || pic[row][col] != '@') return;
  idx[row][col] = 1;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i != 0 || j != 0)
        dfs(row + i, col + j);
    }
  }

}

int main () {
  while (scanf("%d%d", &m, &n) == 2 && m && n) {
    for (int i = 0; i < m; i++) {
      scanf("%s", pic[i]);
    }
    memset(idx, 0, sizeof(idx));
    int count = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (idx[i][j] != 1 && pic[i][j] == '@') {
          dfs(i, j);
          count++;
        }
      }
    }
    cout << count << endl;
  }
  return 0;
}
