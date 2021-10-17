#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 110;
const int INF = 0x3fffffff;
const int MOD = 998244353;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

char s[N];
int n, m; ll ans, vec[N], dm[N][N], cnt[N][10], w[N], f[N];

inline ll fpow(ll x, ll y) {
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
    read(n), read(m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; ++ j)
          ++ cnt[i][s[j] - '0'];
    }
    for (int i = 0; i <= m; ++ i) {
        dm[i][0] = 1;
        for (int j = 1; j <= i; ++ j)
          dm[i][j] = dm[i][j - 1] * (i - j + 1) % MOD;
    }
    for (int i = 1; i < (1 << n); ++ i) {
        int tot = 0; ll sum = 0;
        for (int j = 0; j < n; ++ j) 
          if (i & (1 << j)) vec[++ tot] = j + 1;
        f[0] = 1; for (int j = 1; j <= m; ++ j) f[j] = 0;
        for (int j = 0; j <= 9; ++ j) {
            for (int l = 0; l <= m; ++ l) {
                 w[l] = fpow(dm[l][l], MOD - 2);
                 for (int k = 1; k <= tot; ++ k)
                    w[l] = w[l] * dm[cnt[vec[k]][j]][l] % MOD;
            }
            for (int l = m; l >= 0; -- l)
              for (int k = l - 1; k >= 0; -- k)
                (f[l] += f[k] * w[l - k] % MOD) %= MOD;
        }
        for (int j = 0; j <= m; ++ j) {
            ll tmp = f[j] * dm[j][j] % MOD;
            ll prod = fpow(dm[m][j], MOD - 2);
            (sum += tmp * fpow(prod, tot) % MOD) %= MOD;
        }
        if (tot & 1) (ans += sum) %= MOD;
        else ans = (ans - sum + MOD) % MOD;
    }
    printf("%lld", ans); return 0;
}
