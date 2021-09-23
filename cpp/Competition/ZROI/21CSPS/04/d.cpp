#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 510;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

int n; ll C[N][N], f[N][N];

inline void init_C(int x) {
    for (int i = 0; i <= x; ++ i) C[i][0] = C[i][i] = 1;
    for (int i = 1; i <= x; ++ i)
      for (int j = 1; j < i; ++ j)
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
}

ll fpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) (res *= a) %= MOD;
        (a *= a) %= MOD, b >>= 1;
    }
    return res;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d", &n); init_C(n);
    for (int i = 1; i <= n; ++ i)
      for (int j = 0; j <= n; ++ j) {
          if (j >= i) f[i][j] = fpow(i - 1, j - i) * C[j][i] % MOD;
          for (int k = 0; k <= j; ++ k) {
              if (k == i) continue;
              (f[i][j] += f[i - 1][j - k] * C[j][k] % MOD) %= MOD;
          }
      }
    printf("%lld", f[n][n]);
    return 0;
}