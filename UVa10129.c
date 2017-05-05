/*
 * uva10129
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 100000
#define CHAR_N 26
#define MAX_STR_N 1010

#define INIT_ARR(s) do { memset(s, 0, sizeof(s)); } while(0)

char s[MAX_STR_N];
int in[CHAR_N];
int out[CHAR_N];
int graph[CHAR_N][CHAR_N];
int visit[CHAR_N];
int showed[CHAR_N];

void dfs(int u) {
  visit[u] = 1;
  for (int v = 0; v < CHAR_N; v++) {
    if (!visit[v] && graph[u][v]) {
      dfs(v);
    }
  }
}

int main() {
  int edges = 0;
  int cases = 0;
  scanf("%d", &cases);
  while (cases--) {
    INIT_ARR(in);
    INIT_ARR(out);
    INIT_ARR(graph);
    INIT_ARR(visit);
    INIT_ARR(showed);
    scanf("%d", &edges);
    getchar();
    int start_visit = 0;
    // 读入边
    for (int i = 0; i < edges; i++) {
      fgets(s, MAX_STR_N, stdin);
      int len = strlen(s);
      int k1 = s[0] - 'a';
      int k2 = s[len - 2] - 'a';
      out[k1]++;
      in[k2]++;
      graph[k1][k2] = 1;
      start_visit = k1;
      showed[k1] = 1;
      showed[k2] = 1;
    }

    // 判断是否所有点的入度等于出度，
    // 或者有一个入度比出度大1,一个出度比入度大1
    int fail = 0;
    // 入度-出度 == 1 的个数
    int k1 = 0;
    // 出度 - 入度 == 1 的个数
    int k2 = 0;
    for (int i = 0; i < CHAR_N; i++) {
      in[i] = in[i] - out[i];
      if (in[i] == 1) {
        k1++;
      }
      else if (in[i] == -1) {
        k2++;
        start_visit = i;
      }
      // 1 -1 0 之外，无法构成欧拉回路
      else if (in[i] != 0) {
        fail = 1;
        break;
      }
    }
    if (!fail) {
      fail = !((k1 + k2 == 0) || (k1 == 1 && k2 == 1));
    }
    if (!fail) {
      dfs(start_visit);
      for (int i = 0; i < CHAR_N; i++) {
        if (showed[i] && !visit[i])
          fail = 1;
      }
    }
    if (fail) {
      printf("The door cannot be opened.\n");
    }
    else {
      printf("Ordering is possible.\n");
    }
  }
}
