#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1000010;
const ll MOD = 998244353;

char s[N]; int n; ll val[N], b[N], inv[N], f[N], h[N], g[N];

ll fpow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) (res *= x) %= MOD;
        y >>= 1, (x *= x) %= MOD;
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d%s", &n, s); b[0] = f[0] = g[0] = 1, val[0] = 0;
    for (int i = 1; i <= n; ++ i)
      val[i] = (val[i - 1] * 10 % MOD + s[i - 1] - '0') % MOD;
    for (int i = 1; i <= n; ++ i) b[i] = b[i - 1] * 10 % MOD;
    for (int i = 0; i <= n; ++ i) inv[i] = fpow(b[i], MOD - 2);
    for (int i = 1; i <= n; ++ i) {
        f[i] = (val[i] * g[i - 1] % MOD - b[i] * h[i - 1] % MOD + MOD) % MOD;
        g[i] = (g[i - 1] + f[i]) % MOD;
        h[i] = (h[i - 1] + val[i] * f[i] % MOD * inv[i] % MOD) % MOD;
    }
    printf("%lld", f[n]); return 0;
}
