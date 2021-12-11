#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 20;
const int M = 1 << 16;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int f[M], g[M], h[M], n, e[N][N], bit[M];

inline void print_binary(int x, char c) {
    for (int i = 15; ~i; -- i) printf("%d", (x >> i) & 1); putchar(c);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); g[0] = 1; bit[1] = 0;
    for (int i = 0; i < n; ++ i)
      for (int j = 0; j < n; ++ j) read(e[i][j]);
    for (int i = 0; i < n; ++ i) bit[1 << i] = i;
    for (int s = 1; s < 1 << n; ++ s) {
        int lb = s & -s, x = s ^ lb, p = bit[lb], tmp = 1;
        for (int i = 0; i < n; ++ i) if ((x >> i) & 1)
          tmp = 1ll * tmp * (e[i][p] + 1) % MOD;
        g[s] = 1ll * g[x] * tmp % MOD;
    }
    for (int s = 0; s < 1 << n; ++ s) {
        int x = s ^ (s & -s); f[s] = g[s];
        for (int s1 = x; s1; s1 = (s1 - 1) & x)
          f[s] = (f[s] - 1ll * g[s1] * f[s ^ s1] % MOD + MOD) % MOD;
    }
    printf("%d", f[(1 << n) - 1]); return 0;
}
