#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

inline int random(int x) {
    return (1ll * rand() * rand() % x) + 1;
}

int main() {
    srand((unsigned)time(NULL));
    freopen("in.txt", "w", stdout);
    int n = 50000, q = 50000;
    printf("%d\n", n);
    for (int i = 1; i <= n; ++ i)
      printf("%d\n", random(50000));
    for (int i = 2; i <= n; ++ i)
      printf("%d %d\n", i, random(i - 1));
    printf("%d\n", q);
    for (int i = 1; i <= q; ++ i)
      printf("%d %d\n", random(n), random(n));
    return 0;
}