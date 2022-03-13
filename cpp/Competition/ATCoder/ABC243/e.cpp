#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

const int N = 310;
const int M = 10000;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, d[N][N], e[M][3], cnt[N][N], ans;

signed main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(m); memset(d, 0x3f, sizeof d);
    for (int i = 1, a, b, c; i <= m; ++ i) {
        read(a), read(b), read(c);
        e[i][0] = a, e[i][1] = b; e[i][2] = c;
        d[a][b] = d[b][a] = c;
        cnt[a][b] = cnt[b][a] = 1;
    }
    for (int k = 1; k <= n; ++ k)
      for (int i = 1; i <= n; ++ i) {
          if (i == k) continue;
          for (int j = i + 1; j <= n; ++ j) {
              if (i == j || j == k) continue;
              if (!cnt[k][i] || !cnt[k][j]) continue;
              if (d[k][i] + d[k][j] < d[i][j]) {
                  d[j][i] = d[i][j] = d[k][i] + d[k][j];
                  cnt[i][j] = cnt[j][i] = cnt[k][i] * cnt[j][k];
              } else if (d[k][i] + d[k][j] == d[i][j])
                ++ cnt[i][j], ++ cnt[j][i];
          }
      }
    for (int i = 1; i <= m; ++ i)
      if (d[e[i][0]][e[i][1]] < e[i][2]) ++ ans;
      else if (d[e[i][0]][e[i][1]] == e[i][2])
        if (cnt[e[i][0]][e[i][1]] > 1) ++ ans;
    printf("%lld\n", ans); return (0 - 0);
}
