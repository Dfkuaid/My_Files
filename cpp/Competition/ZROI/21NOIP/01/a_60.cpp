#include <bits/stdc++.h>
#define ll long long
#define int long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int M = 10010;
const int N = 10000010;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

int n, p, nprm[N], prm[N], pcnt;
ll mi[M][M], mu[N], sum[M][M], ans, sum1[N];

inline ll fpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) (res *= a) %= MOD;
        (a *= a) %= MOD; b >>= 1;
    }
    return res;
}

void euler(int x) {
    mu[1] = 1;
    for (int i = 2; i <= x; i ++) {
        if (!nprm[i]) prm[++ pcnt] = i, mu[i] = -1;
        for (int j = 1; j <= pcnt; j ++) {
            if (prm[j] * i > x) break;
            nprm[prm[j] * i] = true;
            if (i % prm[j]) mu[i * prm[j]] = -mu[i];
            else break;
        }
    }
}

signed main() {
    scanf("%lld%lld", &n, &p); euler(n);
    if (p == 1) {
        for (int i = 1; i <= n; ++ i)
          sum1[i] = (sum1[i - 1] + i) % MOD;
        for (int d = 1; d <= n; ++ d) {
            ans += mu[d] * sum1[n / d] % MOD;
            (ans += MOD) %= MOD;
        }
          
    } else {
        for (int i = 1; i <= n; ++ i)
          for (int j = 0; j <= p; ++ j) {
            mi[i][j] = fpow(i, j) % MOD;
            sum[i][j] = (sum[i - 1][j] + mi[i][j]) % MOD;
          }
        for (int i = 1; i <= p; ++ i)
          for (int d = 1; d <= n; ++ d) {
              ans += mu[d] * mi[d][i - 1] % MOD * sum[n / d][i] % MOD;
              (ans += MOD) %= MOD; 
          }
            
    }
    printf("%lld", ans);
    return 0;
}