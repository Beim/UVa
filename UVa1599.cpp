/*
 * uva1599 超时
 */
#include <iostream>
// #include <sstream>
#include <vector>
// #include <cstdio>
#include <algorithm>
#include <queue>
// #include <map>
// #include <stack>
// #include <utility>
#include <cstring>
// #include <cstdlib>

// #include "./util.hpp"

using namespace std;

void bfs(vector<vector<int> > &graph, vector<int> &distance) {
  int n = graph.size() - 1;
  vector<int> visited(n+1, 0);
  queue<int> q;
  q.push(n);
  visited[n] = -1;
  distance[n] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = 1; v <= n; v++) {
      if (graph[v][u] > 0 && !visited[v]) {
        visited[v] = -1;
        distance[v] = distance[u] + 1;
        q.push(v);
      }
    }
    visited[u] = 1;
  }
}

void solve(vector<vector<int> > &graph, vector<int> &path) {
  int n = graph.size() - 1;
  vector<int> distance(n+1, -1);
  bfs(graph, distance);

  int dis = distance[1];
  vector<int> prev(n+1, -1);
  vector<int> vnodes;
  vector<int> visited(n+1, 0);
  prev[1] = 0;
  vnodes.push_back(1);
  visited[1] = 1;

  while (dis--) {
    int least = -1;
    for (auto it = vnodes.begin(); it != vnodes.end(); it++) {
      int u = *it;
      for (int v = 1; v <= n; v++) {
        if (v != u && graph[u][v] > 0 && distance[v] == distance[u] - 1) {
          if (least == -1) {
            least = v;
          }
          else {
            least = graph[u][v] < graph[u][least] ? v : least;
          }
        }
      }
    }
    vector<int> new_vnodes;
    for (auto it = vnodes.begin(); it != vnodes.end(); it++) {
      int u = *it;
      for (int v = 1; v <= n; v++) {
        if (v != u && graph[u][v] > 0 && distance[v] == distance[u] - 1) {
          // if (graph[u][v] == graph[u][least] && !visited[v]) {
          if (graph[u][v] == graph[u][least]) {
            if (!visited[v]) {
              new_vnodes.push_back(v);
              visited[v] = 1;
              prev[v] = u;
            }
            else {
              int prev_best = prev[v];
              if (graph[u][v] < graph[prev_best][v]) {
                prev[v] = u;
              }
            }
            // printf("dis = %d, prev[%d] = %d\n", dis, v, u);
          }
        }
      }
    }
    vnodes.swap(new_vnodes);
    /*
    cout << "vnodes: ";
    for (auto item : vnodes) {
      cout << item << " ";
    }
    cout << endl;
    */
  }
  /*
  for (auto item : prev) {
    cout << item << " ";
  }
  cout << endl;
  */
  int pn = n;
  while (prev[pn] > 0) {
    pn = prev[pn];
    path.push_back(pn);
  }
  reverse(path.begin(), path.end());
}

int main (void) {
  int n;
  int m;
  while (cin >> n >> m) {
    vector<vector<int> > graph(n+1, vector<int>(n+1, -1));
    vector<int> path;
    int ai, bi, ci;
    while (m--) {
      cin >> ai >> bi >> ci;
      graph[ai][bi] = ci;
      graph[bi][ai] = ci;
    }
    solve(graph, path);
    /*
    for (auto item : path) {
      cout << item << " ";
    }
    cout << endl;
    */
    cout << path.size() << endl;
    for (auto it = path.begin(); it != path.end(); it++) {
      if (it+1 != path.end()) {
        cout << graph[*it][*(it+1)] << " ";
      }
      else {
        cout << graph[*it][n];
      }
    }
    cout << endl;
  }
  return 0;
}
