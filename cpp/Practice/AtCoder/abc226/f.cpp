#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 110;
const int MOD = 998244353;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, k, fac[N], fac_p[N][N], res, inv_fac[N], inv_fac_p[N][N], ans;

inline void madd(int &x, int y) {x = x + y < MOD ? x + y : x + y - MOD;}
int gcd(int x, int y) {return y ? gcd(y, x % y) : x;}
inline int lcm(int x, int y) {return (1ll * x * y / gcd(x, y)) % MOD;}

inline int fpow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = 1ll * res * x % MOD;
        y >>= 1; x = 1ll * x * x % MOD;
    }
    return res;
}

inline void calc(int val, int num) {
    val = fpow(val, k);
    madd(ans, 1ll * val * num % MOD);
}

void dfs(int rst, int lmt, int val, int num) {
    if (!rst) {calc(val, num); return;} if (rst < lmt) return;
    for (int i = lmt; i <= rst; ++ i)
      for (int j = 1; i * j <= rst; ++ j) {
          int new_num = 1ll * num * inv_fac_p[i][j] % MOD;
          new_num = 1ll * new_num * inv_fac[j] % MOD * fac_p[i - 1][j] % MOD;
          dfs(rst - i * j, i + 1, lcm(val, i), new_num);
      }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(k); fac[0] = 1;
    for (int i = 1; i <= n; ++ i)
      fac[i] = 1ll * fac[i - 1] * i % MOD;
    for (int i = 0; i <= n; ++ i)
      for (int j = 0; j <= n; ++ j)
        fac_p[i][j] = fpow(fac[i], j);
    for (int i = 0; i <= n; ++ i)
      inv_fac[i] = fpow(fac[i], MOD - 2);
    for (int i = 0; i <= n; ++ i)
      for (int j = 0; j <= n; ++ j)
        inv_fac_p[i][j] = fpow(fac_p[i][j], MOD - 2);
    dfs(n, 1, 1, fac[n]); printf("%d", ans); return 0;
}
