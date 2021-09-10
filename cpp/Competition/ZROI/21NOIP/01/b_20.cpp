#include <bits/stdc++.h>
#define int long long
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 10010;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

ll n, p, f[N], c[N][N];

inline void prework(ll x) {
    for (int i = 0; i <= x; ++ i)
      c[i][0] = 1, c[i][i] = 1;
    for (int i = 1; i <= x; ++ i)
      for (int j = 1; j < i; ++ j)
        c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
}

signed main() {
    scanf("%lld%lld", &n, &p);
    if (p == 0) {
        prework(n); f[1] = f[0] = 1;
        for (int i = 2; i <= n; ++ i)
          for (int j = 0; j < i; ++ j)
            (f[i] += c[i - 1][j] * f[j] % MOD * f[i - j - 1] % MOD) %= MOD;
    }
    printf("%lld", f[n]);
    return 0;
}