/*
 * uva10562
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_N 210

char buf[MAX_N][MAX_N];
int n;

void dfs(int r, int c) {
  printf("%c(", buf[r][c]);
  if (r+1 < n && buf[r+1][c] == '|') {
    int i = c;
    while (i-1 >= 0 && buf[r+2][i-1] == '-')
      i--;
    while (buf[r+2][i] == '-' && buf[r+3][i] != '\0') {
      if (!isspace(buf[r+3][i]))
        dfs(r+3, i);
      i++;
    }
  }
  printf(")");
}

int main(void) {
  FILE *stream = stdin;
  int cases;
  fscanf(stream, "%d", &cases);
  fgetc(stream);
  while (cases--) {
    n = 0;
    while (1) {
      fgets(buf[n], MAX_N, stream);
      if (buf[n][0] == '#') break;
      else n++;
    }
    printf("(");
    if (n) {
      for (int i = 0; i < (int)strlen(buf[0]); i++) {
        if (buf[0][i] != ' ') {
          dfs(0, i);
          break;
        }
      }
    }
    printf(")\n");
  }
  return 0;
}
