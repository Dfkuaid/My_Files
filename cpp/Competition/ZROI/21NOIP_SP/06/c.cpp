#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 110;
const ll INF = 1e18;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

ll n, l, a[N], ans, f[N][40][N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(l);
    while (n || l) {
        for (int i = 1; i <= n; ++ i) read(a[i]);
        auto cmp = [](int x, int y){return x > y;};
        sort(a + 1, a + n + 1, cmp); mset(f, 0x3f);
        f[0][1][2] = f[0][1][1] = 0; ans = INF;
        for (int i = 0; i < n; ++ i)
          for (int j = 1; j <= l; ++ j)
            for (int k = 1; k <= Min(n, 1ll << j); ++ k)
              if (f[i][j][k] < INF) {
                  f[i + 1][j][k - 1] = Min(f[i + 1][j][k - 1], f[i][j][k] + 1ll * a[i + 1] * j);
                  f[i][j + 1][k * 2] = Min(f[i][j + 1][k * 2], f[i][j][k]); 
              }
        for (int i = 0; i <= l; ++ i)
          for (int j = 0; j <= Min(n, 1ll << i); ++ j)
            ans = Min(ans, f[n][i][j]);
        printf("%lld\n", ans); read(n), read(l);
    }
    return 0;
}
