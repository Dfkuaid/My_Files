#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1000010;
const ll MOD = 998244353;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, q, p[N], prod[N], inv[N], sum[N];

inline int fpow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = (1ll * res * x) % MOD;
        y >>= 1; x = (1ll * x * x) % MOD;
    }
    return res;
}

inline int calc(int x, int y) {
    return 1ll * (sum[x] + MOD - sum[y + 1]) * prod[y + 1] % MOD;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(q); prod[n + 1] = 1;
    for (int i = 1; i <= n; ++ i) read(p[i]);
    for (int i = n; i >= 1; -- i)
      prod[i] = (1ll * p[i] * prod[i + 1]) % MOD;
    inv[1] = fpow(prod[1], MOD - 2);
    for (int i = 2; i <= n; ++ i)
      inv[i] = (1ll * inv[i - 1] * p[i - 1]) % MOD;
    for (int i = n; i >= 1; -- i)
      sum[i] = (sum[i + 1] + inv[i]) % MOD;
    while (q --) {
        int x, y; read(x), read(y);
        printf("%d\n", calc(x, y));
    }
    return 0;
}
