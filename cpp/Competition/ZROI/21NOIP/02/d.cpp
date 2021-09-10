#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 3010;
const int M = 20000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

int n, m, MOD; ll f[N][N], g[N][N];
int fac[M], inv[M], invf[M];

inline int C(int a, int b) {
    if (a - b < MOD && MOD <= a) return 0;
    return 1ll * fac[a] * inv[b] % MOD * inv[a - b] % MOD;
}

signed main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d", &n, &MOD); m = 2 * n * n;
    fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i < M; ++ i)
	  if (i == MOD) fac[i] = fac[i - 1];
	  else fac[i] = 1ll * fac[i - 1] * i % MOD;
	for (int i = 2; i < M; ++ i)
      if (i >= MOD) inv[i] = inv[i - MOD];
	  else inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
	for (int i = 1; i < M; ++ i)
      inv[i] = 1ll * inv[i - 1] * inv[i] % MOD;
    f[1][0] = 1, g[n][n] = 1;
    for (int i = n; ~i; -- i)
      for (int j = Min(n - 1, i); ~j; -- j)
        g[i][j] = (g[i + 1][j] + g[i][j + 1]) % MOD;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j < i; ++ j) {
          int rest = 2 * n * (n - j) - i - j;
          if (j == i - 1) {
              if (i == n) {printf("%d", f[i][j]); return 0;}
              (f[i + 1][j + 1] += 1ll * f[i][j] * C(rest - 2, n << 1) % MOD * g[1][0] % MOD) %= MOD;
              for (int k = 1; k <= n; ++ k)
                (f[i + 1][j + 1] += 1ll * f[i][j] * C(rest - k - 2, (n << 1) - k) % MOD * g[k][0] % MOD) %= MOD;
          } else (f[i][j + 1] += 1ll * f[i][j] * C(rest - 1, n << 1) % MOD * g[1][0] % MOD) %= MOD;
          if (i < n) (f[i + 1][j] += f[i][j]) %= MOD;
        }
    } 
    return 0;
}