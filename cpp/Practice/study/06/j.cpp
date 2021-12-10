#define LOCAL
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
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

template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}

int n, a[N], f[N], g[N], h[N], ans;

inline void reset() {g[0] = h[0] = ans = -INF;}

void MAIN() {
    for (int i = 1; i <= n; ++ i) read(a[i]); reset();
    for (int i = 1; i <= n; ++ i) f[i] = Max(a[i], f[i - 1] + a[i]);
    for (int i = 1; i <= n; ++ i) g[i] = Max(g[i - 1], f[i]);
    for (int i = 1; i <= n; ++ i) h[i] = Max(h[i - 1], g[i - 1]) + a[i];
    for (int i = 1; i <= n; ++ i) ans = Max(ans, h[i]);
    printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); while (n) MAIN(), read(n); return 0;
}
