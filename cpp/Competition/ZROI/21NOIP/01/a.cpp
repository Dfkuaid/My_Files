#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int M = 10010;
const int N = 10000010;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

ll n, p, mu[N], nprm[N], prm[N], pcnt;
ll ans, phi[N], f[N], mi[N], inv[N];

inline ll fpow(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) (res *= a) %= MOD;
        (a *= a) %= MOD; b >>= 1;
    }
    return res;
}

void euler(int x) {
    phi[1] = 1; f[1] = 1;
    for (int i = 2; i <= x; i ++) {
        if (!nprm[i]) {
            prm[++ pcnt] = i, mi[i] = fpow(i, p);
            phi[i] = i - 1, f[i] = phi[i] * mi[i] % MOD;
        }
        for (int j = 1; j <= pcnt; j ++) {
            if (prm[j] * i > x) break;
            nprm[prm[j] * i] = true;
            if (i % prm[j]) {
                f[i * prm[j]] = f[i] * f[prm[j]] % MOD;
                phi[i * prm[j]] = phi[i] * (prm[j] - 1) % MOD;
            } else {
                phi[i * prm[j]] = phi[i] * prm[j] % MOD;
                f[i * prm[j]] = f[i] * prm[j] % MOD * mi[prm[j]] % MOD;
                break;
            }
        }
    }
}

int main() {
    scanf("%lld%lld", &n, &p);
    euler(n); inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; ++ i) 
      inv[i] = ((MOD - MOD / i) * inv[MOD % i]) % MOD;
    for (int i = 2; i <= n; ++ i)
      (ans += inv[i - 1] * (f[i] - phi[i]) % MOD + MOD) %= MOD;
    printf("%lld", (ans + p % MOD + MOD) % MOD);
    return 0;
}