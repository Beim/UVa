/*
 * uva1103 (用例未完全通过)
 */
#include <iostream>
// #include <sstream>
#include <vector>
// #include <cstdio>
#include <algorithm>
#include <queue>
// #include <map>
#include <stack>
#include <utility>
#include <cstring>
#include <cstdlib>

// #include "./util.hpp"

using namespace std;

const int MAX_H = 200 + 5;
const int MAX_W = 50 + 5;
const int MAX_W_BIN = MAX_H * 4;

using beim_pair = pair<int, int>;

char origin[MAX_H][MAX_W];
int binary[MAX_H][MAX_W_BIN];
int hole[MAX_H][MAX_W_BIN];

int col, row, col_b;

void hex2bin (char hex, int *bin);
bool dfs_find_pic (int r, int c, int id);
bool dfs_find_hole (int r, int c, int id);
char hole2char (int count);

int main () {
  int cases = 0;
  while (scanf("%d%d", &row, &col) == 2 && col && row) {
    col_b = col * 4;
    cases++;
    memset(origin, 0, sizeof(origin));
    memset(binary, 0, sizeof(binary));
    memset(hole, 0, sizeof(hole));

    for (int i = 0; i < row; i++)
      scanf("%s", origin[i]);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        hex2bin(origin[i][j], &binary[i][j * 4]);

    int count = 1;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col_b; j++) {
        if (binary[i][j] == 1)
          dfs_find_pic(i, j, ++count);
      }
    }

    vector<char> ans;
    for (int p = 2; p <= count; p++) {
      int hole_count = 0;
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < col_b; j++) {
          if (binary[i][j] == p) {
            // printf("count = %d ,", count);
            // printf("cases = %d, p = %d, binary[i][j] = %d, i = %d, j = %d\n", cases, p, binary[i][j], i, j);
            for (int x = -1; x <= 1; x++) {
              for (int y = -1; y <= 1; y++) {
                int r1 = i + x, c1 = j + y;
                if (r1 < 0 || c1 < 0 || r1 >= row || c1 >= col_b) continue;
                if (hole[r1][c1] != 0) continue;
                if (binary[r1][c1] != 0) continue;
                if (dfs_find_hole(r1, c1, p))
                  hole_count++;
              }
            }
          }
        }
      }
      ans.push_back(hole2char(hole_count));
    }
    sort(ans.begin(), ans.end());
    printf("Case %d: ", cases);
    for (auto item : ans)
      cout << item;
    cout << endl;
  }
  return 0;
}
bool dfs_find_hole (int r, int c, int id) {
  // queue<beim_pair > q;
  stack<beim_pair> q;
  q.push(make_pair(r, c));
  while (!q.empty()) {
    beim_pair temp = q.top();
    q.pop();
    int r1 = temp.first;
    int c1 = temp.second;
    hole[r1][c1] = 1;
    // printf("r1 = %d, c1 = %d, binary[r1][c1] = %d, hole[r1][c1] = %d\n", r1, c1,
    //     binary[r1][c1], hole[r1][c1]);
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0) continue;
        int r2 = r1 + i, c2 = c1 + j;
        // r1, c1在边界
        if (r2 < 0 || c2 < 0 || r2 >= row || c2 >= col_b)
          return false;
        if (hole[r2][c2]) continue;
        // 像素点为空
        if (binary[r2][c2] == 0 && hole[r2][c2] == 0) {
          hole[r2][c2] = 1;
          q.push(make_pair(r2, c2));
        }
        else {
          // r1, c1在其他图案旁边
          if (binary[r2][c2] != id) 
            return false;
        }
      }
    }
  }
  return true;
}

char hole2char (int count) {
  switch (count) {
    case 1:
      return 'A';
    case 3:
      return 'J';
    case 5:
      return 'D';
    case 4:
      return 'S';
    case 0:
      return 'W';
    case 2:
      return 'K';
    default:
      return 'X';
  }
}

bool dfs_find_pic (int r, int c, int id) {
  if (r < 0 || c < 0 || r >= row || c >= col_b) return false;
  if (binary[r][c] != 1) return false;
  binary[r][c] = id;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      if (i == 0 || j == 0)
        dfs_find_pic(r + i, c + j, id);
    }
  }
  return true;
}

void hex2bin (char hex, int *bin) {
  char hexx[2] = {0};
  hexx[0] = hex;
  int num = strtol(hexx, NULL, 16);
  for (int i = 0; i < 4; i++) {
    bin[3 - i] = !!(num & (1 << i));
  }
}
