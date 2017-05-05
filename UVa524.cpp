/*
 * UVa 524 accept
 */

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 47;

int n = 0;
int A[maxn];
int vis[maxn];
int isp[maxn*2];

int isPrime(int num) {
    int s = sqrt(num);
    if (num <= 1) return 0;
    for (int i = 2; i <= s; i++) {
        if (num%i == 0) 
            return 0;
    }
    return 1;
}

void print_arr(int *A) {
    for (int i = 0; i < n-1; i++) {
        printf("%d ", A[i]);
    }
    printf("%d\n", A[n-1]);
}

void dfs(int cur) {
    if (cur == n && isp[A[0] + A[n-1]]) {
        print_arr(A);
        return;
    }
    for (int i = 2; i <= n; i++) {
        if (!vis[i] && isp[i + A[cur-1]]) {
            A[cur] = i;
            vis[i] = 1;
            dfs(cur+1);
            vis[i] = 0;
        }
    }
}

int main() {
    for (int i = 1; i < maxn*2; i++) {
       isp[i] = isPrime(i); 
    }
    A[0] = 1;
    int cases = 0;
    scanf("%d", &n);
    while (++cases) {
        printf("Case %d:\n", cases);
        dfs(1);
        if (scanf("%d", &n) > 0) {
            printf("\n");
        }
        else {
            break;
        }
    }
}
