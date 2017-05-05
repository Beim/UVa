/*
 * UVa 129 accept
 */

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

int n;
int L;
int cnt = 0;
int S[80];

int dfs(int cur) {
    if (cnt++ == n) {
        int len = 0;
        for (int i = 0; i < cur; i++) {
            if (len && len%64 == 0)
                printf("\n");
            else if (len && len%4 == 0) 
                printf(" ");
            printf("%c", 'A' + S[i]);
            len++;
        }
        printf("\n%d\n", len);
        return 0;
    }
    for (int i = 0; i < L; i++) {
        S[cur] = i;
        int ok = 1;
        for (int j = 1; j*2 <= cur+1; j++) {
            int equal = 1;
            for (int k = 0; k < j; k++) {
                if (S[cur-k] != S[cur-k-j]) {
                    equal = 0;
                    break;
                }
            }
            if (equal) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            if (!dfs(cur+1)) return 0;
        }
    }
    return 1;
}

int main() {
    while (scanf("%d %d", &n, &L) && n && L) {
        cnt = 0;
        dfs(0);
    }
}
