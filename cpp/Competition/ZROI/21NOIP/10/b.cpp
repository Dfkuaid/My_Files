#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1010;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m; ll a[N][N], b[N][N], sum;

inline void madd(ll &x, ll y) {x = x + y < MOD ? x + y : x + y - MOD;}

ll fpow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % MOD;
        y >>= 1; x = x * x % MOD;
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j)
        read(a[i][j]);
    if (n == 1) {
        int flg = 1;
        for (int i = 2; i <= m; ++ i)
          if (a[1][i] != a[1][1]) {flg = 0; break;}
        if (!flg) {puts("-1"); return 0;}
        puts("1");
        for (int i = 1; i < m; ++ i) printf("0 ");
        printf("%lld", a[1][1]); return 0;
    } else if (m == 1) {
        int flg = 1;
        for (int i = 2; i <= n; ++ i)
          if (a[i][1] != a[1][1]) {flg = 0; break;}
        if (!flg) {puts("-1"); return 0;}
        puts("1");
        for (int i = 1; i < n; ++ i) puts("0");
        printf("%lld", a[1][1]); return 0;
    }
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j)
        madd(sum, a[i][j]);
    b[1][1] = MOD - sum * fpow(n + m - 1, MOD - 2) % MOD;
    for (int i = 1; i <= n; ++ i) madd(a[i][1], b[1][1]);
    for (int i = 2; i <= m; ++ i) madd(a[1][i], b[1][1]);
    for (int i = 1; i <= n; ++ i) {
        ll t = 0;
        for (int j = 1; j <= m; ++ j) madd(t, a[i][j]);
        t = MOD - t * fpow(m - 1, MOD - 2) % MOD;
        madd(b[i][1], t);
        for (int j = 2; j <= m; ++ j) madd(a[i][j], t);
    }
    for (int i = 1; i <= m; ++ i) {
        ll t = 0;
        for (int j = 1; j <= n; ++ j) madd(t, a[j][i]);
        t = MOD - t * fpow(n - 1, MOD - 2) % MOD;
        madd(b[1][i], t);
        for (int j = 2; j <= n; ++ j) madd(a[j][i], t);
    }
    for (int i = n; i > 1; -- i)
      for (int j = m; j > 1; -- j) {
          madd(a[1][1], MOD - a[i][j]);
          madd(a[i][1], a[i][j]);
          madd(a[1][j], a[i][j]);
          madd(b[1][1], a[i][j]);
          madd(b[i][j], a[i][j]);
          madd(b[i][1], MOD - a[i][j]);
          madd(b[1][j], MOD - a[i][j]);
          a[i][j] = 0;
      }
    puts("1");
    for (int i = 1; i <= n; ++ i, puts(""))
      for (int j = 1; j <= m; ++ j)
        printf("%lld ", (MOD - b[i][j]) % MOD);
    return 0;
}
