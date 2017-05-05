/*
 * uva1572 不知为何过不了 = =  udebug没问题
 */
#include <iostream>
// #include <sstream>
// #include <vector>
// #include <cstdio>
// #include <algorithm>
// #include <queue>
// #include <map>
// #include <stack>
// #include <utility>
#include <cstring>
// #include <cstdlib>

// #include "./util.hpp"

using namespace std;

int graph[52][52];
int n;
char str[8];
int source[4];
int visited[52];

bool dfs(int u) {
  visited[u] = -1;
  for (int v = 0; v < 52; v++) {
    if (graph[u][v]) {
      if (visited[v] == -1) return false;
      else if (!visited[v] && !dfs(v)) return false;
    }
  }
  visited[u] = 1;
  return true;
}

bool topsort() {
  for (int i = 0; i < 52; i++) {
    if (!visited[i] && !dfs(i)) {
      return false;
    }
  }
  return true;
}

int ID(int x, int y) {
  return y == '+' ? (x-'A')*2+1 : (x-'A')*2;
}

int main (void) {
  ios::sync_with_stdio(false);
  while (1) {
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    n = 0;
    cin >> n;
    if (n <= 0)
      break;
    while (n-- && cin >> str) {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (i != j && str[i*2] != '0' && str[j*2] != '0') {
            int num1 = ID(str[i*2], str[i*2+1]) ^ 1;
            int num2 = ID(str[j*2], str[j*2+1]);
            graph[num1][num2] = 1;
          }
        }
      }
    }
    if (topsort()) {
      cout << "bounded\n";
    }
    else {
      cout << "unbounded\n";
    }
  }
  return 0;
}
