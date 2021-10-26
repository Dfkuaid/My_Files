#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

inline ll random(ll x) {
    return 1ll * rand() * rand() % x;
}

int main() {
    srand((unsigned)time(NULL));
    freopen("in.txt", "w", stdout);
    int t = random(100) + 1;
    printf("%d\n", t);
    for (int i = 1; i <= t; ++ i) {
        int n = random(100000) + 1, d = random(100000) + 1;
        printf("%d %d %d\n", d, n, random(n) + 1);
        for (int j = 1; j <= n; ++ j) {
            int r = random(d) + 1; int l = random(r) + 1;
            printf("%d %d %d\n", random(3e5) + 1, l, r);
        }
    }
    return 0;
}   
