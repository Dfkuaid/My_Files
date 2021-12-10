#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 15;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}

int w[N][N], f[1 << 12][N], n, m, reach[1 << 12], ans;

inline void print_binary(int x, char c) {
    for (int i = 15; i >= 0; -- i) printf("%d", (x >> i) & 1); putchar(c);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    memset(w, 0x3f, sizeof w); memset(f, 0x3f, sizeof f);
    read(n), read(m); ans = INF;
    for (int i = 1, x = 0, y = 0, l = 0; i <= m; ++ i) {
        read(x), read(y), read(l);
        w[x - 1][y - 1] = Min(w[x - 1][y - 1], l);
        w[y - 1][x - 1] = Min(w[y - 1][x - 1], l);
    }
    for (int i = 0; i < n; ++ i) w[i][i] = 0;
    for (int s = 0; s < 1 << n; ++ s)
      for (int i = 0; i < n; ++ i) if ((s >> i) & 1)
        for (int j = 0; j < n; ++ j) if (w[i][j] != INF)
          reach[s] |= (1 << j);
    for (int i = 0; i < n; ++ i) f[1 << i][1] = 0;
    for (int s0 = 1; s0 < 1 << n; ++ s0)
      for (int s1 = s0 - 1; s1; s1 = (s1 - 1) & s0)
        if(reach[s1] | s0 == reach[s1]) {
            ll sum = 0; int s2 = s1 ^ s0;
            for (int i = 0, mn = INF; i < n; ++ i, mn = INF) if ((s2 >> i) & 1) {
                for (int j = 0; j < n; ++ j) if ((s1 >> j) & 1) mn = Min(mn, w[i][j]);
                sum += mn;
            }
            for (int i = 2; i <= n; ++ i) if (f[s1][i - 1] != INF)
              f[s0][i] = Min(1ll * f[s0][i], 1ll * f[s1][i - 1] + 1ll * (i - 1) * sum);
        }
    for (int i = 1; i <= n; ++ i) ans = Min(ans, f[(1 << n) - 1][i]);
    printf("%d", ans); return 0;
}
