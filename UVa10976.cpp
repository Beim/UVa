/*
 * UVa10976
 * accept
 */
#include <iostream>
#include <vector>
// #include <sstream>
// #include <vector>
// #include <cstdio>
// #include <algorithm>
// #include <queue>
// #include <map>
// #include <stack>
// #include <utility>
// #include <cstring>
// #include <cstdlib>

using namespace std;

struct Ans {
    int x;
    int y;
    Ans(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

void solve(int k, vector<Ans*> &varr) {
    int max = 2 * k;
    for (int y = k+1; y <= max; y++) {
        if ((k*y) % (y-k) == 0) {
            Ans *x = new Ans( (k*y)/(y-k), y );
            varr.push_back(x);
        }
    }
    printf("%lu\n", varr.size());
    for (Ans *ans : varr) {
        printf("1/%d = 1/%d + 1/%d\n", k, ans->x, ans->y);
    }
}

int main(void) {
    int k;
    vector<Ans*> varr;
    while (scanf("%d", &k) > 0) {
        varr.clear();
        solve(k, varr);
    }
}
