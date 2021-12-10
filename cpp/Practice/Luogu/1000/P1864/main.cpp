#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)
using namespace std;

const int N = 110;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int val, tar, w;} p[N];

int n, k, t[N], tcnt, s[N], f[N][N][N], ans = INF;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(k); memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++ i) read(p[i].val);
    for (int i = 1; i <= n; ++ i) read(p[i].tar);
    for (int i = 1; i <= n; ++ i) read(p[i].w);
    for (int i = 1; i <= n; ++ i) t[++ tcnt] = p[i].tar;
    auto cmp = [](Node x, Node y){return x.val < y.val;};
    sort(p + 1, p + n + 1, cmp); sort(t + 1, t + tcnt + 1);
    for (int i = 1; i <= n; ++ i) s[i] = s[i - 1] + p[i].w;
    tcnt = unique(t + 1, t + tcnt + 1) - t - 1;
    for (int i = 1; i <= n; ++ i) p[i].tar = lb(t, tcnt, p[i].tar) - t;
    for (int i = 1; i <= n; ++ i) for (int j = 1; j <= tcnt; ++ j)
      f[i][i][j] = p[i].tar < j ? k + p[i].w : p[i].w;
    for (int x = 2; x <= n; ++ x)
      for (int l = 1, r = l + x - 1; r <= n; ++ l, ++ r) {
        for (int i = 1; i <= tcnt; ++ i)
          for (int j = l; j <= r; ++ j) {
              int val = s[r] - s[l - 1];
              if (j > l) val += f[l][j - 1][i];
              if (j < r) val += f[j + 1][r][i];
              f[l][r][i] = min(f[l][r][i], val + k);
              if (p[j].tar < i) continue;
              val = s[r] - s[l - 1];
              if (j > l) val += f[l][j - 1][p[j].tar];
              if (j < r) val += f[j + 1][r][p[j].tar];
              f[l][r][i] = min(f[l][r][i], val);
          }
    }
    for (int i = 1; i <= tcnt; ++ i) ans = min(ans, f[1][n][i]);
    printf("%d", ans); return 0;
}
