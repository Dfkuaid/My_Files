#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 300010;
const ll MOD = 998244353;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, T; ll ans, a[N], b[N], ta[N], tb[N], tot;
ll sma, smb, sum, posa[N], posb[N], vis[N], vpos[N];

#define lb(t, len, x) lower_bound(t + 1, t + len + 1, x)

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(T);
    for (int i = 1; i <= n; ++ i)
      read(a[i]), (sma += a[i] * a[i] % MOD) %= MOD, ta[i] = a[i];
    for (int i = 1; i <= n; ++ i)
      read(b[i]), (smb += b[i] * b[i] % MOD) %= MOD, tb[i] = b[i];
    sort(ta + 1, ta + n + 1); sort(tb + 1, tb + n + 1);
    for (int i = 1; i <= n; ++ i)
      (sum += ta[i] * tb[i] % MOD) %= MOD;
    ans = ((sma + smb) % MOD - 2 * sum % MOD + MOD) % MOD;
    printf("%lld ", ans); if (!T) return 0;
    for (int i = 1; i <= n; ++ i) posa[i] = lb(ta, n, a[i]) - ta;
    for (int i = 1; i <= n; ++ i) posb[i] = lb(tb, n, b[i]) - tb;
    for (int i = 1; i <= n; ++ i) vpos[posb[i]] = i;
    for (int i = 1; i <= n; ++ i) posa[i] = vpos[posa[i]];
    for (int i = 1; i <= n; ++ i) {
        if (vis[i]) continue; int now = i; ++ tot;
        while (!vis[now]) {vis[now] = 1, now = posa[now];}
    }
    printf("%lld", n - tot);
    return 0;
}   
