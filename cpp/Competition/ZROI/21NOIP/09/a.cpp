#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int M = 30;
const int N = 210;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, a[N], b[N], f[N][M], g[N][M], dp[N][M], tmp[M];

inline void madd(int &x, int y) {x = x + y < MOD ? x + y : x + y - MOD;}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++ i) read(a[i]), read(b[i]);
    for (int i = 1; i <= n; ++ i) {
        mset(f, 0); f[0][0] = 1, f[0][b[i] % m] += 1;
        for (int k = 1; (1 << k) <= a[i]; ++ k)
          for (int u = 0; u < m; ++ u)
            for (int v = 0; v < m; ++ v)
              madd(f[k][(u + v) % m], 1ll * f[k - 1][u] * f[k - 1][v] % MOD);
        g[i][0] = 1;
        for (int k = 0; k <= 31; ++ k) 
          if ((a[i] >> k) & 1) {
              for (int u = 0; u < m; ++ u) tmp[u] = 0;
              for (int u = 0; u < m; ++ u)
                for (int v = 0; v < m; ++ v)
                  madd(tmp[(u + v) % m], 1ll * g[i][u] * f[k][v] % MOD);
              for (int u = 0; u < m; ++ u) g[i][u] = tmp[u];
          }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++ i)
      for (int u = 0; u < m; ++ u)
        for (int v = 0; v < m; ++ v)
          madd(dp[i][(u + v) % m], 1ll * dp[i - 1][u] * g[i][v] % MOD);
    printf("%d", (dp[n][0] + MOD - 1) % MOD); return 0;
}
