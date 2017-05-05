/*
 * uva816(Accepted)
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

struct Node {
  int r;
  int c;
  int dir;
  Node(int r = 0, int c = 0, int dir = 0) : r(r), c(c), dir(dir) {}
};

const char *dirs = "NESW";
const char *turns = "FLR";

int dir_id(char c) {
  return strchr(dirs, c) - dirs;
}
int turn_id(char c) {
  return strchr(turns, c) - turns;
}

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

Node walk(Node &u, int turn) {
  int dir = u.dir;
  if (turn == 1) dir = (dir + 3) % 4;
  else if (turn == 2) dir = (dir + 1 ) % 4;
  return Node(u.r + dr[dir], u.c + dc[dir], dir);
}

int has_age[10][10][4][3];
string sample_name;
int en_r, en_c, out_r, out_c;
char en_dir;
int r1, c1, dir1;

int d[10][10][4];
Node p[10][10][4];

void print_ans(Node u) {
  vector<Node> nodes;
  while (true) {
    nodes.push_back(u);
    if (d[u.r][u.c][u.dir] == 0) break;
    u = p[u.r][u.c][u.dir];
  }
  nodes.push_back(Node(en_r, en_c, dir_id(en_dir)));
  int cnt = 0;
  for (auto it = nodes.end() - 1; it != nodes.begin() - 1; it--) {
    if (cnt % 10 == 0) printf(" ");
    printf(" (%d,%d)", it->r, it->c);
    if (++cnt % 10 == 0) printf("\n");
  }
  if (nodes.size() % 10 != 0) printf("\n");
}

int inside(int r, int c) {
  if (r > 0 && c > 0 && r <= 9 && c <= 9)
    return 1;
  else
    return 0;
}

void solve() {
  queue<Node> q;
  memset(d, -1, sizeof(d));
  Node u(r1, c1, dir1);
  d[u.r][u.c][u.dir] = 0;
  q.push(u);
  while (!q.empty()) {
    Node u = q.front();
    q.pop();
    if (u.r == out_r && u.c == out_c) {
      printf("%s\n", sample_name.c_str());
      print_ans(u);
      return;
    }
    for (int i = 0; i < 3; i++) {
      Node v = walk(u, i);
      if (has_age[u.r][u.c][u.dir][i] && inside(v.r, v.c)
          && d[v.r][v.c][v.dir] < 0) {
        d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
        p[v.r][v.c][v.dir] = u;
        q.push(v);
      }
    }
  }
  printf("%s\n", sample_name.c_str());
  printf("  No Solution Possible\n");
}

int main () {
  while (cin >> sample_name && sample_name != "END") {
    memset(has_age, 0, sizeof(has_age));
    cin >> en_r >> en_c >> en_dir >> out_r >> out_c;
    dir1 = dir_id(en_dir);
    r1 = en_r + dr[dir1];
    c1 = en_c + dc[dir1];
    int r, c;
    string s;
    while (cin >> r && r != 0) {
      cin >> c;
      while (cin >> s && s[0] != '*') {
        int dir = dir_id(s[0]);
        for (auto it = s.begin() + 1; it != s.end(); it++) {
          int turn = turn_id(*it);
          has_age[r][c][dir][turn] = 1;
        }
      }
    }
    solve();
  }
}
