/*
 * UVa11059 accept
 */
#include <iostream>

using namespace std;

long long solve(int len, int *arr) {
    long long result = 0;
    for (int start = 0; start < len; start++) {
        for (int end = start; end < len; end++) {
            long long temp = 1;
            int temp_start = start;
            while (temp_start <= end) {
                temp *= arr[temp_start++];
            }
            result = temp > result ? temp : result;
        }
    }
    return result;
}

int main(void) {
    long long result = 0;
    int n = 0;
    int arr[20];
    int cases = 0;
    while (scanf("%d", &n) > 0) {
        for (int i = 0; i < n; i++) {
            scanf("%d", arr+i);
        }
        result = solve(n, arr);
        printf("Case #%d: The maximum product is %lld.\n\n", ++cases, result);
    }
}
