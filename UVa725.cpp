/*
 * UVa725 accept
 */
#include <iostream>
#include <cstring>

using namespace std;

int p[10];

int solve(int a, int b) {
    if (a > 98765) return 0;
    memset(p, 0, sizeof(p));
    if (b < 10000) p[0] = 1;
    while (a) {
        p[a%10] = 1;
        a /= 10;
    }
    while (b) {
        p[b%10] = 1;
        b /= 10;
    }
    int total = 0;
    for (int i = 0; i < 10; i++) {
        if (p[i]) total++;
    }
    return total == 10;
}

int main(void) {
    int n = 0;
    int m = 0;
    while (scanf("%d", &n) && n>0) {
        if (m++) printf("\n");
        int has_result = 0;
        for (int i = 1234; i < 99999; i++) {
            if (solve(i*n, i)) {
                printf("%d / %05d = %d\n", i*n, i, n);
                has_result = 1;
            }
        }
        if (!has_result) {
            printf("There are no solutions for %d.\n", n);
        }
    }
}
