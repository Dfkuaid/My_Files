#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

ll f[N][N], g[N], h[N], H[N << 1], a[N], b[N], n, k, fac[N], c[N][N], ans;

inline int opt(int a) {return (a & 1) ? (-1) : 1;}

inline int fpow(int a, int b, int mod) {
    int res = 1;
    while(b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod; b >>= 1;
    } return res;
}

inline void dp(int x) {
    for (int i = 0; i <= n; ++ i) f[i][0] = 1;
    int now = 0;
    for (int i = 1; i <= n; ++ i) {
        while (now + 1 <= n && b[now + 1] + a[i] <= x) ++ now;
        for (int j = 1; j <= i; ++ j)
          f[i][j] = (f[i - 1][j] + 1ll * f[i - 1][j - 1] * (now - j + 1) % MOD) % MOD;
    }
}

inline void prework() {
    fac[0] = 1;
    for (int i = 1; i <= n; ++ i) fac[i] = 1ll * fac[i - 1] * i % MOD;
    for (int i = 0; i <= n; ++ i)
      for (int j = 0; j <= i; ++ j)
        if (j ==i || j == 0) c[i][j] = 1;
        else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
}

inline int solve(int x) {
    for (int i = 0; i <= n; ++ i) g[i] = 1ll * fac[n - i] * f[n][i] % MOD;
    for (int i = n - k + 1; i <= n; ++ i) {
        for (int j = i; j <= n; ++ j)
          h[i] = (h[i] + opt(j - i) * c[j][i] * g[j] % MOD) % MOD;
        (H[x] += h[i]) %= MOD;
    }
    return (H[x] - H[x - 1] + MOD) % MOD;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(k);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i) read(b[i]);
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
    reverse(a + 1, a + n + 1); prework();
    for (int i = 2; i <= 800; ++ i) {
        dp(i); ll nowans = solve(i);
        ans = (ans + nowans * i % MOD) % MOD;
        for (int i = 1; i <= n; ++ i) h[i] = 0;
    }
    ans = 1ll * ans * fpow(fac[n], MOD - 2, MOD) % MOD;
    printf("%lld\n", ans); return 0;
}
